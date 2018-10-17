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

using namespace std;

int main () {
    //  Prepare our context and socket
    zmq::context_t context (1);
    zmq::socket_t socket (context, ZMQ_REP);
    socket.bind ("tcp://*:5555");
    int count=0;
    while (true) {
        zmq::message_t request;

        //  Wait for next request from client
        socket.recv (&request); //阻塞在这个地方，等待消息的到来
        string res ((char *)request.data());
        for(int i=0;i<(int)res.size();++i){
            if(res[i]=='\n'){
                cout<<"have another line mark"<<endl;
            }
            if(res[i]==' '){ //除了客户端发送内容外，后面还跟着两个未知的字符，然后又跟了一个socket-type的内容。过一段时间未知字符消失。
                cout<<"have blank in word"<<endl;
            }
            //之所以末尾有奇怪的东西，是因为发的时候长度不够，没有留下一个\0的位置。没有结尾，所以收到的会变长。
            cout<<res[i]<<endl;
            cout<<"i is "<<i<<endl;
        }
        std::cout << "Received |" << res <<"| size is "<<res.size()<< std::endl;
        cout<<"have received count is"<<count<<endl;
        count++;
        //  Do some 'work'
        sleep(1);

        //  Send reply back to client
        zmq::message_t reply (6);
        memcpy (reply.data (), "World\0", 6);      
        socket.send (reply); //回响应，具体回哪个地址哪个端口也没说，反正就是回了
    }
    return 0;
}