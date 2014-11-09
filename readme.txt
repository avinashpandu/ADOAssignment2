		**Assignment 2: Buffer Manager**
****************************************************

					**Team:knariset,asachith,plal1**
					********************************

CONTENTS
*********
1)Instructions to run the code
2)Additional functionalities
3)Description of functions used
4)Additional Test Cases and Additional error checks
5)Implementation

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
1)We have implemented Least Recently Used as an additional replacement strategy.

2)We have made the buffer pool functions thread safe.

3)We have included additional test cases and additional error checks.

3)Description of functions used
********************************

	Function :initBufferPool
	-------------------------


1)Open page file and initialize fHandle.If opening fails,throw an appropriate error code.
#2)Initialize the linked list to be of size numPages and insert the Page Frame.
3)Initialize other Values in bp_manager  by calling the user defined function init_other_vals.
4)The mgmtData is used for book keeping,which contains the information of pages read and pages wrote.


	Function :shutdownBufferPool
	----------------------------
	

1)If the fix count of a page is greater than zero,return an appropriate error code.
2)Check if pages are dirty.If true,write the pages back to the disc by calling forceFlushPool function.
3)Free the memory that has been allocated to the buffer pool.

	
	Function : forceFlushPool
	-------------------------


1)Check if the buffer pool has been initialized.If not,throw an appropriate error code.
#2)Traverse till the end of the page frame.
3)If the dirty_Flag is set true and the fix_Count is equal to zero,then call the  writeBlock function to write the contents to the disk.
#4)On success,return RC_OK to the calling function. 

	Function : markDirty
	---------------------
1)Check if the buffer pool has been initialized.If not,throw an appropriate error code.	
2)Traverse the contents of the page frame from the 1st node till last.
3)If the page is dirty,set the flag to true.
4)On success,return RC_OK to the calling function..



	Function : unpinPage
	---------------------
	
1)Check if the buffer pool has been initialized.If not,throw an appropriate error code.	
2)Traverse the contents of the page frame from the 1st node till last.
###3)Reduce the fix count if the page is already in the buffer.(is this statement true ????)###
###4)If the dirty flag is set,write the page to disk.
5)If the fix count of the frame array is less than zero ,return an appropriate error code.



	Function : forcePage
	--------------------
1)Check if the buffer pool has been initialized.If not,throw an appropriate error code.	
2)Write the current content of the page back to the page file on disk .
3)Increase the count of pages_wrote.
4)On success,return RC_OK to the calling function.


	Function : pinPage 
	------------------
1)Check if the page is already present in the buffer pool.If yes,	
	a)Traverse the contents of the page frame from the 1st node till last.
	b)Increase the fix count of the page ( ##########)
	c)Check if the replacement strategy is either FIFO or LRU .If not,throw an appropriate error code.

2)If the page is not present in the buffer pool,
	a)Check for minimum possible frame and get the page from file .
	b)##Assign the values of the page frame. 
######
######
######
3)On success,return RC_OK to the calling function.


**Statistics Functions**
-------------------------

	Function : getFrameContents
	----------------------------
	
#1)Check if the buffer pool has been initialized.If not,throw an appropriate error code.
2)Traverse till the end of page frame and read the page numbers to the array.
3)Return the array pointer.
 
	Function : getDirtyFlags
	------------------------
	
	
#1)Check if the buffer pool has been initialized.If not,throw an appropriate error code.
2)Traverse till the end of page frame and check if the page is dirty.
3)If true,set that the page is dirty.
4)Read the values to the array.
5)Return the array pointer.


	Function : getFixCounts
	------------------------
	
#1)Check if the buffer pool has been initialized.If not,throw an appropriate error code.
2)Traverse till the end of page frame and check the fix count of the pages in the page frame.
3)Read the values to the array.
4)Return the array pointer.


	Function : getNumReadIO
	------------------------

#1)Check the mgmtData of the buffer manager,which contains the information of the pages read.
#2)Return the pages read. 


	Function: getNumWriteIO
	-----------------------
	
#1)Check the mgmtData of the buffer manager,which contains the information of the pages written.
#2) Return the pages written. 

** User defined functions**
---------------------------

	Function : init_other_vals
	--------------------------
This function is used to initialize the values of the ##buffer pool manager.

##The memory for the dirty_flag_array and fix_Count_array are initialized with the help of this user defined function.
 

	Function : free_all
	-----------------
1)This User Defined function is called by shutdownBufferPool function.

2)Traverse the contents of the page frame from the 1st node till last.

2)Free the memory allocated to the parameters of the buffer pool manager



4) Additional Test Cases and Additional Error Checks
----------------------------------------------------

We have included additional test cases for executing the following functions.

->
->
->
->
->
->
->
->

We have included the following additional error checks

RC_REQUSTED_PAGE_PAGE_NOT_FOUND 206 ->Return if the requested page is not found.

RC_INVALID_STRATEGY 207 ->Return if an invalid replacement strategy is used. 


5) Implementation
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
version 1.0  10/11/2014  All functions were commented
 
version 1.1  10/12/2014  Linked list functions were complete

version 1.2  10/25/2014  LRU and FIFO functions were added to 					    perform the replacement

version 1.3  10/29/2014  Make file was created and code had 					   logical and syntax errors

version 1.4  10/30/2014  Syntax errors were rectified.
 



----------------------------------------------------------------------------------------------------------------------------------
 


