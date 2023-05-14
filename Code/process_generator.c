#include "headers.h"
int sem1;
int sem2;
struct msgbuff
{
    long mtype;
    struct process msgprocess;
};
int msgqid, msgqid2;

void clearResources(int);

void inputfile_func(struct Queue* q)
{
	// read input function
	FILE *fp;
    char* filename = "./processes.txt";
 
    fp = fopen(filename, "r");
    if (fp == NULL){
        printf("Could not open file %s",filename);

    }

	char ignore[1024]; // to ignore the first line
	fgets(ignore, sizeof(ignore), fp);
	

    while(1)
	{
		int id, arr_time, run_time, prior, mem_size;
		fscanf(fp,"%d",&id);
		fscanf(fp,"%d",&arr_time);
		fscanf(fp,"%d",&run_time);
		fscanf(fp,"%d",&prior);
		fscanf(fp, "%d",&mem_size);
		if(feof(fp))
		{
			break;
		}
		else{
		}
		struct process p;
		p.ID=id;
		p.ArrivalTime=arr_time;
		p.RunTime=run_time;
		p.Priorty=prior;
		p.memsize=mem_size;
		enqueue(q,p); 
		if(feof(fp))
		{
			break;
		}
	}
        
    fclose(fp);
	printf("\nHAVE RECIEVED %d PROCESSES\n",q->size);
}


int main(int argc, char * argv[])
{
	int schedulerpid;
    signal(SIGINT, clearResources);
	sem1=create_sem(100,0);

    // TODO Initialization
    // 1. Read the input files.
	struct Queue* process_queue = createQueue(10000);
    inputfile_func(process_queue);

	// 2. Ask the user for the chosen scheduling algorithm and its parameters, if there are any.
	printf("\n 1-SJF  2-RR  3-HPF 4-SRTN\n");
	printf("---------Choose the algorithm from 1-4 \n : ");

	int in;
	int quantum;
	scanf("%d",&in);
	while(in>4)
	{
		printf("-----Please enter number again------- ");
		scanf("%d",&in);
	}
	if(in==2) // take the quantum from the user
	{
	  printf("---------Enter the Quantum:  ");	
	  scanf("%d",&quantum);
	}

	msgqid = msgget(80, IPC_CREAT | 0644);
    if (msgqid==-1)
    {
        perror("Error in create");
    }
	printf("\n message queue is done\n");

    
    // 3. Initiate and create the scheduler and clock processes.

	int pid_1=fork();
	
	if(pid_1<0)
	{
        perror("Yalhyyyy forking");
	}
	else if(pid_1==0)
	{   				
		    char *const __arg[]={"./cccc.out",NULL};
            int status=execvp("./cccc.out",__arg);
			if(status ==-1)
    	    {
    		perror("Yalhyyyy");
    	    }
	}
	else
	{
		down(sem1);
	int pid_2=fork();

	if(pid_2<0)
	{
		perror("Yalhyyyy forking");
 
	}
	else if(pid_2==0)
	{     
             if(in==1) ///////////////SJF scheduler
		{
			char *const __arg[]={"./ss.out",NULL};
    	     int status=execvp("./ss.out",__arg);
    	     if(status ==-1)
    	     {
    		   perror("Yalhyyyy");
			 }

		}  	
		else if(in==2)	/////////// RR scheduler
		{
			int i=quantum;
            int size=5;
            char  buf[size];
            snprintf(buf, sizeof(buf), "%d \n ", i);
			 char *const __arg[]={"./ssrr.out",buf,NULL};
    	     int status=execvp("./ssrr.out",__arg);
    	     if(status ==-1)
    	     {

    		   perror("Yalhyyyy");
			 }

		}
		else if(in==3) ///////////// HPF scheduler 
		{
			char *const __arg[]={"./sshp.out",NULL};
    	     int status=execvp("./sshp.out",__arg);
    	     if(status ==-1)
    	     {

    		   perror("Yalhyyyy");
			 }
		}
		else if(in==4)  //SRTN
		{
		     char *const __arg[]={"./ssrn.out",NULL};
    	     int status=execvp("./ssrn.out",__arg);
    	     if(status ==-1)
    	     {

    		   perror("Yalhyyyy");
			 }

		}


	}
	else
	{ 
	   // 4. Use this function after creating the clock process to initialize clock
	        initClk();
       // To get time use 
	                    struct process p;
						int flag=-1;
	                    while(!isEmpty(process_queue))
						{
							// 6. Send the information to the scheduler at the appropriate time.
							int y=front(process_queue,&p);
							int x=getClk();
							while(p.ArrivalTime==x)
							{
								dequeue(process_queue,&p);

								struct msgbuff sendprocess;
                                sendprocess.mtype=2;
                                sendprocess.msgprocess=p;
								
                                int sender_msg = msgsnd (msgqid, &sendprocess ,sizeof(struct msgbuff)-sizeof(long),!IPC_NOWAIT);
                                
								if (sender_msg==-1)
                                {
                                   perror("Error in sending");
                                }
								else{
									printf("--------------process wil be send with id %d---------",sendprocess.msgprocess.ID);
								}

								if (flag!=getClk())
								{
									  kill(pid_2, SIGUSR1);
								    printf("\n-----------------------------sending signal-------------------\n");
									flag=getClk();
								}


								
							
								//-------------------------------------------------------------------------------------
								int y=front(process_queue,&p);
								if(y==0)
								{
									kill(pid_2, SIGUSR2);
									break;
								}
							}
							
						}
						waitpid(pid_2,NULL,0);
	                    int z=getClk();
                        printf("\n current time %d\n",z);
                    destroyClk(true);
					kill(getpid(),SIGINT);


	}	
      
	}

}

void clearResources(int signum)
{
   printf("\n---------------------------destroying ipcs %d---------------------------------\n",msgqid);
   	destroy_sem(sem1);
    msgctl(msgqid, IPC_RMID, 0);
	//destroy_sem(sem2);
}