#include <thread>
#include <chrono>
#include <vector>
#include <signal.h>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include "AVRClient.hpp"

namespace
{
bool keepGoing = true;
void shutdown(int) { keepGoing = false; }
}

int main(int, char **)
{
	signal(SIGINT, shutdown);

    AVRClient avrClient("127.0.0.1");
    avrClient.Connect();

	std::vector<unsigned char> buffer(1920 * 1080 * 4, 0);
	buffer.back() = 'e';

	std::chrono::time_point<std::chrono::system_clock> last = 
	    std::chrono::system_clock::now();
	
	std::chrono::duration<double> delta = std::chrono::seconds(0);

	std::size_t bytesSent = 0;

	while (keepGoing)
	{
		// blocks during send
		boost::asio::write(*avrClient.mPtrSocket, boost::asio::buffer(buffer));
		std::cout << "Buffer size: " << buffer.size() << std::endl;
	}

    avrClient.Shutdown();

	std::cout << "Client: GoodByte" << std::endl;
}