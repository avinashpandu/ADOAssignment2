//header files
#include "stdio.h"
#include "stdlib.h"
#include "dt.h"
#include "buffer_mgr.h"

// Create a node for page frame (Node of a buffer pool)
typedef struct page_Frame{};

// Define Linked list operations

//print buffer pool
void print_Buffer_Pool();

//Insert a page frame into buffer pool
bool insert_Page_Frame();

// Delete a page from buffer pool
bool delete_Page_Frame();

// Search for a page frame in the buffer pool
page_Frame *search_Page_Frame();

// File associated and no of pages of file in buffer pool
int pages_of_file_Associated (char *fileName,);





