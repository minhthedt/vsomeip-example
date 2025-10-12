// HelloWorldStubImpl.cpp
#include "HelloWorldStubImpl.hpp"

HelloWorldStubImpl::HelloWorldStubImpl() {
}

HelloWorldStubImpl::~HelloWorldStubImpl() {
}

void HelloWorldStubImpl::sayHello(const std::shared_ptr<CommonAPI::ClientId> _client,
        std::string _name, sayHelloReply_t _reply) {

    std::cout << "----------sayHello:" << _name  << "'\n";
    std::stringstream messageStream;
    messageStream << "Hello client " << _name << "!";
    _reply(messageStream.str());
};

void HelloWorldStubImpl::calculateSum(const std::shared_ptr<CommonAPI::ClientId> _client,
        int32_t a, int32_t b, calculateSumReply_t _reply) {
    printf("----------calculateSum(%d, %d)\n", a, b);
    int32_t c = a + b;
    _reply(c);
}

void HelloWorldStubImpl::setValue(const std::shared_ptr<CommonAPI::ClientId> _client,
        int32_t x, setValueReply_t _reply) {
    printf("----------setValue(%d)\n", x);
    //_reply(); // did not call reply() => client raise timeout if waiting for response => REMOTE_ERROR
}