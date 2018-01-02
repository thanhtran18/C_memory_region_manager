
*** MEMORY REGIONS ***

CONTENTS
--------

I. PURPOSE OF THE PROGRAM

II. DATA MODEL

III. HOW TO RUN THE PROGRAM?

IV. GIT TAGS


I. PURPOSE OF THE PROGRAM
-------------------------
This program is the implementation of a named memory regions manager, where each region is given a name (a string) and referred to by that name. Each region has a fixed maximum size that is specified when it is created. Within each region, blocks of memory can be allocated and freed, totalling up to its maximum size.

II. DATA MODEL
--------------
Each ***RegionNode*** has several elements:
1. name
2. data
3. blocks
4. size
5. used bytes
6. next
Each ***OneBlock*** has several elements:
1. size
2. block start
3. next
***regionsList.c*** manages the indexes of all regions (which is region names in this case). It includes some necessary operations for the data structure, including: insertion, deletion, searching, returning the first region and the next region.
***blocks.c*** manages all blocks in each region. It includes some necessary operations for the data structure, including: adding a new block, creating a list of blocks, destroying a block, destroying all blocks, searching for a block, returning the first, the next or the previous block, and the first fit strategy function.

III. HOW TO RUN THE PROGRAM?
----------------------------
1. How to compile this program with my test unit? Run this command:

make

2. How to run this program with my test unit? Run this command:

./regionsRun

3. How to compile this program with the given test files? Run this command (replace the $ sign by the test number you want to test):

make test$Run

!!!For example, If you want to compile test0.c, run: "make test0Run". if you want to compile test1.c, run: "make test1Run", and so on so forth.

4. How to run this program with the given test files given? Run this command (replace the $ sign by the test number you want to test similar to the example above):

./test$Run

***Note*** This unit test contains some invalid testing cases, which will trip off the assertions (they are supposed to do so). If you want to check the usage of assertions, simply remove -DNDEBUG flag from CFLAGS (if it's there) in the Makefile, run the command: "make clean", then recompile with those 2 commands above, you will get assertion failed at the end of the test.
On the other hand, in order to make the unit test work for all cases, add the -DNDEBUG flag to CFLAGS (if it's not there already) in the Makefile, run the command: "make clean" again before recompiling.

IV. GIT TAGS
------------
There are 3 git tags in this assignment:
1. Finish-implementing-regions.c-and-two-other-helper-.c-files: Indicates that regions.c has been implemented successfully.
2. Finished-implementing-the-whole-memory-regions-based-thing-It-worked: Indicates that the program is now working as expected with all the test files. This is the first version.
3. the-assignment-is-done: This is the last version of the assignment. No more features and correction will be added.
