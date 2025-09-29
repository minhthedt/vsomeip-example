// HelloWorldStubImpl.cpp
#include "HelloWorldStubImpl.hpp"

HelloWorldStubImpl::HelloWorldStubImpl() {
}

HelloWorldStubImpl::~HelloWorldStubImpl() {
}

void HelloWorldStubImpl::sayHello(const std::shared_ptr<CommonAPI::ClientId> _client,
        std::string _name, sayHelloReply_t _reply) {

    std::cout << "------------------Server receive:" << _name  << "'\n";
    std::stringstream messageStream;
    messageStream << "Server send: Hello " << _name << "!";
    _reply(messageStream.str());
};