#pragma once
#include <boost/asio.hpp>

class AVRServer
{
public:
    AVRServer();
private:
    unsigned short mPortNum;
    std::shared_ptr<boost::asio::ip::tcp::acceptor> mAcceptor;
}