#include <stdio.h> 
#include <stdlib.h>
#include "binary_tree.h"

typedef struct leafNode { 

	node * data; // pointer on a a free node in the binary tree

	// Lower values indicate higher priority 
	int priority; 
	int priority_order;
	struct leafNode* next; 

} leafNode; 



// Function to Create A New Node 
leafNode* lnewNode(struct node ** leaf, int p,int p2) 
{ 
	
	leafNode* temp = (leafNode*)malloc(sizeof(leafNode)); 
	temp->data =  *leaf;
	temp->priority = p;
	temp->priority_order=p2;
	temp->next = NULL;
	//printf("hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh....................\n"); 
	return temp; 
} 
// Return the value at head 
struct node * lpeek(leafNode** head) 
{ 
	return (*head)->data; 
} 

// Removes the element with the 
// highest priority form the list 
void lpop(leafNode** head, node ** d) 
{ 
	leafNode* temp = *head; 
	(*head) = (*head)->next; 
	*d=temp->data;
	free(temp); 
} 

// Function to check is list is empty 
int lpriorityisempty(leafNode** head) 
{ 
	return (*head) == NULL; 
}

// Function to push according to priority 
void lpush(leafNode** head, node ** d, int p, int p2) 
{ 
	if(lpriorityisempty(head) )
	{
		perror("\n---------------fadyaaaa Leaves queue----------------\n");
		(*head)= lnewNode(d,p,p2);
		return; 
	}
	else
	{
		perror("\n--------------- msh fadyaaaa Leaves queue----------------\n");
	}
	printf("\n ------------------- push with size %d in Leaves queue --------------\n",p);
	leafNode* start = (*head); 

	// Create new Node 
	leafNode* temp = lnewNode(d, p, p2); 

	// Special Case: The head of list has lesser 
	// priority than new node. So insert new 
	// node before head node and change head node. 
	if ((*head)->priority > p) { 

		// Insert New Node before head 
		temp->next = *head; 
		(*head) = temp; 
	} 
	else if((*head)->priority == p && (*head)->priority_order > p2)
	{
		printf("\n--------------priorty_order in Leaves queue-------------\n");
		temp->next = *head; 
		(*head) = temp; 
	}
	/*else if((*head)->priority == p && (*head)->priority_order < p2)
	{
		temp->next = start->next; 
		start->next = temp; 
	}*/
	else { 

		// Traverse the list and find a 
		// position to insert new node 
		while (start->next != NULL && start->next->priority <=p) 
		{    if(start->next->priority ==p && start->next->priority_order >p2)
				break; 
			start = start->next; 
		} 

		// Either at the ends of the list 
		// or at required position 
		temp->next = start->next; 
		start->next = temp; 
	} 
} 


void delteme(leafNode **head_ref,node *d)  // delete the node that has this value
{
    leafNode* temp = (*head_ref), *prev; 
    printf("\n-------------- searching in LEaves queue---------------\n");

    if (temp != NULL && (temp->data)==d)
    { 
		printf("\n--------------deleting head 1 in Leaves queue---------------\n");
        (*head_ref) = (*head_ref)->next;   // Changed head 
		printf("%d",temp->data->size);
        free(temp);  
		//printf("%d",temp->data->size);
		temp= *head_ref;
		printf("%d",temp->data->size);        
		printf("\n-------------- deleting head 2 in Leaves queue ---------------\n");     // free old head 
        return; 
    } 
  
    // Search for the key to be deleted, keep track of the 
    // previous node as we need to change 'prev->next' 
    while (temp != NULL && d != (temp->data))
    { 
        prev = temp; 
        temp = temp->next; 
    } 
  
    // If key was not present in linked list 
    if (temp == NULL) 
	{
		printf("\n--------------i am null in Leaves queue---------------\n");
		return; 
	}
  printf("\n --------------yalhwwaaaay heheheheheehe----------\n");
    // Unlink the node from linked list 
	if(prev ==NULL)
	perror("\n------------------aywaaaa naaa in Leaves queue------------\n");
	else
	perror("\n------------aaaaaaaaaaaaaaaaaaaaaaaaaa in Leaves queue----------------\n");
    prev->next = temp->next; 
    printf("\n-------------- finished searching in Leaves queue---------------\n");  
	free(temp);  // Free memory 
	perror("\n---------------out leaves queue-------------\n");

}
/* Given a reference (pointer to pointer) to the head of a list 
   and a key, deletes the first occurrence of key in linked list */
void deleteleaf(struct leafNode **head_ref, int key, node ** d) 
{ 
    // find the first leafNode with suitable size, return the "data---> node" member then free the leafNode
	// (temp->data)->size/2 <= key && key <= (temp->data)->size
    struct leafNode* temp = *head_ref, *prev; 
    printf("\n------------- searching in deleting Leaves---------------\n");
    // If head node itself holds the key to be deleted 
    if (temp != NULL && (key <= (temp->data)->size))
    { 
		printf("\n--------------deleting head 1 in Leaves queue---------------\n");
        *head_ref = temp->next;   // Changed head 
		*d=temp->data; // return pointer to the node 
        free(temp);          
		printf("\n-------------- deleting head 2 in Leaves queue ---------------\n");     // free old head 
        return; 
    } 
  
    // Search for the key to be deleted, keep track of the 
    // previous node as we need to change 'prev->next' 
    while (temp != NULL && (key > (temp->data)->size))
    { 
        prev = temp; 
        temp = temp->next; 
    } 
  
    // If key was not present in linked list 
    if (temp == NULL) 
	{
		printf("\n--------------i am null in Leaves queue---------------\n");
		return; 
	}
 
    // Unlink the node from linked list 
	if(prev ==NULL)
	perror("\n------------------aywaaaa naaa in Leaves queue------------\n");
	else
	perror("\n------------aaaaaaaaaaaaaaaaaaaaaaaaaa in Leaves queue----------------\n");
    prev->next = temp->next; 
    printf("\n-------------- finished searching in Leaves queue---------------\n");  
	*d=temp->data; // return pointer to the node 
	free(temp);  // Free memory 
	perror("\n-----------------out leaves queue-------------\n");
} 






