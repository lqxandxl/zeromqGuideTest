//
//  Hello World client in C++
//  Connects REQ socket to tcp://localhost:5555
//  Sends "Hello" to server, expects "World" back
//
#include <zmq.hpp>
#include <string>
#include <iostream>

int main ()
{
    //  Prepare our context and socket
    zmq::context_t context (1);
    zmq::socket_t socket (context, ZMQ_REQ);

    std::cout << "Connecting to hello world server…" << std::endl;
    socket.connect ("tcp://localhost:5555");

    //  Do 10 requests, waiting each time for a response
    for (int request_nbr = 0; request_nbr != 1000; request_nbr++) {
        zmq::message_t request (5);
        memcpy (request.data (), "Hello", 5); //内容拷贝到request中
        std::cout << "Sending Hello " << request_nbr << "…" << std::endl;
        socket.send (request); //利用socket发送

        //  Get the reply.
        zmq::message_t reply;
        socket.recv (&reply);  //接受消息，具体哪个端口接受消息？没说
        std::cout << "Received World " << request_nbr << std::endl;
    }
    return 0;
}