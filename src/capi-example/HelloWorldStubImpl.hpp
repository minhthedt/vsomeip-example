// HelloWorldStubImpl.hpp
#ifndef HELLOWORLDSTUBIMPL_H_
#define HELLOWORLDSTUBIMPL_H_

#include <CommonAPI/CommonAPI.hpp>
#include <v0/commonapi/examples/HelloWorldStubDefault.hpp>

class HelloWorldStubImpl: public v0_1::commonapi::examples::HelloWorldStubDefault {

public:
    HelloWorldStubImpl();
    virtual ~HelloWorldStubImpl();

    virtual void sayHello(const std::shared_ptr<CommonAPI::ClientId> _client, std::string _name, sayHelloReply_t _return);
    virtual void calculateSum(const std::shared_ptr<CommonAPI::ClientId> _client,
        int32_t a, int32_t b, calculateSumReply_t _reply);
    virtual void setValue(const std::shared_ptr<CommonAPI::ClientId> _client,
        int32_t x, setValueReply_t _reply);

};
#endif /* HELLOWORLDSTUBIMPL_H_ */