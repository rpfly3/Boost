#include<boost/asio.hpp>

AVRClient::AVRClient()
{
    // Parse IP address and build endpoint
    mRawServerIPAddress = "127.0.0.1";
    mPortNum = 9973;

    boost::system::error_code ret;
    boost::asio::ip::address serverIPAddress = 
        boost::asio::ip::address::from_string(mRawServerIPAddress, ret);
    if(ret.value() != 0)
    {
        std::cerr << "Failed to parse IP address. Error code = "
                  << ret.value() << ". Message: " << ret.message()
                  << " at " << __LINE__ << std::endl;
        exit(-1);
    }
    boost::asio::ip::tcp::endpoint endPoint(serverIPAddress, mPortNum);

    // Build socket
    boost::asio::io_service io;
    mSocket = std::make_shared<boost::asio::ip::tcp::socket>(io, endPoint.protocol());

    mSock->connect(endPoint, ret);
    if(ret.value() != 0)
    {
        std::cerr << "Failed to connect the socket ! Error code = "
                  << ret.value() << ". Message: " << ret.message()
                  << " at " << __LINE__ << std::endl;
        exit(-1);
    }
}

AVRClient::AVRClient(std::string server_ip_address)
{
    // Parse IP address and build endpoint
    mRawServerIPAddress = server_ip_address;
    mPortNum = 9973;

    boost::system::error_code ret;
    boost::asio::ip::address serverIPAddress = 
        boost::asio::ip::address::from_string(mRawServerIPAddress, ret);

    if(ret.value() != 0)
    {
        std::cerr << "Failed to parse IP address. Error code = "
                  << ret.value() << ". Message: " << ret.message()
                  << " at " << __LINE__ << std::endl;
        exit(-1);
    }

    boost::asio::ip::tcp::endpoint endPoint(serverIPAddress, mPortNum);

    // Build socket
    boost::asio::io_service io;
    mSocket = std::make_shared<boost::asio::ip::tcp::socket>(io, endPoint.protocol());

    mSock->connect(endPoint, ret);
    if(ret.value() != 0)
    {
        std::cerr << "Failed to connect the socket ! Error code = "
                  << ret.value() << ". Message: " << ret.message()
                  << " at " << __LINE__ << std::endl;
        exit(-1);
    }
}