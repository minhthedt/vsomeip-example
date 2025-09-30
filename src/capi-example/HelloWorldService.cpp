// HelloWorldService.cpp
#include <iostream>
#include <thread>

#include <CommonAPI/CommonAPI.hpp>
#include "HelloWorldStubImpl.hpp"
#include <dlt/dlt.h>
// 🔹 Define DLT context
DLT_DECLARE_CONTEXT(my_dlt_context);
using namespace std;

std::string toString(const v1::commonapi::examples::CommonTypes::StudentStruct& val) {
    std::stringstream ss;
    ss << "name = " << val.getName().c_str() 
       << " age = " << val.getProfile().getAge()
        << " gender = " << val.getProfile().getGender()
        << " score = " << val.getProfile().getScore();
    return ss.str();
}

int main() {
    CommonAPI::Runtime::setProperty("LogContext", "VSIP");
    CommonAPI::Runtime::setProperty("LogApplication", "E01S");
    CommonAPI::Runtime::setProperty("LibraryBase", "HelloWorld");
    DLT_REGISTER_CONTEXT(my_dlt_context, "MEEE", "Example Context");

    std::shared_ptr<CommonAPI::Runtime> runtime = CommonAPI::Runtime::get();

    std::string domain = "local";
    std::string instance = "commonapi.examples.HelloWorld";
    std::string connection = "service-sample";

    std::shared_ptr<HelloWorldStubImpl> myService = std::make_shared<HelloWorldStubImpl>();
    bool successfullyRegistered = runtime->registerService(domain, instance, myService, connection);

    while (!successfullyRegistered) {
        std::cout << "Register Service failed, trying again in 100 milliseconds..." << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        successfullyRegistered = runtime->registerService(domain, instance, myService, connection);
    }

    std::cout << "Successfully Registered Service!" << std::endl;

    int32_t myStatus = 0;
    ::v1::commonapi::examples::CommonTypes::StudentStruct data;
    data.setName("Alice");
    data.setProfile(::v1::commonapi::examples::CommonTypes::ProfileStruct(myStatus, true, 9.5f));
    printf("++++++++++setStudentDataAttribute(...)\n");
    DLT_LOG(my_dlt_context, DLT_LOG_INFO, DLT_STRING("++++++++++setStudentDataAttribute:"), DLT_STRING(toString(data).c_str()));
    myService->setStudentDataAttribute(data);
    int count = 0;
    while (true) {
        printf("++++++++++fireMyStatusEvent(%d)\n", myStatus);
        DLT_LOG(my_dlt_context, DLT_LOG_INFO, DLT_STRING("++++++++++fireMyStatusEvent: "), DLT_INT(myStatus));
        myService->fireMyStatusEvent(myStatus++); // broadcast
        std::this_thread::sleep_for(std::chrono::seconds(5));
        count++;
        data.setName("Alice" + std::to_string(count));
        myService->setStudentDataAttribute(data);
    }

    return 0;
}