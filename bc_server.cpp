#include <boost/asio.hpp>
#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>
#include <boost/asio.hpp>
#include <boost/interprocess/sync/file_lock.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>


using boost::asio::ip::tcp;


int main() {

 const std::string lock_file_path = "/tmp/bcserver.lock";

    std::ofstream lock_stream;
    lock_stream.open(lock_file_path.c_str(), std::ios_base::app); // Create or open lock file
    if (!lock_stream.is_open()) {
        std::cerr << "Could not open lock file." << std::endl;
        return 1;
    }

    // Create file lock
    boost::interprocess::file_lock file_lock(lock_file_path.c_str());

    // Try to acquire lock
    if (!file_lock.try_lock()) {
        std::cerr << "Another instance is running. Exiting." << std::endl;
        return 1;
    }
    
    // Now this program holds the lock. It will be released when the program terminates.
    std::cout << "Acquired lock. Press Enter to exit..." << std::endl;
    std::cin.get();


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
