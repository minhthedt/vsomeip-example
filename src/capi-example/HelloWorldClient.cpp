// HelloWorldClient.cpp
#include <iostream>
#include <string>
#include <thread>

#ifndef _WIN32
#include <unistd.h>
#endif

#include <CommonAPI/CommonAPI.hpp>
#include <v0/commonapi/examples/HelloWorldProxy.hpp>
#include <dlt/dlt.h>
// 🔹 Define DLT context
DLT_DECLARE_CONTEXT(my_dlt_context);
using namespace v0::commonapi::examples;


std::string toString(const v1::commonapi::examples::CommonTypes::StudentStruct& val) {
    std::stringstream ss;
    ss << "name = " << val.getName().c_str() 
       << " age = " << val.getProfile().getAge()
        << " gender = " << val.getProfile().getGender()
        << " score = " << val.getProfile().getScore();
    return ss.str();
}

void sayHello_cb(const CommonAPI::CallStatus& callStatus, const std::string& out) {
    std::cout << "---------sayHello callback: " << out.c_str() << std::endl;
}

void setValue_cb(const CommonAPI::CallStatus& callStatus) {
    std::cout << "---------setValue callback" << std::endl;
}

int main() {
    CommonAPI::Runtime::setProperty("LogContext", "VSIP");
    CommonAPI::Runtime::setProperty("LogApplication", "E01C");
    CommonAPI::Runtime::setProperty("LibraryBase", "HelloWorld");
    DLT_REGISTER_CONTEXT(my_dlt_context, "MEEE", "Example Context");

    std::shared_ptr < CommonAPI::Runtime > runtime = CommonAPI::Runtime::get();

    std::string domain = "local";
    std::string instance = "commonapi.examples.HelloWorld";
    std::string connection = "HelloWorldClient";

    std::shared_ptr<HelloWorldProxy<>> myProxy = runtime->buildProxy<HelloWorldProxy>(domain,
            instance, connection);

    std::cout << "Checking availability!" << std::endl;
    while (!myProxy->isAvailable())
        std::this_thread::sleep_for(std::chrono::microseconds(10));
    std::cout << "Available..." << std::endl;

    // Subscribe to broadcast
    myProxy->getMyStatusEvent().subscribe([&](const int32_t& val) {
        std::cout << "----------Received MyStatusEvent: MyStatus = " << val << std::endl;
        DLT_LOG(my_dlt_context, DLT_LOG_INFO, DLT_STRING("----------Received broadcast MyStatus = "), DLT_INT(val));
    });

    // subscribe to attribute
    myProxy->getStudentDataAttribute().getChangedEvent().subscribe([&](const v1::commonapi::examples::CommonTypes::StudentStruct& val) {
        printf("----------Receive StudentDataAttribute notificaiton: %s\n", toString(val).c_str());
        DLT_LOG(my_dlt_context, DLT_LOG_INFO, DLT_STRING("----------Receive Attribute notificaiton:"), DLT_STRING(toString(val).c_str()));
    });

    const std::string name = "World";
    CommonAPI::CallStatus callStatus;
    std::string returnMessage;

    CommonAPI::CallInfo info(1000);
    info.sender_ = 1234;

    int myValue = 255;
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(2));
        printf("wait 2s...\n");
        //[ASYNC] SET Method
        printf("SET Method: setValue(%d)\n", myValue);
        //myProxy->setValueAsync(myValue, setValue_cb, &info);
        myProxy->setValue(myValue, callStatus, &info);
        if (callStatus != CommonAPI::CallStatus::SUCCESS) {
            printf("ERROR:setValue(%d) callStatus=%d\n", myValue, static_cast<uint32_t>(callStatus));
            DLT_LOG(my_dlt_context, DLT_LOG_ERROR, DLT_STRING("ERROR:setValue(%d) callStatus= "), DLT_INT(static_cast<uint32_t>(callStatus)));
        }

        //[SYNC] request&response
        int32_t sum = 0;
        int32_t a = 3, b = 4;
        
        printf("SET Method: calculateSum(%d, %d)\n", a, b);
        myProxy->calculateSum(a, b, callStatus, sum, &info);
        if (callStatus != CommonAPI::CallStatus::SUCCESS) {
            std::cerr << "Remote call failed!\n";
            return -1;
        }
        printf("----------SET Method: calculateSum(%d, %d) = %d\n", a, b, sum);
        DLT_LOG(my_dlt_context, DLT_LOG_INFO, DLT_STRING("----------SET Method: calculateSum(3, 4) = "), DLT_INT(sum));

        //[ASYNC] request&response
        myProxy->sayHelloAsync(name, sayHello_cb, &info);

        info.timeout_ = info.timeout_ + 1000;

        //get attribute
        v1::commonapi::examples::CommonTypes::StudentStruct data;
        //myProxy->getStudentDataAttribute().getValueAsync(data, fcb_s, &info);
        myProxy->getStudentDataAttribute().getValue(callStatus, data, &info);
        if (callStatus != CommonAPI::CallStatus::SUCCESS) {
            std::cerr << "Remote call A failed!\n";
        } else {
            printf("----------getStudentDataAttribute: %s\n", toString(data).c_str());
            DLT_LOG(my_dlt_context, DLT_LOG_INFO, DLT_STRING("----------getStudentDataAttribute:"), DLT_STRING(toString(data).c_str()));
        }
        
         printf("wait 2s...\n");
        std::this_thread::sleep_for(std::chrono::seconds(2));

        //set attritube: increase age
        // int count = data.getProfile().getAge();
        // count++;
        // auto profile = data.getProfile();
        // profile.setAge(count);
        // data.setProfile(profile);
        // // myProxy->getStudentDataAttribute().setValueAsync(data, fcb_s, &info);
        // //WARNING ISSUE: both client and server modify attribute => data race
        // printf("++++++++++setStudentDataAttribute: %s\n", toString(data).c_str());
        // DLT_LOG(my_dlt_context, DLT_LOG_INFO, DLT_STRING("++++++++++setStudentDataAttribute:"), DLT_STRING(toString(data).c_str()));
        // myProxy->getStudentDataAttribute().setValue(data, callStatus, data, &info);
        // if (callStatus != CommonAPI::CallStatus::SUCCESS) {
            // std::cerr << "Remote call A failed!\n";
        // } else {
        // }
    }

    return 0;
}