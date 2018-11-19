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
    void *context = zmq_ctx_new ();
    void *requester = zmq_socket (context, ZMQ_REQ);
    zmq_connect (requester, "tcp://localhost:5555"); //类似unix编程，socket和地址进行了绑定

    int request_nbr;
    for (request_nbr = 0; request_nbr != 10; request_nbr++) {
        char buffer [10];
        std::string sendstring;
        sendstring = "hello liqixin my name is fsc";
        int len1 = sendstring.size();
        cout<<"sendstr length is"<<len1<<endl;
        char * sendstr =(char *)sendstring.c_str();
        zmq_send (requester, sendstr, sendstring.size(), 0); //发的时候原则是发多少，写多少的长度。
        int index = zmq_recv (requester, buffer, 10, 0); //收的原则是，留下足够大的缓冲区，然后在末尾加入null的结尾。
        buffer[index]=0;
        std::string res(buffer); 
        std::cout<<"res is "<<res<<std::endl;
    }
    zmq_close (requester);
    zmq_ctx_destroy (context);
    return 0;
}