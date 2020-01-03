#include <zmq.hpp>
#include <time.h>
#include <sys/time.h>
#include <iostream>

//************************************************//
//  任务收集器
//  绑定PULL套接字至tcp://localhost:5558端点
//  从worker处收集处理结果
//************************************************//

int main (int argc, char *argv[])
{
    //  准备上下文和套接字
    zmq::context_t context(1);
    zmq::socket_t receiver(context,ZMQ_PULL);
    receiver.bind("tcp://*:5558");

    //  等待开始信号
    zmq::message_t message;
    receiver.recv(&message);

    //  开始计时
    struct timeval tstart;
    gettimeofday (&tstart, NULL);

    //  确定100个任务均已处理
    int task_nbr;
    int total_msec = 0;     // 时间统计
    for (task_nbr = 0; task_nbr < 100; task_nbr++) {

        receiver.recv(&message);
        if (task_nbr % 10 == 0)
            std::cout << ":" << std::flush;
        else
            std::cout << "." << std::flush;
    }
    //  计算并输出总执行时间
    struct timeval tend, tdiff;
    gettimeofday (&tend, NULL);

    if (tend.tv_usec < tstart.tv_usec) {
        tdiff.tv_sec = tend.tv_sec - tstart.tv_sec - 1;
        tdiff.tv_usec = 1000000 + tend.tv_usec - tstart.tv_usec;
    }
    else {
        tdiff.tv_sec = tend.tv_sec - tstart.tv_sec;
        tdiff.tv_usec = tend.tv_usec - tstart.tv_usec;
    }
    total_msec = tdiff.tv_sec * 1000 + tdiff.tv_usec / 1000;
    std::cout << "\nTotal elapsed time: " << total_msec << " msec\n" << std::endl;
    return 0;
}



