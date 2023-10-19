/ Include statements for Boost.Asio and nlohmann/json
#include <boost/asio.hpp>
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>

// Function to read port from config.json
unsigned short read_port_from_config(const std::string& server_name) {
    std::ifstream config_file("config.json");
    nlohmann::json config_json;
    config_file >> config_json;

    return config_json[server_name]["port"];
}

// Main function
int main(int argc, char* argv[]) {
    unsigned short port = read_port_from_config("COMMS");  // Replace with "RT_GPS" or "RT_Comms" for other servers
    // ... (rest of your server code)
}
