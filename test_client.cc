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

    AVRClient avrClient;
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
		//socket.send(boost::asio::buffer(buffer));

		// accumulate bytes sent
		bytesSent += buffer.size();

		// accumulate time spent sending
		delta += std::chrono::system_clock::now() - last;
		last = std::chrono::system_clock::now();

		// print information periodically
		if (delta.count() >= 5.0) 
		{
			std::printf("Mbytes/sec: %f, Gbytes/sec: %f, Mbits/sec: %f, Gbits/sec: %f\n",
			            bytesSent / 1.0e6 / delta.count(),
			            bytesSent / 1.0e9 / delta.count(),
			            8 * bytesSent / 1.0e6 / delta.count(),
			            8 * bytesSent / 1.0e9 / delta.count());

			// reset accumulators
			bytesSent = 0;
			delta = std::chrono::seconds(0);
		}
	}

    avrClient.Shutdown();

	std::cout << "Client: GoodByte" << std::endl;
}