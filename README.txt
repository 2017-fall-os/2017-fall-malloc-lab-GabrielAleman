This directory contains:

myAllocator.c: a first-fit allocator
myAllocator.h: its header file

myA.c: is a copy of myAllocator.c with some modification of the lab. Things modified are or added
       resizeRegion();
          -added so that if next region is free and it has enough memory it resizes the region
	  instead of making a new block at the end
       bestFit();
          -finds the best region if any to insert the block and returns the block address
       bestFitAllocRegion()
          -inserts block while calling bestFit();

myAllocatorTest1.c: a test program that uses myA.c and shows a an example of best fit and resize
resize region

malloc.c: a replacement for malloc that uses my allocator
test1.c: a test program that uses this replacement malloc

Makefile: a fairly portable "makefile", targets "all" and "clean"

To compile: 
 $ make 
To clean:
 $ make clean

The cygwin runtime uses malloc() and brk() extensively.  It is
interesting to compare the output of test1 & myAllocatorTest1.  All
those extra allocated regions are being used by cygwin's libraries!
