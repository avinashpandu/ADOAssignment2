#include "stdio.h"
#include "stdlib.h"
#include "buffer_mgr.h"
// for type bool
#include "dt.h"

RC initBufferPool(BM_BufferPool *const bm, const char *const pageFileName, 
		  const int numPages, ReplacementStrategy strategy, 
		  void *stratData);
RC shutdownBufferPool(BM_BufferPool *const bm);
RC forceFlushPool(BM_BufferPool *const bm);

// Buffer Manager Interface Access Pages
RC markDirty (BM_BufferPool *const bm, BM_PageHandle *const page);
RC unpinPage (BM_BufferPool *const bm, BM_PageHandle *const page)
{
// Check for the requested page in buffer
// if available check for fix_counts
// if zero then check whether page was dirtied
// if dirty write to disk and unpin
// if not dirty then unpin directly
// if not zero then throw error saying page cant be unpinned
}
RC forcePage (BM_BufferPool *const bm, BM_PageHandle *const page);
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
PageNumber *getFrameContents (BM_BufferPool *const bm);
bool *getDirtyFlags (BM_BufferPool *const bm);
int *getFixCounts (BM_BufferPool *const bm);
int getNumReadIO (BM_BufferPool *const bm);
int getNumWriteIO (BM_BufferPool *const bm);
