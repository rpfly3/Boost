#pragma once
#include<boost/asio.hpp>

class AVRClient
{
public:
    AVRClient();
    AVRClient(std::string server_ip_address);

private:
    unsigned short mPortNum;
    std::string mRawServerIPAddress;
    std::shared_ptr<boost::asio::ip::tcp::socket> mSocket;
}