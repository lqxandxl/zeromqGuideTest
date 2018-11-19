#include <zmq.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>

#include <iostream>
#include <string>

using namespace std;

int main (void)
{
    //  Socket to talk to clients
    void *context = zmq_ctx_new ();
    void *responder = zmq_socket (context, ZMQ_REP);
    int rc = zmq_bind (responder, "tcp://*:5555");
    assert (rc == 0);


    while (1) {
        char buffer [100];
        int index = zmq_recv (responder, buffer, 100, 0);
        std::string res(buffer);
        cout<<"zmq_recv res is "<<index<<endl;  //same 28
        buffer[index] = 0;
        std::cout<<"res size is "<<res.size()<<std::endl;  // 28
        // for(int i=0;i<res.size();i++){
        //     std::cout<<"res[i] is "<<res[i]<<std::endl;
        // }
        std::cout<<"res is "<<res<<std::endl;

        //printf ("Received Hello\n");
        sleep (1);          //  Do some 'work'
        


	    zmq_send (responder, "World",5, 0);
    }
    return 0;
}
