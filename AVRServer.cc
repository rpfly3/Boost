#include "AVRServer.hpp"
#include <iostream>
#include <boost/bind.hpp>


AVRServer::AVRServer() : mVBuffer(2048, 0)
{
	// To prevent io_service from running out of work
    mPtrWork = std::make_shared<boost::asio::io_service::work>(mIO);
    // The working thread
    mPtrThread = std::make_shared<boost::thread>(
        boost::thread(boost::bind(&boost::asio::io_service::run, &mIO)));
    mPtrSocket = std::make_shared<boost::asio::ip::tcp::socket>(mIO);
    mPtrAcceptor = std::make_shared<boost::asio::ip::tcp::acceptor>(mIO,
	    boost::asio::ip::tcp::endpoint(
	        boost::asio::ip::address::from_string("127.0.0.1"), 1234));
}

AVRServer::AVRServer(std::string my_ip_address) : mVBuffer(2048, 0)
{
	// To prevent io_service from running out of work
    mPtrWork = std::make_shared<boost::asio::io_service::work>(mIO);
    // The working thread
    mPtrThread = std::make_shared<boost::thread>(
        boost::thread(boost::bind(&boost::asio::io_service::run, &mIO)));
    mPtrSocket = std::make_shared<boost::asio::ip::tcp::socket>(mIO);
    mPtrAcceptor = std::make_shared<boost::asio::ip::tcp::acceptor>(mIO,
	    boost::asio::ip::tcp::endpoint(
	        boost::asio::ip::address::from_string(my_ip_address.c_str()), 1234));
}


void AVRServer::AcceptHandler(boost::system::error_code ec)
{
    // options
    mPtrSocket->set_option(boost::asio::ip::tcp::no_delay(true)); 
    mPtrSocket->set_option(boost::asio::socket_base::receive_buffer_size(1920 * 1080 * 4));
    mPtrSocket->set_option(boost::asio::socket_base::send_buffer_size(1920 * 1080 * 4));

    mPtrSocket->async_receive(
        boost::asio::buffer(mVBuffer, 2048),
        0,
        boost::bind(mPtrReceiveHandler, _1, _2, boost::ref(*mPtrSocket), 
                                         boost::ref(mVBuffer)));
}

void AVRServer::Accept()
{
	mPtrAcceptor->async_accept(*mPtrSocket, boost::bind(&AVRServer::AcceptHandler, this, boost::asio::placeholders::error));
}

void AVRServer::Shutdown()
{
    mIO.stop();
	mPtrThread->join();
}