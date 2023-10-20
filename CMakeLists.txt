cmake_minimum_required(VERSION 3.10)
project(MyAsioServer)

set(CMAKE_BUILD_TYPE Debug)

set(BOOST_ROOT "/opt/boost_debug")
set(Boost_INCLUDE_DIR "/opt/boost_debug/include")
set(Boost_LIBRARY_DIR "/opt/boost_debug/lib")

find_package(Boost 1.65.1 COMPONENTS filesystem system REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
find_package(nlohmann_json REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})

add_executable(BCServer bc_server.cpp)

target_link_libraries(BCServer 
                     ${Boost_LIBRARIES}
                      nlohmann_json::nlohmann_json)

add_executable(my_program main.cpp)
target_link_libraries(my_program Boost::filesystem)