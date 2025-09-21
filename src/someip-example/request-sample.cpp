#include <iomanip>
#include <iostream>
#include <sstream>
#include <chrono>
#include <condition_variable>
#include <thread>
#include <atomic>
#include <csignal>
#include <mutex>

#include <vsomeip/vsomeip.hpp>
#include <dlt/dlt.h>

#define SAMPLE_SERVICE_ID   0x1234
#define SAMPLE_INSTANCE_ID  0x5678
#define SAMPLE_METHOD_ID    0x0421

DLT_DECLARE_CONTEXT(my_dlt_context);

std::shared_ptr<vsomeip::application> app;
std::mutex mutex_;
std::condition_variable condition;
std::atomic<bool> running{true};
std::atomic<bool> service_available{false};

// Signal handler: do minimal, async-signal-safe-ish actions
void handle_signal(int /*signum*/) {
    // set running false, notify waiting thread and stop vsomeip loop
    running.store(false);
    condition.notify_all();
    if (app) {
        // calling app->stop() from a signal handler is typically OK because
        // vsomeip stops its loop and is thread-safe; keep this minimal.
        app->stop();
    }
}

void run_sender() {
    std::unique_lock<std::mutex> lk(mutex_);
    // Wait until service becomes available or we are asked to stop
    while (running && !service_available.load()) {
        if (condition.wait_for(lk, std::chrono::seconds(5)) == std::cv_status::timeout) {
            if (!running) return;
            // reloop and wait again or log
        }
    }

    // prepare payload once
    auto payload = vsomeip::runtime::get()->create_payload();
    std::vector<vsomeip::byte_t> data;
    for (vsomeip::byte_t i = 0; i < 10; ++i) data.push_back(i);
    payload->set_data(data);

    // send periodically while running and service is available
    while (running.load() && service_available.load()) {
        auto req = vsomeip::runtime::get()->create_request();
        req->set_service(SAMPLE_SERVICE_ID);
        req->set_instance(SAMPLE_INSTANCE_ID);
        req->set_method(SAMPLE_METHOD_ID);
        req->set_payload(payload);
        bool use_tcp = false;
        req->set_reliable(use_tcp);
		if (use_tcp) {
			std::cout << "Client sending TCP..." << std::endl;
		} else {
			std::cout << "Client sending UDP..." << std::endl;
		}
        try {
            app->send(req);
        } catch (const std::exception &e) {
            std::cerr << "send() exception: " << e.what() << std::endl;
        }
        std::this_thread::sleep_for(std::chrono::seconds(3));
    }
}

void on_message(const std::shared_ptr<vsomeip::message> &_response) {
    auto its_payload = _response->get_payload();
    vsomeip::length_t l = its_payload->get_length();

    std::stringstream ss;
    for (vsomeip::length_t i = 0; i < l; ++i) {
        ss << std::setw(2) << std::setfill('0') << std::hex
           << (int)*(its_payload->get_data() + i) << " ";
    }

    DLT_LOG(my_dlt_context, DLT_LOG_INFO, DLT_STRING("Received message: "), DLT_STRING(ss.str().c_str()));
    std::cout << "CLIENT: Received message Client/Session ["
              << std::setw(4) << std::setfill('0') << std::hex << _response->get_client()
              << "/" << std::setw(4) << std::setfill('0') << std::hex << _response->get_session()
              << "] " << ss.str() << std::endl;
}

void on_state(vsomeip::state_type_e _state) {
    std::cout << "Application " << app->get_name() << " is "
        << (_state == vsomeip::state_type_e::ST_REGISTERED ?
                "registered." : "deregistered.")
        << std::endl;
    if (_state == vsomeip::state_type_e::ST_REGISTERED) {
        std::cout << "Application registered. request_service..." << std::endl;
        app->request_service(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID);
    } else {
        std::cerr << "Application is NOT registered" << std::endl;
    }
}

void on_availability(vsomeip::service_t /*_service*/, vsomeip::instance_t /*_instance*/, bool _is_available) {
    {
        std::lock_guard<std::mutex> lock(mutex_);
        service_available.store(_is_available);
    }
    if (_is_available) condition.notify_all();
    std::cout << "CLIENT: Service is " << (_is_available ? "available" : "NOT available") << std::endl;
}

int main() {
    // register signal handlers
    std::signal(SIGINT, handle_signal);
    std::signal(SIGTERM, handle_signal);

    DLT_REGISTER_APP("APP1", "VSOMEIP Application");
    DLT_REGISTER_CONTEXT(my_dlt_context, "APP1", "VSOMEIP Service Context");

    app = vsomeip::runtime::get()->create_application("request-sample");
    if (!app) {
        std::cerr << "Failed to create vsomeip application\n";
        return 1;
    }

    if (!app->init()) {
        std::cerr << "vsomeip init failed\n";
        return 1;
    }
    app->register_state_handler(on_state);
    app->register_availability_handler(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID, on_availability);
    app->register_message_handler(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID, SAMPLE_METHOD_ID, on_message);

    std::thread sender(run_sender);

    // start blocks until app->stop() is called (e.g., by signal)
    app->start();

    // after start returns, ensure sender thread stops and join
    running.store(false);
    condition.notify_all();
    if (sender.joinable()) sender.join();

    // cleanup DLT
    DLT_UNREGISTER_CONTEXT(my_dlt_context);
    DLT_UNREGISTER_APP();

    std::cout << "CLIENT: terminated cleanly." << std::endl;
    return 0;
}
