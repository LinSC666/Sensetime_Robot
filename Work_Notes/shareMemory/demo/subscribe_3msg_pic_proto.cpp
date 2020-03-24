#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <semaphore.h>
#include <fcntl.h>

#include <fstream> // ifstream, ifstream::in
#include <opencv2/opencv.hpp>
#include <iostream>
#include<string.h>

#include <signal.h>

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
#include "msg_pic.pb.h"
//*********************//

//***********************************************************************************************************//
//Linux shareMemory communication
//Publish
//&& shm_master主节点，供注册分配键值使用 && 捕获ctrl+c，若无，则终端直接结束的话，造成一些程序没运行就退出 
//&& 进行多线程处理同步(处理image和普通字符串，不同的while） 
//&& 信号量semaphore实现publish和subscribe进程同步，发才能收，保证一发一收.
//&& 进行protobuf数据序列化
//&& 生成动态链接库，供subscribe_mock_data和publish_mock_data其他单开的node的调用；
//LinSC
//2020/3/14
//***********************************************************************************************************//


using namespace std;
using namespace cv;

#define TEXT_SZ1 1048576
struct share_st
{
    int write;
    char text[TEXT_SZ1];
   // string protobuf_msg;
   /// sem_t sem;
};
#define TEXT_SZ2 1048576  //1024*1024 B = 1 Mb
struct share_st_pic
{
    int write;// 作为一个标志，非0：表示可读，0：表示可写
    int read;// 作为一个标志，非0：表示可读，0：表示可写

    //************* 记录写入 和 读取 的文本***************//
    char write_text1[TEXT_SZ2];
    //char read_text1[TEXT_SZ];
    //sem_t sem;
    //**************************************************//
};

//******************************************************//
//shm_master
#define TEXT_SZ3 10 //2048B
struct share_insert_topic
{
    int shm_insert_id;
    int refresh_flag;
    //std::vector<int> shm_insert_id;
    //string insert_text;
    char insert_text[TEXT_SZ3];
   // char text[TEXT_SZ];
    //sem_t sem;
};
//******************************************************//

//*************************************//
//msg_topic
void *shm=NULL;
void *shm2=NULL;
void *shm3=NULL;
struct share_st *shared=NULL;
struct share_st *shared2=NULL;
struct share_st *shared3=NULL;
//char buffer[BUFSIZ+1];
int shmid,shmid2,shmid3;
//*************************************//

//*************************************//
//picture_topic
int picture_show=0;
void *shm_pic=NULL;
struct share_st_pic *shared_pic=NULL;
char *buffer_pic[3];
int shmid_pic;
key_t key;
string sGetPic;
//*************************************//

sem_t *sem_subscribe1;
int cnum=0;
 demo::msg reader;
char image_buf[TEXT_SZ2];

//*************************************//
//捕抓ctrl+c信号进行停止退出
int running=1;
void my_handler(int s){
           printf("Caught signal %d\n",s);
           running=0;
          // exit(1);
}
//*************************************//

void msg_topic(int a)
{
    while(running)
    {
        if(shared->write==1)//表示可进行读
        {
            sem_wait(sem_subscribe1);

            
            cout<<"^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"<<endl;
           // cout<<"You read_shareMemory1: "<<shared->text<<"  "<<cnum++<<"\n"<<endl;
            cout<<"You read_shareMemory1: "<<shared->text<<"\n"<<endl;
            cout<<"You read_shareMemory2: "<<shared2->text<<"\n"<<endl;
            cout<<"You read_shareMemory3: "<<shared3->text<<"\n"<<endl;
            cout<<"frame_id: "<< reader.frame_id()<<endl;
            cout<<"camera_mode: "<< reader.camera_mode()<<endl;
           // cout<<"string_image: "<< reader.string_image()<< "  " <<reader.string_image().length()<<endl;;
            cout<<"____________________________________________________________"<<"\n\n"<<endl;
           // cout<<"____________________________________________________________"<<endl;
        }
    }
}

int pic_topic(int b)
{
    // printf("receive6666666666666666666666666666\n");
    while(running)
    {
               // printf("%d\n",shared_pic->write); 
        //**************receive client data****************//
          if(shared_pic->write==2)//mean reading...
        {
            shared_pic->write=3;
            //printf("Receive Picture 66666!!!!\n");

            string s;
            //char *p = "adghrtyh";
            s.assign(shared_pic->write_text1,sizeof(shared_pic->write_text1));

            //************************************************************************//
            //进行protobuf数据反序列化
           
            reader.ParseFromString(s);
            cout<<"frame_id: "<< reader.frame_id()<<endl;
            cout<<"camera_mode: "<< reader.camera_mode()<<endl;
           // cout<<"string_image: "<< reader.string_image()<< "  " <<reader.string_image().length()<<endl;;
            cout<<"____________________________________________________________"<<"\n\n"<<endl;
           // memcpy(image_buf,reader.string_image().c_str(),reader.string_image().length());
           // cout<<"    hh       : " << reader.string_image().length()<<"\n\n"<<endl;
           // printf("receive: %s  %s  %s \n",shared_pic->write_text1);
            //sleep(rand()%3);
            ofstream fout(sGetPic.c_str(), ios::binary);
            if(!fout) return false;
            fout.write(reader.string_image().c_str(), reader.string_image().length());

            fout.close();

        }

        //**************receive client data****************//
        else if( shared_pic->write==3)
        {
           shared_pic->write=4;
           Mat image = imread(sGetPic ,cv::IMREAD_REDUCED_COLOR_8);
            //MAT是数据类型（主要用来保存图片信息），image是变量名称。
           Mat dstImage1;
           resize(image, dstImage1, Size(image.cols*2, image.rows*2), (0, 0), (0, 0), 3); //缩小
           //resize(srcImage, dstImage2, Size(srcImage.cols * 2, srcImage.rows * 2), (0, 0), (0, 0), 3); //放大
           imshow("subscribe_pic",dstImage1);     //image在这个窗口上显示.
           waitKey(0);         //等待KEY,2000毫秒，2s等待输入，过了2s自动执行return 0.

          // printf("receive Ok!\n");

            //return 0;
            //sleep(1);
        }

    }
}

int main()
{
    //int running=1;
    void *insert_shm=NULL;
    struct share_insert_topic *insert_shared=NULL;
    int insert_shmid;
    int key_id[10];
   // master_shmid=shmget((key_t)1111,sizeof(struct share_judge_topic),0666|IPC_CREAT);
    insert_shmid=shmget((key_t)2222,sizeof(struct share_insert_topic),0666|IPC_CREAT);
    if(insert_shmid==-1)
    {
        fprintf(stderr,"shmget failed\n");
        exit(EXIT_FAILURE);
    }
    insert_shm=shmat(insert_shmid,(void*)0,0);
    if(insert_shm==(void*)-1)
    {
        fprintf(stderr,"shmat failed\n");
        exit(EXIT_FAILURE);
    }
    printf("Memory attached at %p\n",(void*)insert_shm);
    insert_shared=(struct share_insert_topic*)insert_shm;


    insert_shared->shm_insert_id=0;
    insert_shared->refresh_flag=1;//mark for the topics in and the other node can refresh!!!
  //  insert_shared->insert_text="chatter1";//argv[1]
    memcpy(insert_shared->insert_text,"chatter1",10);
    while(insert_shared->shm_insert_id==0&&running==1)
    {
        cout<<insert_shared->insert_text<<"\n"<<endl;
        //*************************************//
        //捕抓ctrl+c信号进行停止退出
        struct sigaction sigIntHandler;

        sigIntHandler.sa_handler = my_handler;
        sigemptyset(&sigIntHandler.sa_mask);
        sigIntHandler.sa_flags = 0;

        sigaction(SIGINT, &sigIntHandler, NULL);
        //*************************************//
    }
    key_id[0]=insert_shared->shm_insert_id;


    //insert_shared->insert_text="chatter2";
    memcpy(insert_shared->insert_text,"chatter2",10);
    while(insert_shared->shm_insert_id==key_id[0]&&running==1)
    {
        cout<<insert_shared->insert_text<<"\n"<<endl;
        //*************************************//
        //捕抓ctrl+c信号进行停止退出
        struct sigaction sigIntHandler;

        sigIntHandler.sa_handler = my_handler;
        sigemptyset(&sigIntHandler.sa_mask);
        sigIntHandler.sa_flags = 0;

        sigaction(SIGINT, &sigIntHandler, NULL);
        //*************************************//
    }
    key_id[1]=insert_shared->shm_insert_id;


   // insert_shared->insert_text="chatter3";
    memcpy(insert_shared->insert_text,"chatter3",10);
    while(insert_shared->shm_insert_id==key_id[1]&&running==1)
    {
        cout<<insert_shared->insert_text<<"\n"<<endl;
        //*************************************//
        //捕抓ctrl+c信号进行停止退出
        struct sigaction sigIntHandler;

        sigIntHandler.sa_handler = my_handler;
        sigemptyset(&sigIntHandler.sa_mask);
        sigIntHandler.sa_flags = 0;

        sigaction(SIGINT, &sigIntHandler, NULL);
        //*************************************//
    }
    key_id[2]=insert_shared->shm_insert_id;


    //insert_shared->insert_text="image_raw";
    memcpy(insert_shared->insert_text,"image_raw",10);
    while(insert_shared->shm_insert_id==key_id[2]&&running==1)
    {
        cout<<insert_shared->insert_text<<"\n"<<endl;
        //*************************************//
        //捕抓ctrl+c信号进行停止退出
        struct sigaction sigIntHandler;

        sigIntHandler.sa_handler = my_handler;
        sigemptyset(&sigIntHandler.sa_mask);
        sigIntHandler.sa_flags = 0;

        sigaction(SIGINT, &sigIntHandler, NULL);
        //*************************************//
    }
    key_id[3]=insert_shared->shm_insert_id;


    insert_shared->shm_insert_id=111;//stop the shm_master


    shmid=shmget((key_t)key_id[0],sizeof(struct share_st),0666|IPC_CREAT);
    shmid2=shmget((key_t)key_id[1],sizeof(struct share_st),0666|IPC_CREAT);
    shmid3=shmget((key_t)key_id[2],sizeof(struct share_st),0666|IPC_CREAT);
    if(shmid==-1)
    {
        fprintf(stderr,"shmget failed\n");
        exit(EXIT_FAILURE);
    }
    shm=shmat(shmid,(void*)0,0);
    shm2=shmat(shmid2,(void*)0,0);
    shm3=shmat(shmid3,(void*)0,0);
    if(shm==(void*)-1||shm2==(void*)-1||shm3==(void*)-1)
    {
        fprintf(stderr,"shmat failed\n");
        exit(EXIT_FAILURE);
    }
    printf("Memory  attached at %p\n",(void*)shm);
    printf("Memory2 attached at %p\n",(void*)shm2);
    printf("Memory3 attached at %p\n",(void*)shm3);
    shared=(struct share_st*)shm;
    shared2=(struct share_st*)shm2;
    shared3=(struct share_st*)shm3;
    //sem_init(&(share-sem),1,1);
    sem_subscribe1=sem_open("sem_subscribe1",O_CREAT|O_RDWR,0666,0);
    if(sem_subscribe1==SEM_FAILED)
    {
        printf("error1");
        return -1;
    }

    //****************************创建共享内存****************************//
    //key_t key;
    // key=ftok(argv[1],atoi(argv[2]));
    shmid_pic=shmget((key_t)key_id[3],sizeof(struct share_st_pic),0666|IPC_CREAT);
    printf("shmid_pic is: %d\n",shmid_pic);
    //******************************************************************//
    if(shmid_pic==-1)
    {
      fprintf(stderr,"shmget failed\n");
      exit(EXIT_FAILURE);
    }
    //***************************************************************//
    // 将共享内存连接到当前进程的地址空间
    // 注意：shm有点类似通过 malloc() 获取到的内存，所以这里需要做个 类型强制转换
    shm_pic=shmat(shmid_pic,(void*)0,0);
    //***************************************************************//
    if(shm_pic==(void*)-1)
    {
        fprintf(stderr,"shmat failed\n");
        exit(EXIT_FAILURE);
    }
    printf("Memory attached at %p\n",(void*)shm_pic);
    shared_pic=(struct share_st_pic*)shm_pic;

    insert_shared->refresh_flag=0;//mark for the topics in and the other node can refresh!!!
    //sem_init(&(share-sem),1,1);
    //shared2->write=1;//can write
    sGetPic ="/home/linsc/SenseTime_robot/二期开发/shareMemory/shareMemory_multi_topic/linsc_proto.jpg"; //output the image path
  //  shared_pic->write=1;
    printf("--------------------------\n");
    printf("The shared_pic->writ is %d\n",shared_pic->write);
    printf("--------------------------\n\n");

    std::thread temp1(msg_topic,3);
    temp1.detach();

    std::thread temp2(pic_topic,3);
    temp2.detach();

    while(running)
    {
        //*************************************//
        //捕抓ctrl+c信号进行停止退出
        struct sigaction sigIntHandler;

        sigIntHandler.sa_handler = my_handler;
        sigemptyset(&sigIntHandler.sa_mask);
        sigIntHandler.sa_flags = 0;

        sigaction(SIGINT, &sigIntHandler, NULL);
        //*************************************//
    }
    
   // printf("The shared_pic->writ is %d\n",shared_pic->write);
    
    printf("\n\n");
    printf("------------END---------------\n");
    printf("------------------------------\n");
    printf("The node is exit !!!\n");
    printf("Clean the memory Finshined !!!\n");
    printf("------------------------------\n");
    printf("------------------------------\n\n");
  /*  if(shmdt(shm)==-1||shmdt(shm2)||shmdt(shm3)||shmdt(shm_pic))
    {
        
        fprintf(stderr,"shmdt failed!\n");
        exit(EXIT_FAILURE);
    }
    if(shmctl(shmid,IPC_RMID,0)==-1||shmctl(shmid2,IPC_RMID,0)==-1||shmctl(shmid3,IPC_RMID,0)==-1||shmctl(shmid_pic,IPC_RMID,0)==-1)
    {
        fprintf(stderr,"shmctl(IPC_RMID_ failed\n");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);*/
}

















