//blocks.c = block_list.c

#include <stdio.c>
#include <stdlib.c>
#include <assert.h>
#include <string.h>
#include "regions.h"
#include "regionsList.h"

static OneBlock * head = NULL; //=top
static OneBlock * traverse = NULL; //=traverse_block

void * createBlocks()
{
    OneBlock * parent = ( OneBlock * ) malloc( sizeof( OneBlock ) );
    parent->start = NULL;
    parent->next = NULL;
    parent->size = 0;
    return parent;
} //createBlocks

//=firstblock
OneBlock * getFirstBlock( void * top ) //==list_top
{
    OneBlock * curr = NULL;
    head = top;
    //assert( top != NULL ); //should it be here?
    if ( top != NULL )
    {
        curr = top->next;
    }
    return curr;
} //getFirstBlock

//=get_next_block
OneBlock * getNextBlock( void * key )
{
    assert( key != NULL );
    if ( key != NULL )
    {
        traverse = head;
        while ( traverse != NULL && traverse->start < key )
        {
            traverse = traverse->next;
        }
    }
    return traverse;
} //getNextBlock

//=get_prev_block
OneBlock getPrevBlock( void * key )
{
    assert( target != NULL );
    OneBlock result = NULL ; // =prev
    if ( key != NULL )
    {
        traverse = top;
        while ( traverse != NULL && traverse->start < key )
        {
            result = traverse;
            traverse = traverse->next;
        }
        assert( result->start < key );
    }
    return result;
} //getPrevBlock

//=destroy_block_list
Boolean destroyBlocks( void * top ) //=list_top
{
    assert( top != NULL );
    head = top;
    Boolean destroyed = false; //=success
    OneBlock * prev;

    if ( head != NULL )
    {
        if ( head->next != NULL )
        {
            destroyed = true;
        }
        
        if ( !destroyed )
        {
            free( head );
            head = NULL
            if ( head == NULL )
            {
                destroyed = true;
            }
            assert( destroyed );
        }
        else
        {
            prev = head->next;
            traverese = prev->next;
            prev->next = NULL;
            if ( prev->next == NULL )
            {
                destroyed = true;
            }
            assert( destroyed );

            while ( traverse != NULL )
            {
                prev = traverse;
                traverse = traverse->next;
                prev->next = NULL;
                if ( prev->next == NULL )
                {
                    destroyed = true;
                }
                assert( destroyed );
                free( prev );
                prev = NULL;
                assert( prev == NULL );
            } //while
            if ( prev == NULL && traverse == NULL )
            {
                destroyed = true;
            }
            assert( destroyed );
            if ( destroyed )
            {
                free( head );
                head = NULL;
                if ( head == NULL )
                {
                    destroyed = true;
                }
                assert( destroyed );
            }
        } //else
    }
    return destroyed;
} //destroyBlocks
