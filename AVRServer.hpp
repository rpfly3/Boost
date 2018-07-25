#pragma once

#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
#include <string>
#include <vector>
#include "AVRMessage.hpp"

typedef void (*Receive_Handler)(boost::system::error_code ec, std::size_t bytesReceived,
    boost::asio::ip::tcp::socket &socket, AVRMessage &receive_message);

class AVRServer
{
public:
    AVRServer();
    AVRServer(std::string my_ip_address);
    void AcceptHandler(boost::system::error_code ec);
    void Accept();
    void Shutdown();

    AVRMessage mReceivedMessage;
    boost::asio::io_service mIO;
    std::shared_ptr<boost::asio::io_service::work> mPtrWork;
    std::shared_ptr<boost::thread> mPtrThread;
    std::shared_ptr<boost::asio::ip::tcp::socket> mPtrSocket;
    std::shared_ptr<boost::asio::ip::tcp::acceptor> mPtrAcceptor;
    Receive_Handler mPtrReceiveHandler;
};