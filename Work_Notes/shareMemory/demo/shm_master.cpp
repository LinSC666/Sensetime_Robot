#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <semaphore.h>
#include <fcntl.h>

#include <math.h> 
#include <algorithm>

#include <iostream>
#include <string>
#include <vector>
#include <iterator>

//*********************//
//捕获ctrl+c
#include <signal.h>
//*********************//

//***********************************//
//Linux shareMemory communication
//shm_master 一定要先开主节点才不会出错!!!，并删除所有内存
//LinSC
//2020/2/29
//***********************************//

using namespace std;

#define TEXT_SZ 10
struct share_insert_topic
{
    int shm_insert_id;
    int refresh_flag;
    //std::vector<int> shm_insert_id;
    //string insert_text;
    char insert_text[TEXT_SZ];
   // char text[TEXT_SZ];
    //sem_t sem;
};

#define TEXT_SZ2 1048576  //1024*1024 B = 1 Mb
struct share_st_pic
{
    int write;// 作为一个标志，非0：表示可读，0：表示可写
   // int read;// 作为一个标志，非0：表示可读，0：表示可写

    //************* 记录写入 和 读取 的文本***************//
    char write_text1[TEXT_SZ2];
    //char read_text1[TEXT_SZ];
    //sem_t sem;
    //**************************************************//
};


sem_t *sem_subscribe1;
int cnum=0;


//*************************************//
//msg_topic
void *shm=NULL;
void *shm2=NULL;
void *shm3=NULL;
struct share_st *shared=NULL;
struct share_st *shared2=NULL;
struct share_st *shared3=NULL;
char buffer[BUFSIZ+1];
int shmid,shmid2,shmid3;
//*************************************//

//*************************************//
//捕抓ctrl+c信号进行停止退出
int running=1;

void my_handler(int s){
           printf("Caught signal %d\n",s);
           running=0;
          // exit(1);
}
//*************************************//

int main()
{
    int count_node_num=0;
  //  void *master_shm=NULL;
    void *insert_shm=NULL;
   // struct share_judge_topic *master_shared=NULL;
    std::vector<string> master_text;

    struct share_insert_topic *insert_shared=NULL;
  //  char buffer[BUFSIZ+1];
   // int master_shmid;
    int insert_shmid;
    //master_shmid=shmget((key_t)1111,sizeof(struct share_judge_topic),0666|IPC_CREAT);
    insert_shmid=shmget((key_t)2222,sizeof(struct share_insert_topic),0666|IPC_CREAT);
    if(insert_shmid==-1)
    {
	   fprintf(stderr,"shmget failed\n");
	   exit(EXIT_FAILURE);
    }
    //master_shm=shmat(master_shmid,(void*)0,0);
    insert_shm=shmat(insert_shmid,(void*)0,0);
    if(insert_shm==(void*)-1)
    {
    	fprintf(stderr,"shmat failed\n");
	    exit(EXIT_FAILURE);
    }
    printf("Memory attached at %p\n",(void*)insert_shm);
    //master_shared=(struct share_judge_topic*)master_shm;
    insert_shared=(struct share_insert_topic*)insert_shm;
    //sem_init(&(share-sem),1,1);
    sem_subscribe1=sem_open("sem_subscribe1",O_CREAT|O_RDWR,0666,0);
    if(sem_subscribe1==SEM_FAILED)
    {
	    printf("error1");
        return -1;
    }

    vector<string>::iterator ret;

   /* shmid=shmget((key_t)key_id[0],sizeof(struct share_st),0666|IPC_CREAT);
    shmid2=shmget((key_t)key_id[1],sizeof(struct share_st),0666|IPC_CREAT);
    shmid3=shmget((key_t)key_id[2],sizeof(struct share_st),0666|IPC_CREAT);

    shm=shmat(shmid,(void*)0,0);
    shm2=shmat(shmid2,(void*)0,0);
    shm3=shmat(shmid3,(void*)0,0);

*/
    printf("\n\n");
    printf("               ---------------------------------------\n");
    printf("               ***************************************\n");
    printf("               ***         Master Start !!!        ***\n");
    printf("               *** Waiting for topics to subscribe ***\n");
    printf("               ***      I am sensetime Robot       ***\n");
    printf("               ***     ^_^   @_@   &_&   $_$       ***\n");
    printf("               ***************************************\n");
    printf("               ---------------------------------------\n\n");
    int key_id[10];
    int shmid[10];
    void *shm[10];
    while(running)
    {
	
        if(insert_shared->refresh_flag==1)//mark for the topics in and the other node can refresh!!!
        {

            if(master_text.empty()&& insert_shared->insert_text[0]=='\0')
            {
                printf("Topics in !!!!!\n");
              //  cout<<insert_shared->insert_text<<"\n"<<endl;
                //count_node_num=1;
                sleep(1);
            }
            else 
            {
                //vector<char>::iterator ret;
               //  auto ret = std::find(shared->shm_master_id.begin(),shared->shm_master_id.end(), 12);
                ret = std::find(master_text.begin(),master_text.end(), insert_shared->insert_text);
                // printf("%d\n", ret);
                if(ret==master_text.end())//if not found the topic name,push_back 
                {
                    master_text.push_back(insert_shared->insert_text);
                    cout<<"not match!!! so need to push_back!!!"<<"\n"<<endl;
                   // sleep(0.5);
                }
                else //if (ret!=master_text.end())
                {
                    cout<<"final receive number:  "<<insert_shared->insert_text<<"\n"<<endl;
                    //cout<<" position is "<<std::distance(master_text.begin(),ret)+1<<endl;
                    insert_shared->shm_insert_id=(std::distance(master_text.begin(),ret)+1)*100;
                    key_id[count_node_num++]=insert_shared->shm_insert_id;
                    cout<<"The number of node is: "<<insert_shared->shm_insert_id<<"  "<<std::distance(master_text.begin(),ret)+1<<"\n"<<endl;
                   // sleep(0.5);
                }
            
            }
        }
        else
         count_node_num=0;

      //*************************************//
        //捕抓ctrl+c信号进行停止退出
        struct sigaction sigIntHandler;

        sigIntHandler.sa_handler = my_handler;
        sigemptyset(&sigIntHandler.sa_mask);
        sigIntHandler.sa_flags = 0;

        sigaction(SIGINT, &sigIntHandler, NULL);
        //*************************************//
    }
     //****************************************//
    //删除共享内存，并退出！
    //运行这段之后，shared_pic->write会自动清零！！！
   // shared_pic->write=1;
    printf("\n");
    printf("               ---------------------------------------\n");
    printf("               ***************************************\n");
    printf("               ********     Master Out !!!    ********\n");
    printf("               ***************************************\n");
    printf("               ---------------------------------------\n\n");
    
    //********************************************//
    //***delete other proc's id memory
    for(int i=0;i<sizeof(key_id)/sizeof(int);i++)
    {
        shmid[i]=shmget((key_t)key_id[i],sizeof(struct share_st_pic),0666|IPC_CREAT);
        shm[i]=shmat(shmid[i],(void*)0,0);
        shmdt(shm[i]);
        shmctl(shmid[i],IPC_RMID,0);
    }
    //********************************************//

    //********************************************//
    //***delete master's id memory
    if(shmdt(insert_shm)==-1)
    {
        fprintf(stderr,"shmdt failed!\n");
        exit(EXIT_FAILURE);
    }
    if(shmctl(insert_shmid,IPC_RMID,0)==-1)
    {
        fprintf(stderr,"shmctl(IPC_RMID_ failed\n");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
    //********************************************//

}


















