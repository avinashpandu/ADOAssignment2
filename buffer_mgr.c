#include "stdio.h"
#include "stdlib.h"
#include "buffer_mgr.h"
// for type bool
#include "dt.h"

RC rtag=RC_OK,wtag=RC_OK;

RC initBufferPool(BM_BufferPool *const bm, const char *const pageFileName, 
		  const int numPages, ReplacementStrategy strategy, 
		  void *stratData)
{
// Obtain a lock on the code block
//Check if the buffer pool exists
//Check for pointer existence,if null throw an error.
//If false,allocate memory to the buffer pool based on the no of pages passed.
//Call the insert method from linked list and create the number of page frames based on the pages passed.
//Check the return code of insert ,if true,throw sucess else page frame cannot be intialised
//Set the parameters of bm
// unlock the block
}
RC shutdownBufferPool(BM_BufferPool *const bm)
{
// Obtain a lock on the code block
//set that the page is not pinned i.e. it is false
//get the fixed counts
//get the frame contents
//if the fix count is greater than zero then,means that the page has been pinned.
//call the respective method to check if the page is dirty and write back to disk
// Free the memory that has been allocated to the buffer pool.
// Unlock
}
RC forceFlushPool(BM_BufferPool *const bm)
{
// Obtain a lock on the code block
//call the respective method to check if the page is dirty and write back to disk}
// unlock
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
// Check for page frame existence
// Check if the page is dirty.If yes,then write it to the page file.
// #if error file not found.
}
RC pinPage (BM_BufferPool *const bm, BM_PageHandle *const page, 
	    const PageNumber pageNum)
{
// Obtain a lock on the code block
// Check for the page existence in the buffer pool
// if already available say already available and no need to pin again
// if not check for pool whether is free
// if free pin the page
// if not free check for the replacement algorithm called for
// get the proper page to replace
// update node attributes (time and counter)
// add node to buffer pool
// unlock
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
int getNumReadIO (BM_BufferPool *const bm)
{
// Search for the node that was requested for
// When found get the no of pages read
// if not return zero
// If found return no of pages
}
int getNumWriteIO (BM_BufferPool *const bm);
{
// Search for the node that was requested for
// When found get the no of pages wrote
// if not return zero
// If found return no of pages
}

// The algorithm must return whether it is success or not
bool doalgorithm(BM_BufferPool * const bm, const PageNumber pageNum, BM_PageHandle * const page, ReplacementStrategy rs) 
{
	page_Frame *pf;
	char *ra;
	int i,j;
	int pages_per_block = bm->numPages;
	frame_content *page_to_replace,*content,*no_write_pages[pages_per_block],*next_page_content,*replace_content;
	// Search for a page passed
	pf = search_Page_Frame(head_ptr, bm);
	page_to_replace = NULL;
	// See which page to replace 
	//code block starts
	content  = pf->frame_content;
	// Initialize all the blocks to null
	for (i = 0; i < pages_per_block; i++) 
	no_write_pages[i] = NULL;
	
	// Check for fixed count of all frames who has fixed count more than zero
	for (i = 0; i < pages_per_block; i++) 
	{
		// if fixcount is zero then write them to array took
		if ((content[i].fixcounts) == 0) 
		{
			no_write_pages[j] = (content+i);
			j++;
		}
	}

	// no of pages that has no write pages 
    int no_write_pages_size= sizeof (no_write_pages);

	// get a replace page in the first one then loop
	replace_content = no_write_pages[0];
	// get the 
	for (i = 0; i < no_write_pages_size; i++) 
	{
		next_page_content = no_write_pages[i];
		// Until last frame of a pool
		if(next_page_content!=NULL)
		{
		// If FIFO look at the counter and replace with immediate counter
				if(rs == RS_FIFO)
				{
				if ((replace_content->counter) > (next_page_content->counter))
				replace_content = next_page_content;
				}
		// If LRU Look at the time that inserted (Count it up)
		else if(rs ==RS_LRU)
			{
	            if(replace_content->timeStamp > next_page_content->timeStamp)
				replace_content = next_page_content;
			}
		}
	}
	// Code block ends
	
	
	// assign replace 
	page_to_replace = replace_content;
	// if a page returned to replace is null
	if(page_to_replace==NULL)
    return false;
	
	ra = page_to_replace->frame;
		
	// Page replaced need to be written of it is dirty
	// Check for the dirty flag of the page
		if (page_to_replace->dirty_flag == TRUE) 
			{
			wtag = writeBlock(page_to_replace->pageno, bm->mgmtData, ra);
			page_to_replace->dirty_flag=FALSE;
			pf->pages_wrote++;
			}
	
	// Read the block needed
	rtag = readBlock(pageNum, bm->mgmtData, ra);
	// 
		if(rtag==RC_READ_NON_EXISTING_PAGE)
        rtag = appendEmptyBlock(bm->mgmtData);
		
    pf->pages_read++;
	page->pageNum  = pageNum;
	
	// send data
	page->data = page_to_replace->frame;
	// Equal page numbers
    page_to_replace->pagenums = pageNum;
	// Increment 
    page_to_replace->fixcounts = page_to_replace->fixcounts+1;
	// increment pages to replace counter by one 
	page_to_replace->counter = page_to_replace->counter + 1;
	
	//Check for read and write tags and return whatever necessary
	if (rtag == RC_OK && wtag == RC_OK)
	return true; 
	else
	return false;
}