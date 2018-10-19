#include <iostream>
#include <string>


#include "zhelpers.h" //该有的库都包括了
//#define randof(num) (int) ((float) num * random () / (RAND_MAX + 1.0))

int main (void)
{
    //  Prepare our context and publisher
    void *context = zmq_ctx_new ();
    void *publisher = zmq_socket (context, ZMQ_PUB);
    int rc = zmq_bind (publisher, "tcp://*:5556");
    assert (rc == 0);

    //  Initialize random number generator
    srandom ((unsigned) time (NULL));
    int count=0;
    while (1) {
        //  Get values that will fool the boss
        int zipcode, temperature, relhumidity;
        zipcode     = randof (100000);
        temperature = randof (215) - 80;
        relhumidity = randof (50) + 10;

        //  Send message to all subscribers
        char update [20];
        sprintf (update, "%05d %d %d", zipcode, temperature, relhumidity);
        //程序逻辑是这样的，有订阅者进行订阅，server作为推送者，会把消息进行推送，而消息是一个随机数字 温度 还有一个数字 中间用空格分开
        //订阅者只订阅开头是10001的消息，如果有的话，那么就会收到。
        if(count%1000==0){
            std::string sendstring(update);
            std::cout<<"send string is "<<sendstring<<std::endl;
            std::cout<<"send string size is "<<sendstring.size()<<std::endl;
            std::cout<<"count is "<<count<<std::endl;
        }
        s_send (publisher, update);
        count++;
        int max = 0x7fffffff;
        if(count==max){
            count=0;
        }
        //sleep(1); // sleep
        //s_send是什么 这个在guide中指明了，为了安全封装了一层接口，only c可以享受
        //s_send封装在了zhelpers.h中
        //查看地址 https://github.com/booksbyus/zguide/blob/master/examples/C/zhelpers.h
        // std::string sendstring(update);
        // char * sendstr = (char *)sendstring.c_str();
        // zmq_send (publisher, sendstr, sendstring.size()+1, 0);
    }
    zmq_close (publisher);
    zmq_ctx_destroy (context);
    return 0;
}