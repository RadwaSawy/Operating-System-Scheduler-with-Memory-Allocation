#include <stdio.h> 
#include <stdlib.h>


typedef struct Node { 

	 struct process data; 

	// Lower values indicate higher priority 
	int priority; 
	struct Node* next; 

} Node; 



// Function to Create A New Node 
Node* newNode(struct process d, int p) 
{ 
	
	Node* temp = (Node*)malloc(sizeof(Node)); 
	temp->data = d;
	temp->priority = p; 
	temp->next = NULL;
	//printf("hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh....................\n"); 
	return temp; 
} 
// Return the value at head 
struct process peek(Node** head) 
{ 
	return (*head)->data; 
} 

// Removes the element with the 
// highest priority form the list 
void pop(Node** head) 
{ 
	Node* temp = *head; 
	(*head) = (*head)->next; 
	free(temp); 
} 

// Function to check is list is empty 
int priorityisempty(Node** head) 
{ 
	return (*head) == NULL; 
}

// Function to push according to priority 
void push(Node** head, struct process d, int p) 
{ 
	if(priorityisempty(head))
	{
		(*head)=newNode(d, p); 
		return;
	}
	Node* start = (*head); 

	// Create new Node 
	Node* temp = newNode(d, p); 

	// Special Case: The head of list has lesser 
	// priority than new node. So insert new 
	// node before head node and change head node. 
	if ((*head)->priority >= p) { 

		// Insert New Node before head 
		temp->next = *head; 
		(*head) = temp; 
	} 
	else { 

		// Traverse the list and find a 
		// position to insert new node 
		while (start->next != NULL && 
			start->next->priority < p) { 
			start = start->next; 
		} 

		// Either at the ends of the list 
		// or at required position 
		temp->next = start->next; 
		start->next = temp; 
	} 
} 
