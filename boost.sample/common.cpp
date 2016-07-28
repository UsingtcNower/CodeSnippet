#include "common.h"
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <iostream>
#include <boost/thread.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <array>
#include <string>
#include <boost/asio/buffer.hpp>

namespace blocking_timer
{
	void print(const boost::system::error_code& ) 
	{
		std::cout<<"Hello, world!"<<std::endl;
	}

	int main()
	{
		boost::asio::io_service io;
		boost::asio::deadline_timer timer(io, boost::posix_time::seconds(3));
		timer.async_wait(&print);
		io.run();
		std::cout<<"finished"<<std::endl;
		system("pause");
		return 0;
	}
}

namespace two_async_op
{

	using namespace boost::asio;
	int main()
	{
		io_service ioservice;
		deadline_timer timer1(ioservice, boost::posix_time::seconds(3));
		timer1.async_wait([](const boost::system::error_code &ec)
		{int k=200; while(k--) {std::cout<<"tid 1, 3 s\n";}});

		deadline_timer timer2(ioservice, boost::posix_time::seconds(3));
		timer2.async_wait([](const boost::system::error_code &rc)
		{int k=200; while(k--) {std::cout<<"tid 2, 3 s\n";}});

		ioservice.run();
		system("pause");
		return 0;
	}
}

namespace multhread_async_op
{
	using namespace boost::asio;
	int main()
	{
		io_service ioservice;
		deadline_timer timer1(ioservice, boost::posix_time::seconds(3));
		timer1.async_wait([](const boost::system::error_code &ec)
		{int k=200; while(k--) {std::cout<<"tid 1, 3s\n";}});

		deadline_timer timer2(ioservice, boost::posix_time::seconds(3));
		timer2.async_wait([](const boost::system::error_code &ec)
		{int k=200; while(k--) {std::cout<<"tid 2, 3s\n";}});

		boost::thread thread1([&ioservice]() {ioservice.run();});
		boost::thread thread2([&ioservice]() {ioservice.run();});

		std::cout<<"test\n";
		//thread1.join();
		//thread2.join();
		system("pause");
		return 0;
	}
}

namespace web_client
{
	using namespace boost::asio;
	using namespace boost::asio::ip;

	io_service ioservice;
	tcp::resolver resolv(ioservice);
	tcp::socket tcp_socket(ioservice);
	boost::array<char, 4096> bytes;

	void read_handler(const boost::system::error_code &ec,
		std::size_t bytes_transfered)
	{
		if(!ec) {
			std::cout.write(bytes.data(), bytes_transfered);
			tcp_socket.async_read_some(buffer(bytes),read_handler);
		} else {
			std::cout<<ec.message()<<std::endl;
		}
	}

	void connect_handler(const boost::system::error_code &ec)
	{
		if(!ec) {
			std::string r = 
				"GET /HTTP/1.1\r\nHost: theboostcpplibraries.com\r\n\r\n";
			write(tcp_socket, buffer(r));
			tcp_socket.async_read_some(buffer(bytes), read_handler);
		} else {
			std::cout<<ec.message()<<std::endl;
		}
	}

	void resolve_handler(const boost::system::error_code &ec,
		tcp::resolver::iterator it)
	{
		if(!ec) {
			tcp_socket.async_connect(*it, connect_handler);
		} else {
			std::cout<<ec.message()<<std::endl;
		}
	}

	int main()
	{
		tcp::resolver::query q("theboostcpplibraries.com","http");
		resolv.async_resolve(q, resolve_handler);
		ioservice.run();
		system("pause");
		return 0;
	}
}

namespace udp_receiver
{
	int main()
	{
		try
		{
			boost::asio::io_service ioservice;
			boost::asio::ip::address addr(boost::asio::ip::address::from_string("10.1.3.104"));
			boost::asio::ip::udp::endpoint listen_endpoint(addr, 5555);
			boost::asio::ip::udp::socket sock(ioservice, listen_endpoint);
			int msg_cnt = 0;
			for(;;) {
				char buf[4096];
				boost::system::error_code ec;
				std::size_t receive_length = sock.receive(boost::asio::buffer(buf));
				std::cout << std::to_string((long long )receive_length) << " " << (unsigned short)buf[0] << " " << msg_cnt++ << std::endl;
			}
		}
		catch(std::exception &e)
		{
			std::cerr << e.what() << std::endl;
		}
		getchar();
		return 0;
	}
}