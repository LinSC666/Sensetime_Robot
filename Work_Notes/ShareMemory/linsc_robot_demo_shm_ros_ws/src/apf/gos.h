#ifndef __PUB_SUB_H//作用：防止graphics.h被重复引用
#define __PUB_SUB_H
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <semaphore.h>
#include <fcntl.h>
#include <vector>
#include <fstream> // ifstream, ifstream::in
//#include <opencv2/opencv.hpp>
#include <iostream>
//#include <CCFileUtils.h>

//*********************//
//捕获ctrl+c
#include <signal.h>
//*********************//

//*********************//
//进行多线程处理同步
#include <mutex>
#include <thread>
//*********************//

//*********************//
//msg protobuf
//#include "msg_pic.pb.h"
//#include "velocity_msg_.pb.h"
//*********************//
//#include <nlohmann/json.hpp> // https://github.com/nlohmann/json/tree/develop/single_include/nlohmann/json.hpp
//**********************//
//boost
#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <boost/interprocess/ipc/message_queue.hpp>

#include <boost/lockfree/queue.hpp> // ring buffer

#include <boost/interprocess/allocators/allocator.hpp>
//#include <boost/interprocess/containers/string.hpp>
#include <chrono>
#include <time.h>
#include <memory>

//**************************************************************************************//
//Linux shareMemory communication
//gos.h  && 捕获ctrl+c  &&  进行多线程处理同步 && 进行protobuf数据序列化 && 图像订阅与发布
//&&共享链接库　&& 多话题节点同时订阅
//LinSC
//2020/2/29
//**************************************************************************************//

namespace gos
{
    
    class Publisher
    {
     // template <typename M> 
      
    public:
        Publisher();
        ~Publisher() = default;

       //template <class T> 
      template <typename M> 
      int advertiser(const std::string& topic_name,const std::string& config_file_name);
      template <typename M> 
      void publish(M& sendBuf);
      //template <typename M>
      //M serialize_msg;
      

    private:
      size_t id_;
      size_t message_seq_;
      std::vector<std::string> json_queues_;

    //  std::deque<std::pair<std::string, std::string>> pools;
    // boost::interprocess::managed_shared_memory shm_pool;

      std::string pool_name_;
      int add_pool_num;
      std::string gobal_pool_name_;
     // std::unique_ptr<boost::interprocess::managed_shared_memory> pool_;
      
    private:
      static size_t id_counter_;
    };

  template <typename T>  
  class Subscriber
    {
      T deserialize_msg;
    //private:
    public:
       
     //  int subscribe(const char *topics_name,const char *queue_name,void (*pCallback)(const T));
       int subscribe(const char *topics_name,const char *queue_name, std::function<void( T&)> call_back_);
      /* template <typename Type, typename F>
       int subscribe(const std::string& topic_name, const std::string& queue_name, F f) {
       Type t;
       f(t);
       }
       */

    };

/*   
    class test
    {
    private:
      demo::msg reader;

    public:
       template <typename T>
       void print(const T&a);
       
    };
*/
     
  /*  class NodeHandle
    {
    public:
      Publisher advertise(AdvertiseOptions& ops);

    }
   */
}
 
//int advertiser();
#endif
