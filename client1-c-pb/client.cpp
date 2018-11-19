//  Hello World client
#include <zmq.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#include <iostream>
#include <string>


#include "test.pro.pb.h"

int main (void)
{
    //printf ("Connecting to hello world server…\n");
    void *context = zmq_ctx_new ();
    void *requester = zmq_socket (context, ZMQ_REQ);
    zmq_connect (requester, "tcp://localhost:5555");

    int request_nbr;
    for (request_nbr = 0; request_nbr != 10; request_nbr++) {
        char buffer [10];
        //printf ("Sending Hello %d…\n", request_nbr);
        std::string sendstring;
        

        //pb
        tutorial::Person person;
        person.set_name("liqixin");
        person.set_id(381);
        person.set_email("835347829@qq.com");
        person.SerializeToString(&sendstring);
        //pb
        char * sendstr =(char *)sendstring.c_str();
        //zmq_send (requester, "Hello", 5, 0);
        //这个地方很可能是结尾到底有没有/0造成的问题。如果size没有加1，zmq会在后面加一个结尾。而且这个结尾是瞎加的。所以size+1是最合适的。
        zmq_send (requester, sendstr, sendstring.size()+1, 0);//这个地方很神奇，如果size+1，那么收到的反而是5的长度。不加1，收到的就是6的长度。
        zmq_recv (requester, buffer, 10, 0);
        //printf ("Received World %d\n", request_nbr);
        std::string res(buffer); //收到字符串的时候，即使服务端返回的长度是5，末尾会多一个未知的字符。
        std::cout<<"res is "<<res<<std::endl;
        // for(int i=0;i<res.size();i++){
        //     std::cout<<"res[i] is "<<res[i]<<std::endl;
        // }
        std::cout<<"res size is "<<res.size()<<std::endl;
    }
    zmq_close (requester);
    zmq_ctx_destroy (context);
    return 0;
}