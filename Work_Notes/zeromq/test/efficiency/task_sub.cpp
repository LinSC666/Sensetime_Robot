#include "/home/linsc/SenseTime_robot/zeromq/zhelpers.h"
#include <string>
//**********************************//
//  任务执行器
//  连接PULL套接字至tcp://localhost:5557端点
//  从任务分发器处获取任务
//  连接PUSH套接字至tcp://localhost:5558端点
//  向结果采集器发送结果
//**********************************//

int main (int argc, char *argv[])
{
    zmq::context_t context(1);

    //  获取任务的套接字
    zmq::socket_t receiver(context, ZMQ_PULL);
    receiver.connect("tcp://localhost:5557");

    //  发送结果的套接字
    zmq::socket_t sender(context, ZMQ_PUSH);
    sender.connect("tcp://localhost:5558");

    //  循环处理任务
    while (1) {

        zmq::message_t message;
        int workload;         

        receiver.recv(&message);
        std::string smessage(static_cast<char*>(message.data()), message.size());
	
	//  输出处理进度
        std::istringstream iss(smessage);
        iss >> workload;

        //  开始处理
        s_sleep(workload);

        //  发送结果
        message.rebuild();//释放＝＝free
        sender.send(message);

        //  打印结果到终端
        std::cout << "." << std::flush;
    }
    return 0;
}



