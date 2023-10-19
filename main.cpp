#include <iostream>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;

int main() {
    try {
        boost::asio::io_service io_service;

        tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), 8080));

        for (;;) {
            tcp::socket socket(io_service);
            acceptor.accept(socket);

            std::string data = "Hello from ASIO server!\n";
            boost::system::error_code ignored_error;
            boost::asio::write(socket, boost::asio::buffer(data), ignored_error);
        }
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
