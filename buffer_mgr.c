#include "stdio.h"
#include "stdlib.h"
#include "buffer_mgr.h"
// for type bool
#include "dt.h"

// read and write tags 
RC rtag=RC_OK,wtag=RC_OK;

frame_content *tempframe=NULL;

// for mutexes
static pthread_mutex_t lock_initbufferpool=PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t lock_shutdown=PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t lock_forceflush=PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t lock_pin=PTHREAD_MUTEX_INITIALIZER;
//static pthread_mutex_t lock_unpin=PTHREAD_MUTEX_INITIALIZER;

// Head node pointer
pointer_to_node head_ptr=NULL;

// for time
int timeglobal = -100;

RC initBufferPool(BM_BufferPool *const bm, const char *const pageFileName, 
		  const int numPages, ReplacementStrategy strategy, 
		  void *stratData)
{
RC rc=RC_OK;
int ctr;
page_Frame *node_of_pool;
frame_content *frame;
BM_BufferPool *local;
	
// create a file handle too
SM_FileHandle *fh;
bool check;
// Obtain a lock on the code block
pthread_mutex_lock(&lock_initbufferpool);

//Check if the buffer pool exists
node_of_pool = what_pools_active(pageFileName,head_ptr);

//Check for pointer existence,if null then create a pool of required 
	if(node_of_pool == NULL)
    {
        fh=(SM_FileHandle *)malloc(sizeof(SM_FileHandle));
        if(fh==NULL)
        return RC_FILE_HANDLE_NOT_INIT;
        openPageFile(pageFileName,sh);
		
		// assign all parameters to 
        bm->pageFile=pageFileName;
        bm->numPages=numPages;
        bm->strategy=strategy;
        bm->mgmtData=fh;

        //initialize a frame with passed parameters
		tempframe = (frame_content *) malloc(numPages,sizeof(frame_content));
		//If false,allocate memory to the buffer pool based on the no of pages passed.
		if (tempframe !=NULL)
		{
			for (ctr=0;ctr<numPages;ctr++)
			{
			(tempframe+ctr)->frame = initpf (numPages);
			tempframe[i].dirty_flag = false;
			tempframe[i].fix_count=0;
			tempframe[i].pageno = -1;
			}
		}
		frame = tempframe;
		
		if (frame != NULL)
        rc = RC_OK;
		else 
		rc = RC_FILE_HANDLE_NOT_INIT;
		
		//Check the return code of insert ,if true,throw success else page frame cannot be intialised
        check = insert_node(bm,frame,&head_ptr);
		if (check == FALSE)
        rc=RC_FILE_HANDLE_NOT_INIT;
    }
	else
	{
	local = node_of_pool-> pool_Pointer;
	//Set the parameters of bm
	bm->numPages = numPages;
	bm->strategy = strategy;
	bm->mgmtData = tempframe->mgmtData;
	frame_content = node_of_pool->frame_content;
	
	//Call the insert method from linked list and create the number of page frames based on the pages passed.
	check = insert_node(bm,frame,&head_ptr);
	if (check == FALSE)
    rc=RC_FILE_HANDLE_NOT_INIT;
	}

// unlock the block	
pthread_mutex_unlock(&lock_initbufferpool);
return rc;
}


RC shutdownBufferPool(BM_BufferPool *const bm)
{
RC rc=RC_OK;
int *fixc,*gfc,i,accessctr;
page_Frame *pf;
frame_content *fc;
char *fr;
//set that the page is not pinned i.e. it is false
bool pin = FALSE;
// Obtain a lock on the code block
pthread_mutex_lock(&lock_shutdown);

//get the fixed counts
fixc=getFixCounts(bm);
//get the frame contents
gfc=getFrameContents(bm);

for(i=0 ; i < bm->numPages ; i++)
{
	//if the fix count is greater than zero then,means that the page has been pinned.
    if(fixounts[i] > 0)
    pin=TRUE;
}
//check if the page is dirty and write back to disk
if (pin == FALSE)
{
	pf = search_Page_Frame(bm,head_ptr);
	accessctr = pages_of_file_Associated(bm->pageFile,head_ptr);
	if (pf!=NULL)
	{
	fc = pf->frame_content;
		if (fc!=NULL)
		{
			for (i=0; i< bm->numPages; i++)
			{
			fr = fc[i].frame;
				if (fr[i].dirty_flag== TRUE)
				{
					if (writeBlock(fc[i].pageno,bm->mgmtData,fr) == RC_OK)
					rc = RC_OK;
					else
					rc = RC_WRITE_FAILED;
				}
			// Check if pool associated only one file and if yes then free frame
			if (accessctr == 1)
			free (fr);
			}
		}
		if (accessctr == 1)
		free (fc);
		fc = NULL;
		delete_Page_Frame (bm,&head_ptr);
	}
	// Close Page File that is associated with it
	if (accessctr == 1)
	{
	closePageFile(bm->mgmtData);
	// Free the memory that has been allocated to the buffer pool.
	free (bm->mgmtData);
	}
}
// Unlock
pthread_mutex_unlock(&lock_shutdown);
return rc;
}


RC forceFlushPool(BM_BufferPool *const bm)
{
RC rc=RC_OK;
// Local Variables
char *fr;
frame_content *fc;
page_Frame *pf;
// Obtain a lock on the code block
pthread_mutex_lock (&lock_forceflush);
pf = search_Page_Frame(bm,head_ptr);
if (pf!=NULL)
{
fc = pf->frame_content;
	if (fc!=NULL)
	{
		for (i=0; i< bm->numPages; i++)
		{
		fr = fc[i].frame;
		// Check if the page is dirty and write back to disk}
			if (fr[i].dirty_flag== TRUE)
			{
				if (writeBlock(fc[i].pageno,bm->mgmtData,fr) == RC_OK)
				rc = RC_OK;
				else
				rc = RC_WRITE_FAILED;
				fc.dirty_flag = FALSE;
				pf->pages_wrote++;
			}
		}
	}
}
// unlock
pthread_mutex_unlock(&lock_forceflush);
return rc;
}

// Buffer Manager Interface Access Pages
RC markDirty (BM_BufferPool *const bm, BM_PageHandle *const page)
{
RC rc=RC_OK;
// Local variables
page_Frame *pf;
frame_content *fc;
int i;
pf = search_Page_Frame(bm,head_ptr);
fc = pf->frame_content;
//Traverse the contents of the page frame from the 1st node till last.If dirty,RC_OK else,mark dirty failed error. 
for (i=0;i<bm->numPages;i++)
{
	if (((fc+i)->pageno) == page->pageNum)
	{
	(fc+i)->dirty_flag = TRUE;
	rc = RC_OK;
	}
rc = RC_WRITE_FAILED;
}
return rc;
}


RC unpinPage (BM_BufferPool *const bm, BM_PageHandle *const page)
{
RC rc;
//Local Variables
page_Frame *pf;
frame_content *fc;
int page_count,i;
// Check for the requested page in buffer
pf = search_Page_Frame (bm,head_ptr);
page_count = bm->numPages;
// if available check for fix_counts
if (pf !=NULL)
{
fc = pf->frame_content;
	for (i=0;i<page_count;i++)
	{
		if (((fc+i)->pageno) == page->pageNum)
		{
		// if zero then check whether page was dirtied
			if (((fc+i)->dirty_flag)== TRUE)
			{
			// if dirty write to disk and unpin
			rc = writeBlock(page->pageNum,bm->mgmtData,page->data);
			(fc+i)->fix_count --;
			// if not zero then throw error saying page cant be unpinned
			}
			else 
			rc = RC_WRITE_FAILED;
		}
	}
}
return rc;
}

RC forcePage (BM_BufferPool *const bm, BM_PageHandle *const page)
{
RC rc;
// Local Variables
page_Frame *pf;
// Check for page frame existence
pf = search_Page_Frame (bm,head_ptr);
if (pf !=NULL)
{
	//Check for file handle null 
	if (bm->mgmtData !=NULL)
	{
	writeBlock(page->pageNum,bm->mgmtData,page->data);
	pf->pages_wrote ++;
	rc = RC_OK;
	}
	else
	// #if error file not found.
	rc= RC_FILE_NOT_FOUND;
}
return rc;
}

RC pinPage (BM_BufferPool *const bm, BM_PageHandle *const page, 
	    const PageNumber pageNum)
{
RC rc,rtag,wtag;
bool rettag; //for checking doalgorithm return
// Local Variables
page_Frame *pf;
frame_content *fc,*pr; //pr is for page_return
int page_count,i,flag=1; // flag is for check for an empty frame
ReplacementStrategy rs = bm->strategy;
page_count = bm->numPages;
// Obtain a lock on the code block
pthread_mutex_lock(&lock_pin);
// Check for the page existence in the buffer pool
pf = search_Page_Frame (bm,head_ptr);
if (pf !=NULL)
{
fc = pf->frame_content;
	// Check for availability till end of page count 
	for (i=0;i<page_count;i++)
	{
		if (((fc+i)->pageno) > -1 )
		{
		flag=0;
		// if already available say already available and no need to pin again
			if (((fc+i)->pageno) == pageNum)
			{
			(fc+i)->timeStamp = timeglobal++;
			page -> pageNum = pageNum;
			page->data = (fc+i)-> frame;
			((fc+i)->fix_count)++;
			// unlock
			pthread_mutex_unlock(&lock_pin);
			rc = RC_OK;
			return rc;
			}
		}
	} //Done with checking whether it is available 
		
	// if not check for pool whether is free, and assign page available
	for (i<0;i<page_count;i++)
	{
		if (((fc+i)->pageno) == -1 )
		{
		pr = fc+i;
		flag= 1;
		break;
		}
	}
}
// No page frame initialization
else
{
pr = fc;
(fc->counter)++;
(fc+i)->timeStamp = timeglobal++;
flag=1;
}

//Check for the flag and see if there is an empty flag
if (flag==1)
{
page->pageNum = pageNum;
page->data = pr->frame;
wtag = RC_OK;
	// if free pin the page
	if (readBlock(pageNum,bm->mgmtData,pr->frame) == RC_READ_NON_EXISTING_PAGE)
	rtag = writeBlock(page_count+1,bm->mgmtData,page->data);
	else
	{
	// update node attributes (time and counter)
	rtag = RC_OK;
	pf->pages_read++;
	fc->pageno = pageNum;
	fc->fix_count++;
	}
}
else
{
	// if not free check for the replacement algorithm called for
	if (rs == RS_FIFO || rs == RS_LRU)
	// get the proper page to replace
	rettag = doalgorithm (bm,pageNum,page,rs);
	else 
	{
	rettag = FALSE;
	rc = RC_INVALID_STRATEGY;
	}
}
if (flag==1 || rtag == RC_OK)
rc = RC_OK;
else
rc = RC_WRITE_FAILED;
return rc;
}

// Statistics Interface
PageNumber *getFrameContents (BM_BufferPool *const bm)
{
PageNumber *page_array;
int i;
//Local Variables
frame_content *fc;
pointer_to_node *ptn;
//check for the frame existence.
ptn = search_Page_Frame (head_ptr,bm);
//allocate memory to the boolean array
page_array = (PageNumber *) malloc(bm->numPages,sizeof(PageNumber));
if (ptn !=NULL)
{
//traverse till the end of page frame.
fc = ptn->frame_content;
	if (fc!=NULL)
	{
	//Check if the page is dirty.if yes,set true
		for (i=0;i<bm->numPages;i++)
		page_array[i]=fc[i].pageno;
	}
}
//return the array 
return page_array;
}

bool *getDirtyFlags (BM_BufferPool *const bm)
{
bool *dirty_array;
int i;
//Local Variables
frame_content *fc;
pointer_to_node *ptn;
//check for the frame existence.
ptn = search_Page_Frame (head_ptr,bm);
//allocate memory to the boolean array
dirty_array = (bool *) malloc(bm->numPages,sizeof(bool));
if (ptn !=NULL)
{
//traverse till the end of page frame.
fc = ptn->frame_content;
	if (fc!=NULL)
	{
	//Check if the page is dirty.if yes,set true
		for (i=0;i<bm->numPages;i++)
		dirty_array[i]=fc[i].dirty_flag;
	}
}
//return the array 
return dirty_array;
}

int *getFixCounts (BM_BufferPool *const bm)
{
int i,*fc_array;
//Local Variables
pointer_to_node *ptn;
frame_content *fc;
//check for the frame existence.
ptn = search_Page_Frame (head_ptr,bm);
//allocate memory to the integer array
fc_array = (int *) malloc(bm->numPages,sizeof (int));
	
if (ptn !=NULL)
{
//traverse till the end of page frame.
fc = ptn->frame_content;
	if (fc!=NULL)
	{
	//Check the fix count of the pages in the page frame .
		for (i=0;i<bm->numPages;i++)
		fc_array[i]=fc[i].fix_count;
	}
}
//return the array 
return fc_array;
}

int getNumReadIO (BM_BufferPool *const bm)
{
int i;
pointer_to_node *ptn;
// Search for the node that was requested for
ptn = search_Page_Frame (head_ptr,bm);
// When found get the no of pages read
// if not return zero
if (ptn == NULL)
i =0;
// If found return no of pages
else
i= ptn->pages_read;
return i;
}


int getNumWriteIO (BM_BufferPool *const bm);
{
int i;
pointer_to_node *ptn;
// Search for the node that was requested for
ptn = search_Page_Frame (head_ptr,bm);
// When found get the no of pages write
// if not return zero
if (ptn == NULL)
i =0;
// If found return no of pages
else
i= ptn->pages_wrote;
return i;
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

// Check pools that are active
page_Frame *what_pools_active(char *filename,pointer_to_node head_ptr)
{
    pointer_to_node prev_ptr=NULL;
    pointer_to_node curr_ptr=head_ptr;
	
    BM_BufferPool *bp;
	
    while(curr_ptr!=NULL)
    {
        bp=(BM_BufferPool *)curr_ptr->pool_Pointer;
        if(bp->pageFile==filename)
        break;
        prev_ptr = curr_ptr;
        curr_ptr = curr_ptr->next_Page_Frame;
    }
    return curr_ptr;
}

// To allocate a page
char *initpf (const int np)
{
int i;
char *page;
page = (char *)malloc (PAGE_SIZE);
	if (page != NULL)
	{
	for(i=0;i < PAGE_SIZE ; i++)
    page[i]='\0';
    }
}