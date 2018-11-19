#最低版本需求
cmake_minimum_required(VERSION 2.6)

PROJECT(client)

SET(SRC_LIST client.cpp)

#build路径以及source路径
MESSAGE(STATUS "THIS IS BINARY DIR" ${client_BINARY_DIR})
MESSAGE(STATUS "THIS IS SOURCE DIR" ${client_SOURCE_DIR})

#引入头文件
INCLUDE_DIRECTORIES(/home/lqx/zmq/include)


#引入库文件
LINK_DIRECTORIES(/home/lqx/zmq/lib)


#必须在前面，否则TARGET_LINK_LIBIRARIES找不到
ADD_EXECUTABLE(client ${SRC_LIST})

#引入库文件名
#原先命令 g++ -g -Wall -fPIC -I/home/lqx/zmq/include -L/home/lqx/zmq/lib -lzmq client.cpp -o client
TARGET_LINK_LIBRARIES(client zmq)