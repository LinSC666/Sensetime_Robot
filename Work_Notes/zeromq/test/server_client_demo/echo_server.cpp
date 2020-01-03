
#include</home/linsc/FSEC/cppzmq/zmq.hpp>
    #include <assert.h>
     
    int main () {
        zmq::context_t context (1);
        zmq::socket_t socket (context, ZMQ_REP);
        socket.bind("tcp://*:5555"); //bind
     
        int data_size = 4096;
        char buff[4*1024*1024] = "";
        zmq::message_t reply (buff, sizeof(buff), NULL, NULL);
        for(;;) {
            reply.rebuild(buff, sizeof(buff), NULL, NULL);
            assert(socket.recv (&reply, 0)); //recive
            assert(socket.send (reply));   //send
        }
        return 0;
    }
