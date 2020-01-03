#include <zmq.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>

#define within(num) (int) ((float) num * random () / (RAND_MAX + 1.0))

//********************************************//
//  任务分发器
//  绑定PUSH套接字至tcp://localhost:5557端点
//  发送一组任务给已建立连接的worker
//********************************************//

int main (int argc, char *argv[])
{
    zmq::context_t context (1);

    //  用于发送消息的套接字
    zmq::socket_t  sender(context, ZMQ_PUSH);
    sender.bind("tcp://*:5557");

    std::cout << "Press Enter when the workers are ready: " << std::endl;
    getchar ();
    std::cout << "Sending tasks to workers...\n" << std::endl;

    //  The first message is "0" and signals start of batch
    //  用于发送开始信号的套接字
    zmq::socket_t sink(context, ZMQ_PUSH);
    sink.connect("tcp://localhost:5558");
    zmq::message_t message(2);
    //  开始信号为０
    memcpy(message.data(), "0", 1);
    sink.send(message);

    //  Initialize random number generator初始化随机数生成器
    srandom ((unsigned) time (NULL));

    //  发送100个任务
    int task_nbr;
    int total_msec = 0;     //  预计执行时间（毫秒）
    for (task_nbr = 0; task_nbr < 100; task_nbr++) {
        int workload;
        // 随机产生1-100毫秒的工作量
        workload = within (100) + 1;//这里的within==randof()!!!
        total_msec += workload;

        message.rebuild(10);//释放＝＝free
        memset(message.data(), '\0', 10);
        sprintf ((char *) message.data(), "%d", workload);
        sender.send(message);
    }
    std::cout << "Total expected cost: " << total_msec << " msec" << std::endl;
    sleep (1);  //  延迟一段时间，让任务分发完成

    return 0;
}


