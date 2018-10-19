//  Weather update client
//  Connects SUB socket to tcp://localhost:5556
//  Collects weather updates and finds avg temp in zipcode

#include "zhelpers.h"
#include <string>
#include <iostream>

int main (int argc, char *argv [])
{
    //  Socket to talk to server
    printf ("Collecting updates from weather server…\n");
    void *context = zmq_ctx_new ();
    void *subscriber = zmq_socket (context, ZMQ_SUB);
    int rc = zmq_connect (subscriber, "tcp://localhost:5556");
    assert (rc == 0);

    //  Subscribe to zipcode, default is NYC, 10001
    char *filter =(char *) ((argc > 1)? argv [1]: "10001 "); //const char * to char * add by liqixin 2018-10-19
    rc = zmq_setsockopt (subscriber, ZMQ_SUBSCRIBE,
                         filter, strlen (filter));
    assert (rc == 0);

    //  Process 100 updates
    int update_nbr;
    long total_temp = 0;
    //client收集1000个数据就停止 计算总结果。如果没有收到想要的消息，那么就阻塞在了s_recv
    for (update_nbr = 0; update_nbr < 1000; update_nbr++) {
        char *s1 = s_recv (subscriber);
        std::string res(s1); //char * to string
        std::cout<<"res size is "<<res.size()<<std::endl;
        std::cout<<"res is "<<res<<std::endl;
        int zipcode, temperature, relhumidity;
        sscanf (s1, "%d %d %d",
            &zipcode, &temperature, &relhumidity);
        total_temp += temperature;
        free (s1);
    }
    printf ("Average temperature for zipcode '%s' was %dF\n",
        filter, (int) (total_temp / update_nbr));

    zmq_close (subscriber);
    zmq_ctx_destroy (context);
    return 0;
}