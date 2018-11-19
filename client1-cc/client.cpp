//  Hello World client
#include <zmq.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#include <iostream>
#include <string>
using namespace std;

int main (void)
{
    //printf ("Connecting to hello world server…\n");
    void *context = zmq_ctx_new ();
    void *requester = zmq_socket (context, ZMQ_REQ);
    zmq_connect (requester, "tcp://localhost:5555");

    int request_nbr;
    for (request_nbr = 0; request_nbr != 10; request_nbr++) {
        char buffer [10];
        std::string sendstring;
        sendstring = "hello liqixin my name is fsc";
        int len1 = sendstring.size();
        cout<<"sendstr length is"<<len1<<endl;
        char * sendstr =(char *)sendstring.c_str();
        //zmq_send (requester, "Hello", 5, 0);
        zmq_send (requester, sendstr, sendstring.size(), 0);
        zmq_recv (requester, buffer, 10, 0);
        std::string res(buffer); //收到字符串的时候，即使服务端返回的长度是5，末尾会多一个未知的字符。
        std::cout<<"res is "<<res<<std::endl;
        std::cout<<"res size is "<<res.size()<<std::endl;
    }
    zmq_close (requester);
    zmq_ctx_destroy (context);
    return 0;
}