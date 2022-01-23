#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;
using namespace std;

int main()
{
	try
	{
		// �⺻������ Boost Asio ���α׷��� �ϳ��� IO Service ��ü�� ����.
		boost::asio::io_service io_service;
		// ������ �̸��� TCP ���������� �ٲٱ� ���� Resolver�� ���.
		tcp::resolver resolver(io_service);
		// �����δ� ���� ����, ���񽺴� daytime ���������� ����.
		tcp::resolver::query query("localhost", "daytime");
		// DNS�� ��ó IP �ּ� �� ��Ʈ ��ȣ�� ����.
		tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
		// ���� ��ü�� �ʱ�ȭ �Ͽ� ������ ����.
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