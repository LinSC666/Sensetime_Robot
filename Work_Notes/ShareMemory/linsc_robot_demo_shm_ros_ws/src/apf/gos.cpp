#include "gos.h"
#include "nlohmann/json.hpp"
#include <boost/atomic.hpp>
//using json = nlohmann::json;
//**********************//

//***********************************************************************************************************//
//Linux shareMemory communication
//gos
//&& 捕获ctrl+c，若无，则终端直接结束的话，造成一些程序没运行就退出 
//&& 进行多线程处理同步(处理image和普通字符串，不同的while） 
//&& 信号量semaphore实现publish和subscribe进程同步，发才能收，保证一发一收.
//&& 进行protobuf数据序列化
//&& 生成动态链接库，供subscribe_mock_data和publish_mock_data其他单开的node的调用；
//LinSC

//2020/3/27
//***********************************************************************************************************//


using namespace boost::lockfree;
using namespace boost::interprocess;
using namespace std;
//using namespace cv;
using namespace gos;
//namespace bip = boost::interprocess;
using namespace std;

int cnum=0;

//*************************************//
//picture_topic
/*int picture_show=0;
int shmid_pic;
key_t key;
string sPicPath ;
char chBuf[1024*1024] = {0};        //这边可以控制图片的大小，1024 = 1KB， 1024*1024 = 1M
*/  
//*************************************//

//**************************************//
//protobuf
//char text11[TEXT_SZ];
//**************************************//
//int pub_flag=0;//only pub once
/*
#define chatter(name1)  chatter##name1
#define mmap(name2)  mmap##name2
#define chatter_add(name3)  chatter_add##name3
*/
std::vector<std::string> all_pool_name;
std::vector<std::string> all_json_queues;
//boost::interprocess::managed_shared_memory pool_;

//******************************************************************//
//message queue
typedef struct mq_share_st 
{
    char pool_name[30];
    char message_sequence[10]; 
}message_reference;
//******************************************************************//
//share_pool_memory
class shm_pool_st
{
public:
   // boost::atomic_int reference_counter;
    boost::atomic<int> reference_counter;
   //int reference_counter;
   char protobuf_msg[1024];
 /*   char protobuf_msg2[1024];
    char protobuf_msg3[1024];
    char protobuf_msg4[1024];
    char protobuf_msg5[1024];
    char protobuf_msg6[1024];
    char protobuf_msg7[1024];
    char protobuf_msg8[1024];
    char protobuf_msg9[1024];
*/
  //sem_t sem;
};
//******************************************************************//

namespace shm_queue
{
    typedef boost::lockfree::queue<message_reference, boost::lockfree::capacity<1>>que ;
}
//******************************************************************//

void Pub_exit_handler(int s){
      printf("Caught signal %d\n",s);
      for(size_t i=0;i<all_pool_name.size();i++)
      {
        shared_memory_object::remove(all_pool_name[i].c_str());
        //cout<<all_pool_name[i].c_str()<<endl;
      }
      for(size_t i=0;i<all_json_queues.size();i++)
      {
        message_queue::remove(all_json_queues[i].c_str());
        //cout<<all_json_queues[i].c_str()<<endl;
      }
      printf("\n\n");
      printf("------------END---------------\n");
      printf("------------------------------\n");
      printf("The Publisher is exit !!!\n");
      printf("Clean the memory Finshined !!!\n");
      printf("------------------------------\n");
      printf("------------------------------\n\n");
      exit(1);
}
void Sub_exit_handler(int s){
      printf("Caught signal %d\n",s);
      //running=0;

      printf("\n\n");
      printf("------------END---------------\n");
      printf("------------------------------\n");
      printf("The Subscriber is exit !!!\n");
      printf("Clean the memory Finshined !!!\n");
      printf("------------------------------\n");
      printf("------------------------------\n\n");
      exit(1);
}
//*************************************//
//template <typename M> 
size_t Publisher::id_counter_ = 0;
//template <typename M> 
Publisher::Publisher() : message_seq_(0) {
  id_ = id_counter_;
  cout<<"pub"+std::to_string(id_)<<"  "<<std::to_string(message_seq_)<<"\n\n"<<endl;
  ++id_counter_;
}
template <typename M> 
int Publisher::advertiser(const std::string& topic_name,const std::string& config_file_name)
{
      gobal_pool_name_=topic_name;
      add_pool_num=0;
      nlohmann::json json_obj;
      //cout<<Global_topic_name<<endl;
      // 从文件读取配置
      std::ifstream json_fin(config_file_name);   // 注意此处是相对路径
      json_fin >> json_obj; 
      json_fin.close();
      
      //***********************************************************************//
      // Traversing json array
      if(json_obj.find(topic_name) == json_obj.end()) {
        return 0;
      }
      auto topic_obj = json_obj[topic_name];
      for(size_t i = 0; i < topic_obj["sub"].size(); ++i) {
        auto queue =  topic_obj["sub"][i].get<std::string>();
       // cout<< queue <<endl;
        json_queues_.push_back(queue);
        all_json_queues.push_back(queue);
      }
     // cout<<"\n"<<"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"<<"\n\n"<<endl;
     // all_json_queues=json_queues_;
     // pool_name_ = "gos.pool.node1." + std::to_string( id_ ) + "_" + "1";
      pool_name_ = "gos.pool."+ topic_name + std::to_string( id_ ) + "_" + std::to_string(add_pool_num );
    //  pool_ = std::make_unique <managed_shared_memory>(open_or_create, pool_name_,  65536);
     // pool_=std::unique_ptr<boost::interprocess::managed_shared_memory>(open_or_create, pool_name_.c_str(),  65536);
     // all_pool_name.push_back( pool_name_ );
      //***********************************************************************//
}
//boost::interprocess::managed_shared_memory shm_pool;
template <typename M> 
void  Publisher::publish(M& sendBuf)
{
     // demo::msg writer;
     // writer.SerializeToString(&sendBuf);
        
      //*****************************************************************************//
      //The sending message sequence,and count the numbers,also call it msg's "id"
      std::string msg_seq = std::to_string(id_) + "_" + std::to_string(message_seq_);
   //   cout<<"\n"<<sendBuf<<"    "<<msg_seq<<endl;
      ++message_seq_;
      //****************************************************************************//
      message_reference mq_msg_ref;
     
      for (size_t i=0;i<add_pool_num+1;i++)
      {    
          pool_name_ = "gos.pool." + gobal_pool_name_ +"."+ std::to_string( id_ ) + "_" + std::to_string(add_pool_num );
          vector<string>::iterator ret = std::find(all_pool_name.begin(),all_pool_name.end(),pool_name_);
          while(ret==all_pool_name.end())//if not found the pool name,push_back 
          {
              all_pool_name.push_back(pool_name_);
            //  cout<<"Push New Pool to all_pool_name!!! and the all_pool_name number is: "<<all_pool_name.size()<<endl;
              // sleep(0.5);
          }
          
          managed_shared_memory shm_pool(open_or_create,pool_name_.c_str(), 1048576);//share_memory segment---1Mb
         // cout<<"Get the remaining bytes of the memory fragment: "<< shm_pool.get_free_memory()<<" Bytes"<<endl;//
         
          if(shm_pool.get_free_memory()>10000)//the pool_space is enough!!!But the threshold(10000) need to be cared!!!\
                                               it depends on class shm_pool_st's Buffer size!!!
          {
            //pool_name_=all_pool_name[i];
            //cout <<"The current pool_space is enough: "<<pool_name_.c_str()<<"  The number of pool is: "<<add_pool_num+1<<endl;
            //while(all_pool_name[])
            //build the object on the topic's pool,named as  msg's "id"!
           // managed_shared_memory shm_segment=pools.pop_back().second;
            shm_pool_st *pool_message_storage_obj =shm_pool.find_or_construct<shm_pool_st>( msg_seq.c_str())();
            //shm_pool_st* message_storage_obj = pool_->find_or_construct<shm_pool_st>(msg_seq)();
            //the queue's numbers,also known the same one topic's subscribe numbers
            pool_message_storage_obj->reference_counter = json_queues_.size();
            //uint32_t send_buf_size = sendBuf.size();//the length of msg!
            //memcpy(pool_message_storage_obj->protobuf_msg, &send_buf_size, sizeof(send_buf_size));
            //the msg need to be sent
           // memcpy(pool_message_storage_obj->protobuf_msg + sizeof(send_buf_size), sendBuf.c_str(), sendBuf.length());
            string msg_v_;
            sendBuf.SerializeToString(&msg_v_);
            memcpy(pool_message_storage_obj->protobuf_msg, msg_v_.c_str(), msg_v_.length()); 
            memset(mq_msg_ref.pool_name, 0, sizeof(mq_msg_ref.pool_name));//clear
            memset(mq_msg_ref.message_sequence, 0, sizeof(mq_msg_ref.message_sequence));//clear
            memcpy(mq_msg_ref.pool_name, pool_name_.c_str(), pool_name_.length());//deliver the pool_name
            memcpy(mq_msg_ref.message_sequence, msg_seq.c_str(), msg_seq.length());//deliver the msg's "id"

            add_pool_num=0;
            break;

          }
          else //the pool_space is not enough!!!
          {
          //  pool_name_ = "gos.pool.node1." + std::to_string( id_ ) + "_" + std::to_string(add_pool_num++ );
           /* vector<string>::iterator ret = std::find(all_pool_name.begin(),all_pool_name.end(),pool_name_);
            // printf("%d\n", ret);
            while(ret==all_pool_name.end())//if not found the topic name,push_back 
            {
                all_pool_name.push_back(pool_name_);
                cout<<"Push New Pool to all_pool_name!!! and the all_pool_name number is: "<<all_pool_name.size()<<endl;
                // sleep(0.5);
            }
            */
            add_pool_num++;
           // cout <<"Create New Space_Pool!"<<pool_name_.c_str()<<endl;
          }
      }
      
      
      for(auto& queue : json_queues_) //3 json_queues_ : recycle 3 times
      {
          managed_shared_memory queue_segment(open_or_create, queue.c_str(), 1048576);//---1Mb
          shm_queue::que* queue_obj = queue_segment.find_or_construct<shm_queue::que>("queue")();//find
         //******************************************************************************************//
          //500 buffers in front !!!! 
          //***if the queue's msg is full(>500)(boost::lockfree::capacity<500>),and pop out!!! 
          while(!queue_obj->push(mq_msg_ref))
          {
             // cout<<"The queue is full!!!,and need to be pop out!!!!"<<endl;
              message_reference temp_msg_ref;
              queue_obj->pop(temp_msg_ref);
              std::string temp_pool_name(temp_msg_ref.pool_name);
              std::string temp_msg_seq(temp_msg_ref.message_sequence);

              //***************************************************************************************//
              //---delete the shm pool Object,500 buffers in front !!!!
              auto temp_pool = managed_shared_memory(open_or_create, temp_pool_name.c_str(), 1048576);//---1Mb
              auto* temp_obj = temp_pool.find_or_construct<shm_pool_st>(temp_msg_seq.c_str())();//find
              
              //*****************************************//
              //***the number of subscribe'nodes -1
              //***if the number of subscribe'nodes=0,delete the current pool_object
              //***if ignore,it will occur 962 bad alloc!!!
              //***reference_counter =means the node subscribe's numbers!!!
              --temp_obj->reference_counter;//atomic
              //cout<<"   "<<shm_pool->reference_counter<<endl;
              //*******************************************//
             // cout<<"reference_counter: "<<temp_obj->reference_counter<<"  Current Pool_object_name: "<<temp_msg_seq.c_str()  <<endl;
              if(!temp_obj->reference_counter) 
              {
               // cout<<"Destroy!!!!"<<endl;
                temp_pool.destroy<shm_pool_st>(temp_msg_seq.c_str());//delete you_ming object
               // temp_pool.destroy_ptr<shm_pool_st>(temp_obj);//delete you_ming object
              }
              //*****************************************//
          }
      }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
      
      //*************************************//
      //捕抓ctrl+c信号进行停止退出
     /*   struct sigaction sigIntHandler;

        sigIntHandler.sa_handler = Pub_exit_handler;
        sigemptyset(&sigIntHandler.sa_mask);
        sigIntHandler.sa_flags = 0;

        sigaction(SIGINT, &sigIntHandler, NULL);*/
      //*************************************//
      //****************开两个子线程进行不同消息处理*********************//
     // std::thread temp1(message_queue_send,1);
     // temp1.detach();

     // std::thread temp2(pub_msg_topic,1);
     // temp2.detach();
      //*************************************************************//
}
/*
template<typename T>
int test<T>::add(T a,T b)
{
    return a+b;
}*/
 
/*  template <typename T>
    void test::print(const T&a) 
    {
      cout << a <<endl;
      //printf("%s\n",a );
    }
*/
template <typename T>
//int Subscriber::subscribe(const char *topics_name,const char *queue_name, void (*pCallback)(const T))
int Subscriber<T>::subscribe(const char *topics_name,const char *queue_name, std::function<void(T&)> call_back_)
{
    //managed_shared_memory shm_segment(open_or_create,topics_name, 65536); 
    //***********************************************************//
    //message queue
    // create segment and corresponding allocator
    managed_shared_memory queue_segment(open_or_create, queue_name, 1048576);//--1mb
    shm_queue::que *sub_queue = queue_segment.find_or_construct<shm_queue::que>("queue")();
    message_reference msg_out;
    //***********************************************************//
    if (sub_queue->pop(msg_out))//reading speed decided by subscribe speed.
    {
        cout<<msg_out.message_sequence<<"  subscribe_pool_name: "<<msg_out.pool_name<<endl;//msg's id
      //Shared memory object size in bytes
     //   cout<<msg_out.pool_name<<endl;
        managed_shared_memory shm_segment(open_or_create,msg_out.pool_name, 1048576);
        shm_pool_st *shm_pool = shm_segment.find_or_construct<shm_pool_st>(msg_out.message_sequence)();
       //std::cout << "Memory1: '" << shm_pool->reference_counter<<"  "<<shm_pool->protobuf_msg << "'\n";
       // string s;
        //cout<<shm_pool->protobuf_msg<<endl;
        //*******************************************//
        //***if ignore,it will occur 962 bad alloc!!!
        //***reference_counter =means the node subscribe's numbers!!!
        
        //cout<<"   "<<shm_pool->reference_counter<<endl;
        //*******************************************//
        //s.assign(shm_pool->protobuf_msg,strlen(shm_pool->protobuf_msg));
        string s(shm_pool->protobuf_msg,sizeof(shm_pool->protobuf_msg));
       // s.assign(shm_pool->protobuf_msg, shm_pool->protobuf_msg.length());
        //************************************************************************//
        //进行protobuf数据反序列化
        deserialize_msg.ParseFromString(s);
        //cout<<"frame_id: "<< reader.frame_id()<<endl;
       // cout<<"camera_mode: "<< reader.camera_mode()<<endl;
       // cout<<"string_image: "<< reader.string_image()<<endl;

         //*************************//
          //**call_back()
         // void (*p)(const T);
        //  p = pCallback;
         //  demo::msg result = reader;
         // (*p)(deserialize_msg);
          //*************************//
        call_back_(deserialize_msg);
        --shm_pool->reference_counter;
       // sleep(1);  
    }
   
    //*************************************//
    //捕抓ctrl+c信号进行停止退出
  /*  struct sigaction sigIntHandler;
    sigIntHandler.sa_handler = Sub_exit_handler;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;
    sigaction(SIGINT, &sigIntHandler, NULL);*/
    //*************************************//
    //***********************************************************//
   
 /*   sem_close(sem_subscribe1);
    sem_close(sem_subscribe5);
    sem_unlink("sem_subscribe1");
    sem_unlink("sem_subscribe5");
    */
}
/*
int main()
{
  gos::Publisher n;
  n.advertiser("chatter","/home/linsc/SenseTime_robot/二期开发/shareMemory/Boost/3msg_pic_proto_demo/gos_config.json");
}*/
















