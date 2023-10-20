#include <boost/asio.hpp>
#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>
#include <boost/asio.hpp>
#include <boost/interprocess/sync/file_lock.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>


using namespace boost::asio;
using namespace boost::asio::ip;


namespace ns
{
    struct ServerConfig
    {
        std::string host = "127.0.0.1";
        int port = 5000;
        int timeout = 60;

        ServerConfig() = default;
        ServerConfig(std::string host_, int port_, int timeout_)
            : host(std::move(host_)), port(port_), timeout(timeout_)
        {}
    };

    NLOHMANN_DEFINE_TYPE_NON_INTRUSIVE(ServerConfig, host, port, timeout)
}



#if 0
int main()
{
    // Load settings from a JSON file
    std::ifstream settings_file("path/to/your/settings.json");
    nlohmann::json config;

    settings_file >> config;

    ns::ServerConfig bc_config = config["BCServer"].get<ns::ServerConfig>();
    ns::ServerConfig rts_config = config["RTS"].get<ns::ServerConfig>();

    settings_file.close();


    return 0;
}
#endif

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
    std::ifstream settings_file("settings.json");
    nlohmann::json config;
    settings_file >> config;

    ns::ServerConfig bc_config = config["BCServer"].get<ns::ServerConfig>();
    ns::ServerConfig rts_config = config["RTS"].get<ns::ServerConfig>();

    settings_file.close();

    try {
        boost::asio::io_context io_context;

        tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), bc_config.port));

        std::cout << "Server is running on port " << bc_config.port << std::endl;

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
