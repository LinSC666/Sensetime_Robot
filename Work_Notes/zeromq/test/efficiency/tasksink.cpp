#include <zmq.hpp>
#include <time.h>
#include <sys/time.h>
#include <iostream>

int main (int argc, char *argv[])
{
    zmq::context_t context(1);
    
    struct timeval tstart;
    gettimeofday (&tstart, NULL);


    int task_nbr;
    int total_msec = 0;     // 定义一个时间点

   //***************************************************//
   //测试任务：打印一百万条指令所花费时间
    for (task_nbr = 0; task_nbr < 10000000; task_nbr++) {

            std::cout << "ZMQ_linsc_effiency_test!!!..." << std::endl;
    }
   //***************************************************//

    struct timeval tend, tdiff;
    gettimeofday (&tend, NULL);//获取结束任务时间点

    if (tend.tv_usec < tstart.tv_usec) {
        tdiff.tv_sec = tend.tv_sec - tstart.tv_sec - 1;
        tdiff.tv_usec = 1000000 + tend.tv_usec - tstart.tv_usec;
    }
    else {
        tdiff.tv_sec = tend.tv_sec - tstart.tv_sec;
        tdiff.tv_usec = tend.tv_usec - tstart.tv_usec;
    }

    total_msec = tdiff.tv_sec * 1000 + tdiff.tv_usec / 1000;
    printf("\nTotal elapsed time: %d msec\n" ,total_msec);
    return 0;

}





