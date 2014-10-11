//header files
#include "stdio.h"
#include "stdlib.h"
#include "buffer_mgr.h"
// for type bool
#include "dt.h"

// Create a node for page frame (Node of a buffer pool)
typedef struct page_Frame
{
//pointer to next frame
struct page_Frame *next_Page_Frame;
// Pointer to pool
void *pool_Pointer;
// count no of pages read and wrote to set read vs write counts
int pages_read,pages_wrote;
// node content
void *frame_content;
}page_Frame;

typedef struct frame_content
{
// page no of the file being read
PageNumber pageno;
// To check whether a page is dirty or not
bool dirty_flag;
// Fix count
int fix_count;
// pointer to content of node
char *frame;
// for FIFO and LRU
unsigned long timestamp;
int counter;
}frame_content;

// need a pointer to node for go to previous and next nodes
struct page_Frame *pointer_to_node;

// Define Linked list operations

//print buffer pool
void print_Buffer_Pool(pointer_to_node head);

//Insert a page frame into buffer pool
bool insert_Page_Frame(void *pool_Pointer,void *frame_content,pointer_to_node *new_node);

// Delete a page from buffer pool
bool delete_Page_Frame(void *pool_Pointer,pointer_to_node *node);

// Search for a page frame in the buffer pool
page_Frame *search_Page_Frame(void *pool_Pointer,pointer_to_node node);

// File associated and no of pages of file in buffer pool
int pages_of_file_Associated (char *fileName,pointer_to_node node);