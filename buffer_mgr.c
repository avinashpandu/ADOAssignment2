#include "stdio.h"
#include "stdlib.h"
#include "buffer_mgr.h"
// for type bool
#include "dt.h"

RC initBufferPool(BM_BufferPool *const bm, const char *const pageFileName, 
		  const int numPages, ReplacementStrategy strategy, 
		  void *stratData)
{//Check if the buffer pool exists
//Check for pointer existence,if null throw an error.
//If false,allocate memory to the buffer pool based on the no of pages passed.
//Call the insert method from linked list and create the number of page frames based on the pages passed.
//Check the return code of insert ,if true,throw sucess else page frame cannot be intialised
//Set the parameters of bm
}
RC shutdownBufferPool(BM_BufferPool *const bm)
{
//set that the page is not pinned i.e. it is false
//get the fixed counts
//get the frame contents
//if the fix count is greater than zero then,means that the page has been pinned.
//call the respective method to check if the page is dirty and write back to disk
Free the memory that has been allocated to the buffer pool.
}
RC forceFlushPool(BM_BufferPool *const bm)
{

//call the respective method to check if the page is dirty and write back to disk}

}
// Buffer Manager Interface Access Pages
RC markDirty (BM_BufferPool *const bm, BM_PageHandle *const page)
{
//Traverse the contents of the page frame from the 1st node till last.If dirty,RC_OK else,mark dirty failed error. 
}
RC unpinPage (BM_BufferPool *const bm, BM_PageHandle *const page)
{
// Check for the requested page in buffer
// if available check for fix_counts
// if zero then check whether page was dirtied
// if dirty write to disk and unpin
// if not dirty then unpin directly
// if not zero then throw error saying page cant be unpinned
}
RC forcePage (BM_BufferPool *const bm, BM_PageHandle *const page)
{
Check for page frame existence
Check if the page is dirty.If yes,then write it to the page file.
#if error file not found.
}
RC pinPage (BM_BufferPool *const bm, BM_PageHandle *const page, 
	    const PageNumber pageNum)
{
// Check for the page existence in the buffer pool
// if already available say already available and no need to pin again
// if not check for pool whether is free
// if free pin the page
// if not free check for the replacement algorithm called for
// get the proper page to replace
// update node attributes (time and counter)
// add node to buffer pool
}

// Statistics Interface
PageNumber *getFrameContents (BM_BufferPool *const bm)
{
//check for the frame existence.
//allocate memory to the integer array
//traverse till the end of page frame.
//return the array 
}
bool *getDirtyFlags (BM_BufferPool *const bm)
{
//check for the frame existence.
//allocate memory to the integer array
//traverse till the end of page frame.
//Check if the page is dirty.if yes,set true
//return the array 
}
int *getFixCounts (BM_BufferPool *const bm)
{
//check for the frame existence.
//allocate memory to the integer array
//traverse till the end of page frame.
//Check the fix count of the pages in the page frame .
//return the array 
}
int getNumReadIO (BM_BufferPool *const bm);
int getNumWriteIO (BM_BufferPool *const bm);
