//blocks.h

#ifndef _BARSLIST_H
#define _BARSLIST_H

typedef struct ONE_BLOCK OneBlock; // = block_node

struct ONE_BLOCK
{
    OneBlock * next;
    void * start; //block_start
    r_size_t size;
};

void * createBlocks();
//=destroy_block_list
Boolean destroyBlocks( void * top ); //=list_top
//=firstblock
OneBlock * getFirstBlock( void * top ); //==list_top
//=get_next_block
OneBlock * getNextBlock( void * key );
//=get_prev_block
OneBlock getPrevBlock( void * key );
