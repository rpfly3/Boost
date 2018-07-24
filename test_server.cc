#include <thread>
#include <chrono>
#include <vector>
#include <signal.h>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include "AVRServer.hpp"
namespace
{
bool keepGoing = true;
void shutdown(int)
{
	keepGoing = false;
}

std::size_t bytesAccum = 0;
void justReceive(boost::system::error_code ec, std::size_t bytesReceived,
    boost::asio::ip::tcp::socket &socket, std::vector<unsigned char> &buffer)
{
	bytesAccum += bytesReceived;

	auto end = buffer.begin() + bytesReceived;
	for (auto it = buffer.begin(); it != end; ++it)
	{
		if (*it == 'e')
		{
			std::printf("server got: %lu\n", bytesAccum);
			bytesAccum = 0;
		}
	}

	socket.async_receive(
	    boost::asio::buffer(buffer, 2048),
	    0,
	    boost::bind(justReceive, _1, _2, boost::ref(socket), 
	                                     boost::ref(buffer)));
}
}

int main(int, char **)
{
	signal(SIGINT, shutdown);

	AVRServer avrServer("127.0.0.1");
	avrServer.mPtrReceiveHandler = justReceive;
	avrServer.Accept();

	// Other function thread
	while (keepGoing)
	{
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}

	avrServer.Shutdown();

	std::cout << "Server: GoodBye" << std::endl;

	return 0;
}