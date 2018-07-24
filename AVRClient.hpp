#pragma once
#include <boost/asio.hpp>
#include <boost/thread/thread.hpp>
#include <string>

class AVRClient
{
public:
    AVRClient();
    AVRClient(std::string server_ip_address);
    void Connect();
    void Shutdown();

	boost::asio::io_service mIO;
    std::shared_ptr<boost::asio::io_service::work> mPtrWork;
    std::shared_ptr<boost::thread> mPtrThread;
    std::shared_ptr<boost::asio::ip::tcp::socket> mPtrSocket;
private:
    unsigned short mPortNum;
    std::string mRawServerIPAddress;
};