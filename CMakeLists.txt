SET(execName AVRSocket)
CMAKE_MINIMUM_REQUIRED(VERSION 2.4)
PROJECT(${execName})

find_package(Boost COMPONENTS system thread REQUIRED)

include_directories(${Boost_INCLUDE_DIR})

add_definitions(-std=c++11 -g -O3)

ADD_EXECUTABLE(client test_client.cc AVRClient.cc AVRServer.cc)

ADD_EXECUTABLE(server test_server.cc AVRClient.cc AVRServer.cc)


TARGET_LINK_LIBRARIES(client
    ${Boost_LIBRARIES} )

TARGET_LINK_LIBRARIES(server
    ${Boost_LIBRARIES} )