#include <stdio.h>
#include <stdlib.h>
#include "linkedList.h"

#define LIST_END -1
//#define LIST_FIRST 0

//node definition for linked list
typedef struct node{
	int index; //index of the node
	void* obj; //object data
	void* next; //pointer to the next

} node_t;

//Inner functions (cannot used at the outside of this file)
node_t* genNode(void)
{
	node_t* ndPtr;
	
	//allocate memory for creating the node
	ndPtr = (node_t*)malloc(sizeof(node_t));
	if (ndPtr != NULL)
	{
		ndPtr->next = NULL;
		ndPtr->obj = NULL;
	}
	
	return ndPtr;	
}

node_t* travelList(node_t* ndPtr, int offset)
{
	//return for wrong input
	if (ndPtr == NULL || offset <-1)
	{
		printf("[ERROR] either ndPtr or offset is wrong! (offset : %i)\n", offset);
		return NULL;
	}	
	
	//repeat travelling until the node is the end or offset becomes 0
	while ( list_isEndNode(ndPtr) == 0 && offset != 0)
	{
		ndPtr = ndPtr->next;
		offset--;
	}
	
	return ndPtr;
}

int updateIndex(node_t* ndPtr)
{
	int len=0;
	int index = ndPtr->index;
	
	while ( list_isEndNode(ndPtr) == 0 )//travel until it is the end node
	{
		ndPtr = ndPtr->next; //travel once
		ndPtr->index = ++index;
		len++;//increase the length variable
	}
	
	return len;
}

//API function
//functions for list creating and editing-----------------------------

/*
	description : function for making and initializing a list
				(This must be called for using Linked List)
	input parameters : NONE
	return value : pointer to the list (header node)
					(this pointer will be used for further handling the list)
	
	operation : 1. generate a node (allocate memory)
	            2. initialize the members of the nodes
	            3. return the generated node (this is the header node, which can be the list itself)
*/
void* list_genList(void)
{
	node_t* ndPtr = genNode(); //make the header node
	
	if (ndPtr != NULL)
	{
		ndPtr->obj = NULL;
		ndPtr->next = NULL;
	}
	
	return ndPtr;
}

/*
	description : adding a data object to the list
	input parameters : obj - data object to add to the list
	                   list - target list
	return value : addition result (0 - succeeded, -1 - failed)
	
	operation : 1. make a new node
	            2. find the last node in the list
	            3. make the last node's next pointer to point the new node
	            4. update the index
*/
int list_addTail(void* obj, void* list)
{
	node_t* listPtr = (node_t*)list;
	node_t* ndPtr;
	node_t* newNdPtr;
	
	//parameter checking
	if (listPtr == NULL || obj == NULL)
	{
		printf("[ERROR] Failed to do addTail : list pointer is NULL or object indicates NULL! (%u, %u)\n", list, obj);
		return -1;
	}
	
	//generate new node
	newNdPtr = genNode();
	if (newNdPtr == NULL)
	{
		printf("[ERROR] Failed to do addTail : Failed to create a node\n");
		return -1; //indicate to the upper function that node addition is failed 
	}
	newNdPtr->obj = obj;
	
	//add node to the list tail
	listPtr = travelList(list, LIST_END);
	listPtr->next = newNdPtr;
	newNdPtr->index = listPtr->index+1;
	
	return 0;
}


/*
	description : adding a data object to the next position of the input node
	input parameters : obj - data object to add to the list
	                   nd - target node
	return value : addition result (0 - succeeded, -1 - failed)
	
	operation : 1. make a new node
	            2. make the input node's next pointer to point the new node
	            4. update the index of the nodes after the new node
*/
int list_addNext(void* obj, void* nd)
{
	node_t* ndPtr = (node_t*)nd;
	node_t* newNdPtr;
	node_t* nextNdPtr;
	
	//parameter checking
	if (ndPtr == NULL || obj == NULL)
	{
		printf("[ERROR] Failed to do addNext : node pointer is NULL or object indicates NULL! (%u, %u)\n", ndPtr, obj);
		return -1;
	}
	
	//generate new node
	newNdPtr = genNode();
	if (ndPtr == NULL)
	{
		printf("[ERROR] Failed to do addNext :  Failed to create a node\n");
		return -1; //indicate to the upper function that node addition is failed 
	}
	newNdPtr->obj = obj;
	
	//add node to the next tail
	nextNdPtr = ndPtr->next;
	
	ndPtr->next = newNdPtr;
	newNdPtr->index = ndPtr->index+1;
	
	newNdPtr->next = nextNdPtr;
	
	//update indices of the further nodes
	updateIndex(newNdPtr);
	
	return 0;
}


//functions for list observation -----------------------------

/*
	description : tell whether the input node is the last node of the list or not
	input parameters : nd - target node
	return value : 0 - it is not the last node, 1 - it i sthe last node, -1 - it is weird
	
	operation : 1. make a new node
	            2. make the input node's next pointer to point the new node
*/
int list_isEndNode(void* nd)
{
	node_t* ndPtr = (node_t*)nd;
	if (ndPtr == NULL)
	{
		return -1;
	}
	
	return (ndPtr->next == NULL);
}


/*
	description : calculate the number of nodes in the list
	input parameters : list - target list
	return value : number of nodes in the list
	
	operation : 1. point to the next node
	            2. count 1
	            3. if the node is not the last one, the repeat from 1
*/
int list_len(void* list)
{
	node_t* listPtr = (node_t*)list;
	int len=0;
	
	//parameter checking
	if (listPtr == NULL)
	{
		printf("[ERROR] Failed to calculate list length : list pointer is NULL! (%u)\n", list);
		return -1;
	}
	
	while ( list_isEndNode(listPtr) == 0 )//travel until it is the end node
	{
		listPtr = listPtr->next; //travel once
		len++;//increase the length variable
	}
	
	return len;
}


/*
	description : get the next node of the input node
	input parameters : nd - input node (we would like to get the node next to this input node)
	return value : the next node pointer
	
	operation : 1. if the input node is not the last node
	            2. return the node that the input node's next pointer points to
*/
void* list_getNextNd(void* nd)
{
	node_t* ndPtr = (node_t*)nd;
	
	//parameter checking
	if (ndPtr == NULL)
	{
		printf("[ERROR] Failed to get next node : node pointer is NULL!(%u)\n", nd);
		return NULL;
	}
	
	if (list_isEndNode(ndPtr) == 1 )//travel until it is the end node
	{
		printf("[WARNING] node pointer is the end node! the next nd will be NULL\n");
	}
	
	return (void*)travelList(ndPtr, 1);
}

/*
	description : get the node with specific index
	input parameters : index - the index of the node that we would like to get
	                   list - the linked list that we search from
	return value : the node whose index is the same as the input index
	
	operation : 1. go through the list
	            2. if there is the node whose index is the same, then return it
*/
void* list_getIndexNd(int index, void* list)
{
	node_t* listPtr = (node_t*)list;
	
	if (listPtr == NULL)
	{
		printf("[ERROR] Failed to get the node with index : list pointer is NULL! (%u)\n", listPtr);
		return NULL;
	}
	
	while (list_isEndNode(listPtr) == 0 )//travel until it is the end node
	{
		listPtr = listPtr->next;
		if (listPtr->index == index)
		{
			return listPtr;
		}
	}
	
	printf("[ERROR] Failed to get the node with index : cannot find the node for index %i in this list!\n", index);
	return NULL;
}


/*
	description : get the node with specific index
	input parameters : index - the index of the node that we would like to get
	                   list - the linked list that we search from
	return value : the node whose index is the same as the input index
	
	operation : 1. go through the list
	            2. if there is the node whose index is the same, then return it
*/
void* list_srchNd(int (*matchFunc)(void* obj, void* cond), void* cond, void* list)
{
	node_t* listPtr = (node_t*)list;
	
	if (listPtr == NULL)
	{
		printf("[ERROR] search node fail : list pointer is NULL! (%u)\n", listPtr);
		return NULL;
	}
	
	while (list_isEndNode(listPtr) == 0 ) //travel until it is the end node
	{
		listPtr = listPtr->next;
		if (matchFunc(listPtr->obj, cond) == 1)
		{
			return listPtr;
		}
	}
	
	printf("[ERROR] search node fail : no matched node!\n");
	return NULL;
}


//functions for list object handling -----------------------------


/*
	description : repeat processing a function for each node
	input parameters : func - the function that will be repeated for each node (the parameter void* obj is equal to the node->obj)
	                   list - the linked list that we would like to process
	return value : the number of nodes that are processed
	
	operation : 1. until the node pointer reaches to the last one
	            2. go to the next node and call func() with argument node->obj
*/
int list_repeatFunc(void (*func)(void* obj), void* list)
{
	node_t* listPtr = (node_t*)list;
	int len=0;
	
	//parameter checking
	if (listPtr == NULL || func == NULL)
	{
		printf("[ERROR] Repeat function fail : list pointer or func is NULL! (%u %u)\n", list, func);
		return -1;
	}
	
	while ( list_isEndNode(listPtr) == 0 )//travel until it is the end node
	{
		listPtr = listPtr->next; //travel once
		func(listPtr->obj);
		len++;//increase the length variable
	}
	
	return len;
	
}


/*
	description : get the pointer to the object that the input node holds
	input parameters : nd - the target node that we would like to get object from
	return value : pointer to the object
	
	operation : 1. return the node->obj
*/
void* list_getNdObj(void* nd)
{
	node_t* ndPtr = (node_t*)nd;
	
	//parameter checking
	if (ndPtr == NULL)
	{
		printf("[ERROR] failed to get object : node pointer is NULL! (%u)\n", nd);
		return NULL;
	}
	
	return (void*)ndPtr->obj;
}


