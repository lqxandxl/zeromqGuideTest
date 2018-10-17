//
//  Hello World server in C++
//  Binds REP socket to tcp://*:5555
//  Expects "Hello" from client, replies with "World"
//
#include <zmq.hpp>
#include <string>
#include <iostream>
#ifndef _WIN32
#include <unistd.h>  //linux引用这个
#else
#include <windows.h>

#define sleep(n)    Sleep(n)
#endif

int main () {
    //  Prepare our context and socket
    zmq::context_t context (1);
    zmq::socket_t socket (context, ZMQ_REP);
    socket.bind ("tcp://*:5555");

    while (true) {
        zmq::message_t request;

        //  Wait for next request from client
        socket.recv (&request); //阻塞在这个地方，等待消息的到来
        std::cout << "Received Hello" << std::endl;

        //  Do some 'work'
        sleep(1);

        //  Send reply back to client
        zmq::message_t reply (5);
        memcpy (reply.data (), "World", 5);
        socket.send (reply); //回响应，具体回哪个地址哪个端口也没说，反正就是回了
    }
    return 0;
}