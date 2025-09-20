// HelloWorldStubImpl.cpp
#include "HelloWorldStubImpl.hpp"

HelloWorldStubImpl::HelloWorldStubImpl() {
}

HelloWorldStubImpl::~HelloWorldStubImpl() {
}

void HelloWorldStubImpl::sayHello(const std::shared_ptr<CommonAPI::ClientId> _client,
        std::string _name, sayHelloReply_t _reply) {

    std::stringstream messageStream;

    messageStream << "Hello " << _name << "!";
    std::cout << "Server receive:" << _name  << "'\n";

    //_reply(messageStream.str());
    std::cout << "Server response:" << messageStream.str()  << "'\n";
    try {
        _reply(messageStream.str());
    } catch (const std::exception& e) {
        std::cerr << "Exception in sayHello: " << e.what() << std::endl;
    }

};