//header files
#include "stdio.h"
 #include "stdlib.h"
//include the node file
#include "linked_list.h"

// Define Linked list operations

//print buffer pool
void print_Buffer_Pool(pointer_to_node head)
{
BM_BufferPool *node;
// start with head node
pointer_to_node prev_pntr=NULL,curr_pntr=head;
int ctr=0;
// check if there are first is null
if (curr_pntr == NULL)
// If yes say list empty
printf("\nPool is empty...It has absolutely nothing");
else
{
// If no, traverse to last node (i.e null pointer) and print contents of each node
	while (curr_pntr != NULL)
	{
	ctr++;
	prev_pntr = curr_pntr;
	curr_pntr = curr_pntr -> next_Page_Frame;
	node = (BM_BufferPool *) prev_pntr -> pool_pointer;
	printf ("\n%d node contents are: %s",ctr, node->pageFile);
	}
}
}

//Insert a page frame into buffer pool
bool insert_Page_Frame(void *pool_Pointer,void *frame_content,pointer_to_node *new_node)
{
pointer_to_node new_nodel,prev_pntr,curr_pntr;
// obtain a lock on this method 
*******************************
// allocate memory for new node
new_nodel = malloc(sizeof(page_Frame));
// check for the new pointer being added ,if not null
if (new_nodel == NULL)
printf("\n Node to insert has a problem!!");
else 
{
// set current to node read from insert parameters
new_nodel->frame_content = frame_content;
new_nodel->page_read = 0;
new_nodel->page_write = 0;
new_nodel->pool_Pointer = pool_Pointer;
prev_pntr = NULL;
curr_pntr = *new_node;
// track to last node (not null)
	while (curr_pntr!=NULL)
	{
	prev_pntr = curr_pntr;
	curr_pntr = curr_pntr->next_Page_Frame;
	}
// insert a node
	if(prev_pntr==NULL)
	*new_node = new_nodel;
	else
	prev_pntr->next_Page_Frame = new_nodel;
}
// unlock
******************************** 
}

// Delete a page from buffer pool
bool delete_Page_Frame()
{
// obtain a lock on the block of code
// Loop until the node equal to node provided
// Change the pointers as required
// free the memory of that node
// unlock
}

// Search for a page frame in the buffer pool
page_Frame *search_Page_Frame()
{
// Loop until last node
// Search for the node given
// If we get it, break the loop 
// If not say the node we looking for is not available
// return the node if found or return null
}

// File associated
int pages_of_file_Associated (char *fileName,)
{
// Loop until last node
// Look for the pages of that file passed in buffer pool
// increment a counter if pages are found
// return no of pages of the file
}

