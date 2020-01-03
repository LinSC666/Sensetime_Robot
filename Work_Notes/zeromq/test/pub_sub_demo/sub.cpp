
#include <zmq.hpp>
#include <iostream>
#include <sstream>

//************************************//
// 连接SUB套接字至tcp://*:5556端点
//  收集指定邮编的气象信息，并计算平均温度
//************************************//

int main (int argc, char *argv[])
{
    zmq::context_t context (1);

    //  Socket to talk to server,创建连接至服务端的套接字
    std::cout << "Collecting updates from weather server...\n" << std::endl;
    zmq::socket_t subscriber (context, ZMQ_SUB);
    subscriber.connect("tcp://localhost:5556");

    //  Subscribe to zipcode, default is NYC, 10001;设置订阅信息，默认为纽约，邮编10001
	const char *filter = (argc > 1)? argv [1]: "10001 ";
    subscriber.setsockopt(ZMQ_SUBSCRIBE, filter, strlen (filter));

    //  Process 100 updates
    //  处理100条更新信息,也是发送100个任务
    int update_nbr;
    long total_temp = 0;
    for (update_nbr = 0; update_nbr < 100; update_nbr++) {

        zmq::message_t update;
        int zipcode, temperature, relhumidity;

        subscriber.recv(&update);

        std::istringstream iss(static_cast<char*>(update.data()));
	iss >> zipcode >> temperature >> relhumidity ;
		total_temp += temperature;
    }
    std::cout 	<< "Average temperature for zipcode '"<< filter
    			<<"' was "<<(int) (total_temp / update_nbr) <<"F"
    			<< std::endl;
    return 0;
}




