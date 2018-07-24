#include "AVRClient.hpp"
#include <iostream>

AVRClient::AVRClient()
{
    // To prevent io_service from running out of work
    mPtrWork = std::make_shared<boost::asio::io_service::work>(mIO);
    // The working thread
    mPtrThread = std::make_shared<boost::thread>(
        boost::thread(boost::bind(&boost::asio::io_service::run, &mIO)));
    mPtrSocket = std::make_shared<boost::asio::ip::tcp::socket>(mIO);

    // Parse IP address and build endpoint
    mRawServerIPAddress = "127.0.0.1";
    mPortNum = 1234;
}

AVRClient::AVRClient(std::string server_ip_address)
{
    // To prevent io_service from running out of work
    mPtrWork = std::make_shared<boost::asio::io_service::work>(mIO);
    // The working thread
    mPtrThread = std::make_shared<boost::thread>(
        boost::thread(boost::bind(&boost::asio::io_service::run, &mIO)));
    mPtrSocket = std::make_shared<boost::asio::ip::tcp::socket>(mIO);

    // Parse IP address and build endpoint
    mRawServerIPAddress = server_ip_address;
    mPortNum = 1234;
}

void AVRClient::Connect()
{
	auto endpoint = boost::asio::ip::tcp::resolver(mIO).resolve({ 
	    mRawServerIPAddress.c_str(), "1234" });
	boost::asio::connect(*mPtrSocket, endpoint);

	// options to test
    mPtrSocket->set_option(boost::asio::ip::tcp::no_delay(true)); 
	mPtrSocket->set_option(boost::asio::socket_base::receive_buffer_size(1920 * 1080 * 4));
	mPtrSocket->set_option(boost::asio::socket_base::send_buffer_size(1920 * 1080 * 4));
}

void AVRClient::Shutdown()
{
    mIO.stop();
	mPtrThread->join();
}