//header files
#include "stdio.h"
#include "stdlib.h"
//include the node file
#include "linked_list.h"

// Define Linked list operations

//print buffer pool
void print_Buffer_Pool()
{
// start with head node
// check if there are first is null 
// If yes say list empty
// If no, traverse to last node (i.e null pointer) and print contents of each node
}

//Insert a page frame into buffer pool
bool insert_Page_Frame()
{
// allocate memory for new node
// check for the new pointer being added ,if not null
// set current to node read from insert parameters
// track to last node (not null)
// insert a node
}

// Delete a page from buffer pool
bool delete_Page_Frame()
{
// Loop until the node equal to node provided
// Change the pointers as required
// free the memory of that node
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

