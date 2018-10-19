//
//  Hello World client in C++
//  Connects REQ socket to tcp://localhost:5555
//  Sends "Hello" to server, expects "World" back
//
#include <zmq.hpp>
#include <string>
#include <iostream>
#include <sstream>

using namespace std;

string int_to_string(int x){
    stringstream ss;
    ss<<x;
    string res;
    ss>>res;
    return res;
}

int main ()
{
    //  Prepare our context and socket
    zmq::context_t context (1);
    zmq::socket_t socket (context, ZMQ_REQ);

    std::cout << "Connecting to hello world server…" << std::endl;
    socket.connect ("tcp://localhost:5555");

    //  Do 10 requests, waiting each time for a response
    for (int request_nbr = 0; request_nbr != 1000; request_nbr++) {
        string req;
        req = "Hello";
        string numS = int_to_string(request_nbr);
        req = req+numS;
        req=req;      
        int reqSize = req.size();
        zmq::message_t request (reqSize+1); //这里必须+1留一个赋予给\0，string结尾是否有\0不同编译器貌似不一样，留一个位置就没bug了。
        memcpy (request.data (), req.c_str(), reqSize+1); //内容拷贝到request中
        string res = static_cast<char *>(request.data());
        std::cout << "Sending Hello " << req << "and req size is "<< req.size() << std::endl;
        socket.send (request); //利用socket发送

        //  Get the reply.
        zmq::message_t reply;
        socket.recv (&reply);  //接受消息，具体哪个端口接受消息？没说
        string res2 ((char *)reply.data());
        for(int i=0;i<(int)res2.size();++i){
            if(res2[i]=='\n'){
                cout<<"have another line mark"<<endl;
            }
            if(res2[i]==' '){ //除了客户端发送内容外，后面还跟着两个未知的字符，然后又跟了一个socket-type的内容。过一段时间未知字符消失。
                cout<<"have blank in word"<<endl;
            }
            cout<<res2[i]<<endl;
            cout<<"i is "<<i<<endl;
        }  
        std::cout << "Received World " << request_nbr<<"reply from server is "<< res2 << std::endl;
    }
    return 0;
}