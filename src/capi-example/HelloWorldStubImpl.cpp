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