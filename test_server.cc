#include <thread>
#include <chrono>
#include <vector>
#include <deque>
#include <signal.h>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include "AVRServer.hpp"

typedef std::deque<AVRMessage> AVRMessageQueue;

AVRMessageQueue avr_message_queue;

namespace
{
bool keepGoing = true;
void shutdown(int)
{
	keepGoing = false;
}

std::size_t bytesAccum = 0;
void justReceive(boost::system::error_code ec, std::size_t bytesReceived,
    boost::asio::ip::tcp::socket &socket, AVRMessage& receive_message)
{
	char* buffer = receive_message.GetHeader();
	bytesAccum += bytesReceived;
	for (size_t it = 0; it != bytesReceived; ++it)
	{
		if (buffer[it] == 'e')
		{
			std::printf("server got: %lu\n", bytesAccum);
			bytesAccum = 0;
		}
	}

	socket.async_receive(
	    boost::asio::buffer(receive_message.GetHeader(), 2048),
	    0,
	    boost::bind(justReceive, _1, _2, boost::ref(socket), 
	                                    boost::ref(receive_message)));
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