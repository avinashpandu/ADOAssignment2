		**Assignment 2: Buffer Manager**
****************************************************

					**Team:knariset,asachith,plal1**
					********************************

CONTENTS
*********
1)Instructions to run the code
2)Additional functionalities
2)Description of functions used
3)Additional Test Cases and Additional error checks
4)Implementation

*****************************************************************

1)Instructions to run the code
*******************************

a)For executing mandatory test cases:

1) In the terminal,navigate to the assignment directory.

2) Type: 
	make -f makefile1

3) ./assign1



*****************************************************************

2)Additional functionalities
**************************
1)We have implemented Least recently used algorithm as an additional replacement strategy.

2)We have made the buffer pool functions thread safe.

3)We have included additional test cases and additional error checks.

3)Description of functions used
********************************

	Function :initBufferPool
	-------------------------

1)Obtain a lock on the code block for making the #function(application) thread safe.
2)Check for buffer pool existence.
3)Initialize the parameters of the buffer pool and the frame.  
4)Create the number of page frames based on the number of pages passed by calling the insert method from linked list.
5)Unlock the block.#

	Function :shutdownBufferPool
	----------------------------
	
1)Obtain a lock on the code block for making the #function(application) thread safe.
2)If the fix count of a page is greater than zero,set that the page has been pinned.
3)Check if pages are dirty.If true,write the pages back to the disc.
4)Delete the page frame.
5)Free the memory that has been allocated to the buffer pool.
6)Unlock the block.# 
	
	Function : forceFlushPool
	-------------------------

1)Obtain a lock on the code block for making the #function(application) thread safe.
2)Check if any page is dirty.If true,write the page back to the disk.
3)Throw an error message if the writing to the disk was not successfull.
4)Unlock the block.# 

	Function : markDirty
	---------------------
	
1)Traverse the contents of the page frame from the 1st node till last.
2)If the page is dirty,set the flag to true .RC_OK else,mark dirty failed error.
3)Return the appropriate message to the calling function.#



	Function : unpinPage
	---------------------
	

1)Check if the requested page is in the buffer.
2)Check for the fixcount of the page.If zero, check whether page was dirtied.
3)If the dirty flag is set,write the page to disk and unpin it.
4)On failure,throw an appropriate message.


	Function : forcePage
	--------------------
	
1)Check for page frame existence.
2)Write the current content of the page back to the page file on disk .
3)Return the appropriate message to the calling function.


	Function : pinPage 
	------------------

1)Obtain a lock on the code block for making the #function(application) thread safe.
2)Check if the page is already available in the buffer.If true,there is no need to pin the page again
3)Check if the buffer pool is free.If true,#pin the page.
4)If the buffer pool is not free, check for the replacement algorithm passed .
5)The page is replaced with the new page by calling the user defined function doalgorithm.



**Statistics Functions**
-------------------------

	Function : getFrameContents
	----------------------------
	
1)Check for the frame existence.
2)Traverse till the end of page frame and read the page numbers to the array.
3)Return the array pointer.
 
	Function : getDirtyFlags
	------------------------
	
	
1)Check for the frame existence.
2)Traverse till the end of page frame and check if the page is dirty.
3)If true,set that the page is dirty.
3)Read the values to the array.
4)Return the array pointer.


	Function : getFixCounts
	------------------------
	
1)Check for the frame existence.
2)Traverse till the end of page frame and check the fix count of the pages in the page frame.
3)Read the values to the array.
4)Return the array pointer.


	Function : getNumReadIO
	------------------------

1) Search for the buffer node that was requested for.
2) On Success,return the total number of reads that have taken place. 


	Function: getNumWriteIO
	-----------------------
	
1) Search for the buffer node that was requested for.
2) On Success,return the total number of writes that have taken place. 

** User defined functions**
---------------------------
We have included the following User defined functions and their functionalities are as described:

	Function: doalgorithm
	----------------------
This function returns if the replacement is a success or not
	
1)Check for fixed count of all frames who has fixed count more than zero.
2)For the pages with a fix count of zero,write them to the array.
3)Check the pages that have to be replaced from the buffer node and use the replacement strategy
	a)If the replacement strategy is FIFO,look at the counter and replace with immediate counter.
	b)If the replacement strategy is LRU,look at the time it was inserted.
3)Check the page for dirty flag.If set,then the page has to be written to the disk.
4)Update the replacement parameters.
5)Check for read and write tags and return true if success.


	Function : what_pools_active
	----------------------------
This function is used to check the pools that are active.
	

	Function : initpf
	-----------------
This function is used to initialize the page frame.
1)Traverse till the size of the page.
2)Fill the contents of the page with null bytes.

4) Additional Test Cases and Additional Error Checks
----------------------------------------------------

We have included additional test cases for executing the following functions.

-
-
-
-
-
-
-
-


4) Implementation
-----------------

Before the actual coding of the project was done,we figured out the cause and effect of the problem,which made the implementation more systematic.

We then split the project into 3 modules and worked on the modules.
 
The modules being:
 
a)Operations pertaining to Buffer pool functions.

b)Operations pertaining to Page management and Statistics functions.

c)Functions pertaining to Linked list operations.

then,the code was integrated using GitHub.

The implementation versions with the descriptions are as follows.

Version 	   Date 	   Description				
----------    --------   ------------
version 1.0  9/25/2014   Initial code had logical and syntax 					   errors

version 1.1  9/26/2014   Errors had been rectified and makefile 					   was created

version 1.2  9/27/2014   Changes in ensure capacity were   				              incorporated     

version 1.3  10/02/2014  All test cases were sucessfully 					  	   implemented and additional test cases 					   were added

version 1.4  10/03/2014  makefile was updated and comments were 
(FINAL)			   added to improve readability of the 					   code.
 



----------------------------------------------------------------------------------------------------------------------------------
 


