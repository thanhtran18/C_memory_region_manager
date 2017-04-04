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
