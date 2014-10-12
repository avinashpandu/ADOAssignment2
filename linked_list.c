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
static pthread_mutex_t lock_insert_code ;
pthread_mutex_init (&lock_insert_code, NULL);
pthread_mutex_lock (&lock_insert_code);
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
pthread_mutex_unlock (&lock_insert_code);
}

// Delete a page from buffer pool
bool delete_Page_Frame(void *pool_Pointer,pointer_to_node *node)
{
pointer_to_node prev_pntr=NULL,curr_pntr=node,local;
RC ret;
bool val;
// obtain a lock on the block of code
static pthread_mutex_t lock_delete_code ;
pthread_mutex_init (&lock_delete_code, NULL);
pthread_mutex_lock (&lock_delete_code);
// Loop until the node equal to node provided
while ((curr_pntr != NULL) && curr_pntr->pool_Pointer!=pool_Pointer)
{
prev_pntr = curr_pntr;
curr_pntr = curr_pntr->next_Page_Frame;
}
// Change the pointers as required
if(curr_pntr != NULL)
{
local=curr_pntr;
val = TRUE;
	if(prev_pntr == NULL)
	*node = curr_pntr->next_Page_Frame;
	else
	prev_pntr->next_Page_Frame = curr_pntr->next_Page_Frame;
// free the memory of that node
free(local);
}
else
{
//if not found say node requested wasn't found
ret = RC_REQUSTED_PAGE_PAGE_NOT_FOUND;
val = FALSE;
printError (ret);
}
// unlock
pthread_mutex_unlock (&lock_delete_code);
ret val;
}


// Search for a page frame in the buffer pool
page_Frame *search_Page_Frame(void *pool_Pointer,pointer_to_node node)
{
pointer_to_node prev_pntr = NULL,curr_pntr=node;
RC ret;
// Lock the block of code
static pthread_mutex_t lock_search_code ;
pthread_mutex_init (&lock_search_code, NULL);
pthread_mutex_lock (&lock_search_code);
// Loop until last node
while (curr_pntr != NULL)
{
// Search for the node given
	if (curr_pntr->pool_pointer = pool_Pointer)
	// If we get it, break the loop
	goto exit;
prev_pntr = curr_pntr;
curr_pntr = curr_pntr->next_Page_Frame;
}
// If not say the node we looking for is not available
if (curr_pntr == NULL)
{
ret = RC_REQUSTED_PAGE_PAGE_NOT_FOUND;
printError (ret);
}
//unlock
pthread_mutex_unlock (&lock_search_code);
// return the node if found or return null
return curr_pntr;
}

// File associated
int pages_of_file_Associated (char *fileName,pointer_to_node node)
{
int no_Of_Pages;
pointer_to_node prev_pntr=NULL,curr_pntr=node;
BM_BufferPool *pool_local;
// Loop until last node 
while (curr_pntr != NULL)
{
// Look for the pages of that file passed in buffer pool
pool_local= (BM_BufferPool *) curr_pntr->pool_Pointer;
	if (pool_local->pageFile == fileName)
	// increment a counter if pages are found
	no_Of_Pages++;
prev_pntr = curr_pntr;
curr_pntr = curr_pntr->next_Page_Frame;
}
// return no of pages of the file
return no_Of_Pages;
}

