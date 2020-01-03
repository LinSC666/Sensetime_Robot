
#include</home/linsc/FSEC/cppzmq/zmq.hpp>
#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdio.h>
 
long long int gettime(){
    struct timeval tv = {0, 0};
    gettimeofday(&tv, NULL);
    return tv.tv_sec * 1000000 + tv.tv_usec;
}
 
int main (int argc, char *argv[]) {
    if(argc != 4){
        printf("Usage:%s <message_size> <total_count> <server_host>\n", argv[0]);
        return -1;
    }
    int message_size = atoi(argv[1]);
    int total_count = atoi(argv[2]);
    char *server_host = argv[3];
    zmq::context_t context (3);
    zmq::socket_t socket (context, ZMQ_REQ);
    socket.connect(server_host) ; //tcp连接到server端
 
    std::string data; //构造传输消息
    for(int i=0; i<message_size; i++){
        data.append("A");
    }
    int data_size = data.size();
    zmq::message_t request((void *)data.c_str(), data_size, NULL);
    zmq::message_t reply (data_size);
    long long int start = gettime();
    for(int i=0; i<total_count; i++) {
        request.rebuild((void *)data.c_str(), data_size, NULL);
        socket.send (request); //send data to server
        reply.rebuild(data_size);
        socket.recv (&reply, 0);//recive data from server
    }
    long long int end = gettime();
    long long total_time = end - start;
    printf("message_size=%d total_count=%ld total_time=%ldus qps=%lf rt=%lfus band_width=%ldM\n", message_size, total_count, total_time, (double)(total_count/(total_time/1000000)), (double)(total_time/total_count), (data_size*total_count)/(total_time/1000000)/(1024*1024));
    return 0;
 
}

