#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <zmq.h>


#include <time.h>
#include <sys/time.h>
#include <iostream>

long long int num=0;

int main()
{
    printf("sub!\n");

    void* context = zmq_ctx_new();/// 创建一个新的环境
    assert(context != NULL);

    int ret = zmq_ctx_set(context, ZMQ_MAX_SOCKETS, 1);/// 该环境中只允许有一个socket的存在
    assert(ret == 0);

    void* subscriber = zmq_socket(context, ZMQ_SUB);/// 创建一个订阅者
    assert(subscriber != NULL);

    ret = zmq_connect(subscriber, "tcp://localhost:8888");/// 连接到服务器
    assert(ret == 0);

    ret = zmq_setsockopt(subscriber, ZMQ_SUBSCRIBE, "", 0);/// 必须添加该语句对消息滤波，否则接受不到消息
    assert(ret == 0);

    char buf[16];/// 消息缓冲区

    struct timeval tstart;
    gettimeofday (&tstart, NULL);
    int task_nbr;
    int total_msec = 0;     // 定义一个时间点

    while(1)
    {
        ret = zmq_recv(subscriber, buf, 16, ZMQ_DONTWAIT);/// 接收消息，非堵塞式
    /*    if (ret != -1)/// 打印消息
        {
            buf[ret] = '\0';
            printf("%s\n", buf);
        }
        sleep(1);
     */
        if (ret != -1)/// 打印消息
        {
		num++;
		if(num>=1000000)
		{
		    std::cout << "start_ZMQ_linsc_effiency_test!!!..." << std::endl;
		    break;
		}
	}
    }

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



