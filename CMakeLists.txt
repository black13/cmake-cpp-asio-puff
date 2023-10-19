cmake_minimum_required(VERSION 3.10)
project(MyAsioServer)

set(CMAKE_BUILD_TYPE Debug)

set(BOOST_ROOT "/opt/boost_debug")
set(Boost_INCLUDE_DIR "/opt/boost_debug/include")
set(Boost_LIBRARY_DIR "/opt/boost_debug/lib")

find_package(Boost REQUIRED COMPONENTS system)
find_package(nlohmann_json REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})

add_executable(BCServer bc_server.cpp)

target_link_libraries(BCServer 
                     ${Boost_LIBRARIES}
                      nlohmann_json::nlohmann_json)
