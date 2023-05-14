#include "headers.h"

node * root ; // holde the binary tree
leafNode* Qfreeleaves; // children that are free to be allocated

//process Table-------------------------------------------------------------------------------------------------
    struct process process_table[1010];
//--------------------------------------------------------------------------------------------------------------

//array-----------------------------------------------------------------------
int WT_arr[1010];
int WT_counter=0;
//-----------------------------------------------------------------------------

struct msgbuff
{
    long mtype;
    struct process msgprocess;
};
int msgqid;

struct PQueue* PCB_Table;
int counter=0;
Node* head=NULL;

int End_process=0;

int number_of_process=0;
float Avg_WTA=0;
int Avg_wait=0;
float std_WTA=0;
int total_time=0;
FILE *out;
FILE *out2;
FILE *memout;


void handler_byebye_process(int signum )
{
   End_process=1;
   printf("\n-----------------end signal at %d -------------------\n",getClk());
}

void allocate_memory(struct process* p)
{ 
  //Qfreeleaves
  // find the first node with size equal or greater than the process
  node * PA;
  deleteleaf(&Qfreeleaves,p->memsize,& PA);

  while(PA->size/2>=p->memsize) // need to split
  { 
    insert(&PA,PA->size/2); // two nodes with half the size 
    printf("\n------------already inserted -----------\n");
    node * first=PA->left;
    node * second=PA->right;
    // return one node to the leaves queue and test on the other 
    lpush(&Qfreeleaves, &second, second->size,second->start);
    PA=first;
  } 
 
  // now we have a pointer to a memory that is free and of the right size 
  // allocate 
  PA->node_state=noccupied;
  p->test=3;
  p->memory=PA; // store a pointer to the memory in the process 
  fprintf(memout,"#At time %d allocated %d bytes for process %d from %d to %d \n",getClk(),p->memsize,p->ID,PA->start,PA->end);

}

void dellocate_memory(struct process* p)
{
  printf("\n--------------test %d--------------\n",p->test);
  (p->memory)->node_state=nfree; // 1 is free 
  node* par= (p->memory)->m_parent;
  node* me=p->memory;
  fprintf(memout,"#At time %d freed %d bytes for process %d from %d to %d \n",getClk(),p->memsize,p->ID,(p->memory)->start,(p->memory)->end);
while(1)
{
  if(par->left->node_state==nfree && par->right->node_state==nfree && par->size!=512) // both are free ... can merge 
  {          printf("\n-----------Merging--------------\n");
            printf("\ninside deallocation===============%d========\n",Qfreeleaves->data->size);
    // determining me 
    if(me==par->left)
    { 
      printf("deleting right");
      delteme(&Qfreeleaves,par->right);
    }
    else if(me ==par->right)
    {
      printf("deleting left");
       delteme(&Qfreeleaves,par->left);
    }
  
      printf("\ninside deallocation===============%d========\n",Qfreeleaves->data->size);
      printf("\n going into delete child\n");
      deletechild(par);
      printf("\ninside deallocation===============%d========\n",Qfreeleaves->data->size);
      par->node_state=nfree;
      // insert ll parent in leaves queue 
      printf("\n===============%d========\n",Qfreeleaves->data->size);
    //lpush(&Qfreeleaves, &par, par->size,par->start);

      printf("\n===============%d========\n",Qfreeleaves->data->size);
  }
  else{
    
    lpush(&Qfreeleaves, & me , me->size, me->start);
    printf("\n===============%d========\n",Qfreeleaves->data->size);
    break;
  }
  printf("\n-------------finished Dellocation---------\n");
  me=par;
  par=par->m_parent;

}
}

void MSG_Process()
{
    while(1)
    {
        struct process p;
        struct msgbuff arrprocess;
        printf("Waiting for msg \n");
        int rec_msg = msgrcv (msgqid , &arrprocess , sizeof(struct msgbuff)-sizeof(long),0,!IPC_NOWAIT);
        if (rec_msg ==-1)
        {
            perror("Error in receving");
        }
        else
        {
              p=arrprocess.msgprocess; 
              int pid_1=fork();
              number_of_process++;
             if(pid_1<0)
             {
                  perror("Yalhyyyy");

             }
            else if(pid_1==0)
        {
           printf("\n-------------------------------------new process with arr %d---------------------------\n",p.ArrivalTime);
           int i=p.RunTime;
           int size=5;
           char  buf[size];
           snprintf(buf, sizeof(buf), "%d \n ", i);
           char *const __arg[]={"./process2.out",buf,NULL};
    	     int status=execvp("./process2.out",__arg);
    	     if(status ==-1)
    	     {

    		    perror("forking the process");
            }
            

        }
        else
  {  
    //------------------------------------------------------------------------------------------------------
    
    total_time=total_time+p.RunTime;
    p.actualid=pid_1;
    p.remaining_time=p.RunTime;
    p.totalwork=0;
    p.s=ready;
    kill(getpid(),SIGSTOP);
    printf("i am a scheduler and my process id is %d \n",p.actualid);

   //------------add the process to the Process table----------------------------------------------------
    process_table[p.ID]=p;
   //------------------------------------------------------------------------------------------------------
    allocate_memory(&p);
    printTree(root,0);

    if(head == NULL)
    {
        
         head = newNode(p,p.Priorty);
         printf("\n ------------First Head created---------------\n");
    }
    else
      {
         
         if(head->next == NULL)
         printf("\n el next is NULL ");
         push(&head,p,p.Priorty); 
      }
     
    }
        }
       int rc;
       struct msqid_ds buf;
       int num_messages;
       rc = msgctl(msgqid, IPC_STAT, &buf);
       num_messages = buf.msg_qnum;
       printf("\n ---------- number of msgs %d-----------",num_messages);    
       if(num_messages == 0)
       {
           printf("\n------------------no msgs here----------------------\n");
           break;
       }    

    }       
}

void handler_welcome_process(int signum)
{   
     MSG_Process();
}





void scheduling_HPF() ////////////////when it is excuted ??????????????????????????
{
   //pick the first process
   struct process p = peek(&head) ;
   printf("\ninside the scheduling function %d\n",p.actualid);
   pop(&head);
   kill(p.actualid,SIGCONT);
   int starttime=getClk();
   
   int waitedtime=getClk()-p.ArrivalTime-p.totalwork;
   Avg_wait=Avg_wait+waitedtime;
   if(p.remaining_time==p.RunTime)
   {
        fprintf(out,"At time %d process %d %s arr %d total %d remain %d wait %d \n",getClk(),p.ID,"Started",p.ArrivalTime,p.RunTime,p.RunTime,waitedtime);
   }
   else
   {if(p.s==stoped)
     fprintf(out,"At time %d process %d %s arr %d total %d remain %d wait %d \n",getClk(),p.ID,"Resumed",p.ArrivalTime,p.RunTime,p.remaining_time,waitedtime);
   }
   p.s=running;
   int rem_sleep=p.remaining_time;  
   printf("\n------------------------------schudler is going to sleep for %d at time %d------------------------------------------------\n",rem_sleep,getClk());
   printf("------------------------------%d-------------------\n",getClk());
   int r = getClk();
   sleep(rem_sleep);
   r=getClk()-r;
   printf("------------------------------clk %d and r=%d -------------------",getClk(),r);
       
    p.remaining_time=p.remaining_time-r;
    p.totalwork=p.totalwork+r;


   if(p.remaining_time>0) // process does not finished
   {
     kill(p.actualid,SIGSTOP);
     //w2=getClk()-p.pause;
     //int waitedtime=w1+w2;
     printf("\nprocess with id %d back to sleep with remaing time %d at time %d \n",p.actualid,p.remaining_time,getClk());
     if(head!=NULL)
     { perror("\n");
       struct process p2=peek(&head);
         if(p2.Priorty<p.Priorty)
           {
             fprintf(out,"At time %d process %d %s arr %d total %d remain %d wait %d \n",getClk(),p.ID,"Stoped",p.ArrivalTime,p.RunTime,p.remaining_time,waitedtime);
            p.s=stoped;
          }
     }
     push(&head,p,p.Priorty); 
   }
   else
   {
     int pid = waitpid(0,NULL,0);
     printf("\n---------deallocating---------\n");
     dellocate_memory(&p);
     printTree(root,0);
     int waitedtime=getClk()-p.ArrivalTime-(p.RunTime-p.remaining_time);
     int TA=getClk()-p.ArrivalTime;
     float WTA;
     if(p.RunTime!=0)
    {
      WTA=(1.0*TA)/p.RunTime;
    }
    else
     WTA=0;
     Avg_WTA=Avg_WTA+WTA;
      //storing WTA------------------------------------------------------
      WT_arr[WT_counter]=WTA;
      WT_counter=WT_counter+1;
      //-----------------------------------------------------------------
     fprintf(out,"At time %d process %d %s arr %d total %d remain %d wait %d TA %d WTA %.2f \n",getClk(),p.ID,"Finshed",p.ArrivalTime,p.RunTime,0,waitedtime,TA,WTA);

   }
 printf("Back in the scheduler with current time from the scheduling function %d",getClk());
int rc;
       struct msqid_ds buf;
       int num_messages;
       rc = msgctl(msgqid, IPC_STAT, &buf);
       num_messages = buf.msg_qnum;
       if(num_messages!=0)
       {
         MSG_Process();
       }


}

int main(int argc, char * argv[])
{
    initClk();
      msgqid = msgget(80, 0);
    if (msgqid==-1)
    {
        perror("Error in connect");
    }
    out = fopen("HPF.log", "w");
    if (out == NULL) {  printf("Something is wrong");}
    //fprintf(out, " I'm logging something ...\n");
    fprintf(out,"#At time x process y state arr w total z remain y wait k \n");

    out2=fopen("HPF.perf","w");
    if (out == NULL) {  printf("Something is wrong");}

    memout=fopen("HPFmemory.log","w");
    if(memout==NULL) {printf("Something wrong");}
    fprintf(memout,"#At time x allocated y bytes for process z from i to j \n");
    
    signal (SIGUSR1, handler_welcome_process);
    signal (SIGUSR2, handler_byebye_process);
    //p_s_shmid  = shmget(p_s_key,4096, IPC_CREAT | 0644);/////------make sure of the size--------------------------------------
    // PCB_Table=argv[1];

     //intializing the binary tree
    
    insert(&root,1024); // 1024
    root->m_parent=NULL;
    root->start=0;
    root->end=1023;
    insert(&root,512); // two nodes 512
    node * first512=root->left;
    node * second512=root->right;
    insert(&first512,256); // two nodes 256
    insert(&second512,256); // two nodes 256

    node * first256=first512->left; // pointer to a node in binary tree 
    node * second256=first512->right;
    node * third256=second512->left;
    node * forth256=second512->right;   


    Qfreeleaves= lnewNode(&first256,first256->size, first256->start); 
    lpush(&Qfreeleaves, &second256, second256->size,second256->start);
    lpush(&Qfreeleaves, &third256, third256->size,third256->start);
    lpush(&Qfreeleaves, &forth256, forth256->size,forth256->start);  
    printTree(root,0);

  while(End_process==0 || !priorityisempty(&head))
  {  
     if(!priorityisempty(&head))
     {//if(head!=NULL)
        //printf("\n i am not working properly %d\n",priorityisempty(&head));
       scheduling_HPF();
    } 

  }

  perror("\n ==========I AM OUT============================\n");
  int m=getClk();
    float cpu=(1.0*total_time/m)*100;
    fprintf(out2,"CPU utilization = %0.2f%%\n",cpu);

  float TAvg_wait=1.0*Avg_wait/number_of_process;
   fprintf(out2,"Avg waiting time = %0.2f\n",TAvg_wait); 
  Avg_WTA=Avg_WTA/number_of_process;
 fprintf(out2,"Avg WTA = %0.2f\n",Avg_WTA);  

 printf("\n -------------------yalaaaaaaaaaaaaahwaaaaaaaaay----------------\n"); 
 for(int i=0;i<sizeof(WT_arr);++i)
  {
      std_WTA=std_WTA+((WT_arr[i]-Avg_WTA)*(WT_arr[i]-Avg_WTA));
      printf("Std WTA = %0.2f",std_WTA);
      if(WT_arr[i]==0)
      {
          printf("\n Finshed loop \n");
          break;
      }
      
  }
  printf("\nStd WTA  = %0.2f \n",std_WTA);
  float fstd_WTA=sqrt(std_WTA/number_of_process);
  fprintf(out2,"Std WTA = %0.2f\n",fstd_WTA);
  
  fclose(memout);
  fclose(out2);
  fclose(out);
    printf("\n------------------------------------------scheduler terminating--------------------------\n");
    destroyClk(false);
}