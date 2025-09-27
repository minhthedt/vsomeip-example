#include <iomanip>
#include <iostream>
#include <sstream>

#include <vsomeip/vsomeip.hpp>
#include <dlt/dlt.h>
#include <condition_variable>
#include <thread>
 
#define SAMPLE_SERVICE_ID 0x1234
#define SAMPLE_INSTANCE_ID 0x5678
#define SAMPLE_METHOD_ID 0x0421
#define APPLICATION_NAME  "response-sample-x"

// 🔹 Define DLT context
DLT_DECLARE_CONTEXT(my_dlt_context);

std::shared_ptr<vsomeip::application> app;
bool is_registered_ = false;
std::mutex mutex_;
std::condition_variable condition_;

void on_state(vsomeip::state_type_e _state) {
    std::cout << "Application " << app->get_name() << " is "
            << (_state == vsomeip::state_type_e::ST_REGISTERED ?
                    "registered." : "deregistered.")
            << std::endl;
    std::lock_guard<std::mutex> its_lock(mutex_);
    if (_state == vsomeip::state_type_e::ST_REGISTERED) {
        std::cout << "Application registered. Offering service..." << std::endl;
         if (!is_registered_) {
            is_registered_ = true;
            condition_.notify_one();
        }
    } else { // vsomeip::state_type_e::ST_DEREGISTERED
        std::cerr << "Application is NOT registered" << std::endl;
        is_registered_ = false;
    }

}

void on_message(const std::shared_ptr<vsomeip::message> &_request) {
 
    std::shared_ptr<vsomeip::payload> its_payload = _request->get_payload();
    vsomeip::length_t l = its_payload->get_length();
 
    // Get payload
    std::stringstream ss;
    for (vsomeip::length_t i=0; i<l; i++) {
       ss << std::setw(2) << std::setfill('0') << std::hex
          << (int)*(its_payload->get_data()+i) << " ";
    }
 
    std::cout << "SERVICE: Received message with Client/Session ["
        << std::setw(4) << std::setfill('0') << std::hex << _request->get_client() << "/"
        << std::setw(4) << std::setfill('0') << std::hex << _request->get_session() << "] "
        << ss.str() << std::endl;

    DLT_LOG(my_dlt_context, DLT_LOG_INFO, DLT_STRING("Received message: "), DLT_STRING(ss.str().c_str()));

    // Create response
    std::shared_ptr<vsomeip::message> its_response = vsomeip::runtime::get()->create_response(_request);
    its_payload = vsomeip::runtime::get()->create_payload();
    std::vector<vsomeip::byte_t> its_payload_data;
    for (int i=9; i>=0; i--) {
        its_payload_data.push_back(i % 256);
    }
    its_payload->set_data(its_payload_data);
    its_response->set_payload(its_payload);
    app->send(its_response);
}

void offer() {
    std::unique_lock<std::mutex> its_lock(mutex_);
    if (!is_registered_) {
        condition_.wait(its_lock);
    }

    DLT_LOG(my_dlt_context, DLT_LOG_INFO, DLT_STRING("offer_service is called"));
    std::cout << "offer_service is called" << std::endl;
    app->offer_service(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID);
}

int main() {
    DLT_REGISTER_APP("RESPONSE", "VSOMEIP Application");
    DLT_REGISTER_CONTEXT(my_dlt_context, "RESPONSE", "VSOMEIP Service Context");
    std::thread offer_thread(offer);
    app = vsomeip::runtime::get()->create_application(APPLICATION_NAME);
    if (!app->init()) {
        std::cerr << "Couldn't initialize application" << std::endl;
        return false;
    }
    app->register_state_handler(on_state);
    app->register_message_handler(SAMPLE_SERVICE_ID, SAMPLE_INSTANCE_ID, SAMPLE_METHOD_ID, on_message);
    app->start();
   
}