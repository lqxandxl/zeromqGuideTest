#最低版本需求
cmake_minimum_required(VERSION 2.6)

PROJECT(client)

SET(SRC_LIST client.cpp test.pro.pb.cc)

#build路径以及source路径
MESSAGE(STATUS "THIS IS BINARY DIR" ${client_BINARY_DIR})
MESSAGE(STATUS "THIS IS SOURCE DIR" ${client_SOURCE_DIR})

#引入头文件
INCLUDE_DIRECTORIES(/home/liqixin/zmq/include)
INCLUDE_DIRECTORIES(/home/liqixin/pb/include)
#引入库文件
LINK_DIRECTORIES(/home/liqixin/zmq/lib)
LINK_DIRECTORIES(/home/liqixin/pb/lib)
#必须在前面，否则TARGET_LINK_LIBIRARIES找不到
ADD_EXECUTABLE(client ${SRC_LIST})

#引入库文件名
#原先命令 g++ -g -Wall -fPIC -I/home/liqixin/zmq/include -L/home/liqixin/zmq/lib -lzmq client.cpp -o client
TARGET_LINK_LIBRARIES(client zmq protobuf protobuf-lite protoc)