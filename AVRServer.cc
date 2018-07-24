#include <boost/asio.hpp>

AVRServer::AVRServer()
{
    // Build TCP endpoint
    mPortNum = 9973;
    boost::asio::ip::address clientIPAddress = 
        boost::asio::ip::address_v4::any();
    boost::asio::ip::tcp::endpoint endPoint(clientIPAddress, mPortNum);

    // Build acceptor
    boost::asio::io_service io;
    mAcceptor = std::make_shared<boost::asio::ip::tcp::acceptor>(io, endPoint.protocol());
    boost::system::error_code ret;

    mAcceptor->bind(endPoint, ret);
    if(ret.value() != 0)
    {
        std::cerr << "Failed to bind the acceptor socket. Error code = "
                  << ret.value() << ". Message: " << ret.message()
                  << " at " << __LINE__ << std::endl;
        exit(-1);
    }
}