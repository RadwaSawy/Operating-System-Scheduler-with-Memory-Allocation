// C program for array implementation of queue 
#include <limits.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include "leaves_queue.h"
enum state { ready=1, running=2,stoped=3,finished=4,started=5};

/*struct PCB
{
  struct process p;
  enum state s;
};*/

struct process
{
	int ID;
	int ArrivalTime;
	int RunTime;
	int remaining_time;
	int Priorty;
	int totalwork;
	int s;
	int memsize;
	node * memory;
	int actualid;   // the pid of the actual forked process
	int test;
};


// A structure to represent a queue 
struct Queue { 
	int front, rear, size; 
	unsigned capacity; 
	struct process * array; 
}; 

// function to create a queue 
// of given capacity. 
// It initializes size of queue as 0 
struct Queue* createQueue(unsigned capacity) 
{ 
	struct Queue* queue = (struct Queue*)malloc( 
		sizeof(struct Queue)); 
	queue->capacity = capacity; 
	queue->front = queue->size = 0; 

	// This is important, see the enqueue 
	queue->rear = capacity - 1; 
	queue->array = (struct process *)malloc( 
		queue->capacity * sizeof(struct process )); 
	return queue; 
} 

// Queue is full when size becomes 
// equal to the capacity 
int isFull(struct Queue* queue) 
{ 
	return (queue->size == queue->capacity); 
} 

// Queue is empty when size is 0 
int isEmpty(struct Queue* queue) 
{
	return (queue->size == 0); 

} 

// Function to add an item to the queue. 
// It changes rear and size 
void enqueue(struct Queue* queue, struct process  item) 
{ 
	if (isFull(queue)) 
		return; 
	queue->rear = (queue->rear + 1) 
				% queue->capacity; 
	queue->array[queue->rear] = item; 
	queue->size = queue->size + 1; 
	//printf("%d enqueued to queue\n", item); 
} 

// Function to remove an item from queue. 
// It changes front and size 
void dequeue(struct Queue* queue, struct process * p ) 
{ 
	if (isEmpty(queue)) 
		return;
	struct process  item = queue->array[queue->front]; 
	queue->front = (queue->front + 1) 
				% queue->capacity; 
	queue->size = queue->size - 1; 
    *p=item;
    return;
} 

// Function to get front of queue 
int front(struct Queue* queue, struct process * p) 
{ 
	if (isEmpty(queue)) 
		return 0;
	*p=queue->array[queue->front]; 
	return 1;
} 

// Function to get rear of queue 

/*int rear(struct Queue* queue) 
{ 
	if (isEmpty(queue)) 
		return INT_MIN; 
	return queue->array[queue->rear]; 
} */


