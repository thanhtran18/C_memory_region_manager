//-----------------------------------------------------------------------------------
// NAME:           CONG THANH TRAN
// STUDENT NUMBER: 7802106
// COURSE:         COMP2160, SECTION: A01
// INSTRUCTOR:     FRANKLIN BRISTOW
// ASSIGNMENT:     assignment 4 - MEMORY REGIONS
// 
// REMARKS: This module is the header file of blocks.c. This will be included in
//          other files for further using.
//-----------------------------------------------------------------------------------

//blocks.h

#ifndef _BLOCKS_H
#define _BLOCKS_H

typedef struct ONE_BLOCK OneBlock;

//-----------------------------------------------------------------------------------
// OneBlock - struct
//
// PURPOSE: each OneBlock has a size, a pointer to its starting position, and a pointer
//          to the next OneBlock.
//-----------------------------------------------------------------------------------
struct ONE_BLOCK
{
    r_size_t size;    //size of the block
    void * start;     //starting position
    OneBlock * next;  //pointer to the next OneBlock
};

void * createBlocks();

//this function will destroy all blocks in a region
Boolean destroyBlocks( void * top );

//this function will return the first block in the region
OneBlock * getFirstBlock( void * top );

//this function will return the next block of the given one in the region
OneBlock * getNextBlock( void * key );

//this function will return the previous block of the given one in the region
OneBlock * getPrevBlock( void * key );

//this function will find the first fit block of in a region for a given block
void * firstFitStrategy( r_size_t dSize, r_size_t bSize, void * first );

//this function will add a new block with given information to a suitable position in the region
OneBlock * createBlock( r_size_t dSize, r_size_t bSize, void * first, void * parent );

//this function will delete a block with given information in the region in the region
Boolean deleteBlock( void * top, OneBlock * key );

//this function will search for a block with given information in a region
OneBlock * blockSearch( void * top, void * blockFirst );

#endif
