#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;
using namespace std;

int main()
{
	try
	{
		// 기본적으로 Boost Asio 프로그램은 하나의 IO Service 객체를 가짐.
		boost::asio::io_service io_service;
		// 도메인 이름을 TCP 종단점으로 바꾸기 위해 Resolver를 사용.
		tcp::resolver resolver(io_service);
		// 서버로는 로컬 서버, 서비스는 daytime 프로토콜을 적음.
		tcp::resolver::query query("localhost", "daytime");
		// DNS를 거처 IP 주소 및 포트 번호를 얻어옴.
		tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
		// 소켓 객체를 초기화 하여 서버에 연결.
		tcp::socket socket(io_service);
		boost::asio::connect(socket, endpoint_iterator);

		while(1)
		{
			boost::array<char, 128> buf;
			boost::system::error_code error;
			size_t len = socket.read_some(boost::asio::buffer(buf), error);
			if (error == boost::asio::error::eof)
				break;
			else if (error)
				throw boost::system::system_error(error);

			cout.write(buf.data(), len);
		}
	}
	catch (exception& e)
	{
		cerr << e.what() << endl;
	}

	system("pause");
	return 0;
}