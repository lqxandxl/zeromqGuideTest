#include <zmq.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>

#include <iostream>
#include <string>

int main (void)
{
    //  Socket to talk to clients
    void *context = zmq_ctx_new ();
    void *responder = zmq_socket (context, ZMQ_REP);
    int rc = zmq_bind (responder, "tcp://*:5555");
    assert (rc == 0);

    while (1) {
        char buffer [10];
        zmq_recv (responder, buffer, 10, 0);
        std::string res(buffer);
        std::cout<<"res size is "<<res.size()<<std::endl;
        // for(int i=0;i<res.size();i++){
        //     std::cout<<"res[i] is "<<res[i]<<std::endl;
        // }
        std::cout<<"res is "<<res<<std::endl;
        //printf ("Received Hello\n");
        sleep (1);          //  Do some 'work'
        zmq_send (responder, "World", 5+1 , 0);
    }
    return 0;
}