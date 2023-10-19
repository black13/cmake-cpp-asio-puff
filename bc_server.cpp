#include <boost/asio.hpp>
#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>

using boost::asio::ip::tcp;

int main() {
    // Load settings from a JSON file
    std::ifstream json_file("settings.json");
    nlohmann::json config;
    json_file >> config;

    std::string bc_host = config["BCServer"]["host"];
    int bc_port = config["BCServer"]["port"];
    int bc_timeout = config["BCServer"]["timeout"];

    try {
        boost::asio::io_context io_context;

        tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), bc_port));

        std::cout << "Server is running on port " << bc_port << std::endl;

        for (;;) {
            tcp::socket socket(io_context);
            acceptor.accept(socket);

            std::string message = "Hello from server";
            boost::system::error_code ignored_error;
            boost::asio::write(socket, boost::asio::buffer(message), ignored_error);
        }
    }
    catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
