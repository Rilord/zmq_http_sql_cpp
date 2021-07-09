cmake_minimum_required(VERSION 3.0)

project(PUB_SUB_CLIENT LANGUAGES CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")

# BOOST

set(Boost_USE_STATIC_LIBS ON)
find_package(Boost COMPONENTS program_options REQUIRED)
include_directories(${BOOST_INCLUDE_DIRS})

# ZMQ LIBRARY


add_subdirectory(vendor/zmqpp-4.2.0 ${ZEROMQ_INCLUDE_DIR})
include_directories(vendor/zmqpp-4.2.0/src)

# HTTP LIBRARY
add_subdirectory(vendor/cpp-httplib-0.9.0 vendor/cpp-httplib-0.9.0)

add_executable(client_app client.cpp data_client.cpp data_client.h record.h record.cpp)

target_link_libraries(client_app zmqpp ${ZeroMQ_LIBRARY} ${Boost_LIBRARIES} httplib)
