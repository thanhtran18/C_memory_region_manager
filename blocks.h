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
//first_fit                   / data_size / block_size / data_start
void * firstFitStrategy( r_size_t dSize, r_size_t bSize, void * first )
//add_block                 / data_size / block_size / data_start / list_top
OneBlock createBlock( r_size_t dSize, r_size_t bSize, void * first, void * parent )
//=deleteBlock      //list-top / target
Boolean deleteBlock( void * top, OneNode * key )
//=find_block            list_top / block_start
OneBlock * blockSearch( void * top, void * blockFirst )
