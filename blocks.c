//blocks.c = block_list.c

#include <stdio.c>
#include <stdlib.c>
#include <assert.h>
#include <string.h>
#include "regions.h"
#include "regionsList.h"

static OneBlock * head = NULL; //=top
static OneBlock * traverse = NULL; //=traverse_block

//=new_block_list
void * createBlocks()
{
    OneBlock * parent = ( OneBlock * ) malloc( sizeof( OneBlock ) );
    parent->start = NULL;
    parent->next = NULL;
    parent->size = 0;
    return parent;
} //createBlocks

//=first_block
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

//first_fit                   / data_size / block_size / data_start
void * firstFitStrategy( r_size_t dSize, r_size_t bSize, void * first )
{
    assert( dSize > 0 );
    assert( bSize % 8 == 0 );
    assert( first != NULL );
    void * firstFitBlock = NULL; //=block_start
    traverse = head->next;
    OneBlock prev = head; //=prev_block
    unsigned int prevSize; //=prev_size
    if ( dSize > 0 && bSize % 8 == 0 && first != NULL && bSize > 0 )
    {
        //if (success)
        prevSize = ( unsigned int ) first;
        while ( traverse != NULL && bSize > ( unsigned int ) traverse->start - prevSize )
        {
            prev = traverse;
            traverse = traverse->next;
            prevSize = ( unsigned int ) prev->start + ( unsigned int ) prev->size;
        }
        if ( bSize <= dSize - ( prevSize - ( unsigned int ) first ) )
        {
            firstFitBlock = prev->start + prev->size;
        }
        else if ( prev->size == 0 )
        {
            firstFitBlock = first;
        }

    } //if
    return firstFitBlock;
} //firstFitStrategy

//add_block                 / data_size / block_size / data_start / list_top
OneBlock createBlock( r_size_t dSize, r_size_t bSize, void * first, void * parent )
{
    assert( dSize > 0 );
    assert( bSize % 8 == 0 );
    assert( parent != NULL && first != NULL );
    OneBlock prev; //prev_block
    OneBlock curr = ( OneBlock * )malloc( sizeof( OneBlock ) ); //new_block
    assert( curr != NULL );
    head = parent;

    if ( dSize > 0 && bSize % 8 == 0 && parent != NULL && first != NULL )
    {
        //if (success)
        curr->size = bSize;
        if ( top->next != NULL)
        {
            curr->start = firstFitStrategy( dSize, bSize, first );
            if ( curr->start == NULL )
            {
                free( curr );
                curr = NULL;
                assert( curr == NULL );
            }
            else
            {
                curr->next = getNextBlock( curr->start );
                prev = getPrevBlock( curr->start );
                prev->next = curr;
            }
        }
        else
        {
            curr->start = first;
            curr->next = head->next;
            head->next = curr;
        } //else
    } //big if
} //createBlock

//=deleteBlock      //list-top / target
Boolean deleteBlock( void * top, OneNode * key )
{
    Boolean passed;
    OneBlock prev;
    if ( key != NULL && top != NULL )
    {
        head = top;
        prev = getPrevBlock( key->start );
        prev->next = key->next;
        free( key );
        key = NULL;
        if ( key == NULL )
        {
            passed = true;
        }
        assert( passed );
    }
    return passed;
} //deleteBlock

//=find_block            list_top / block_start
OneBlock * blockSearch( void * top, void * blockFirst )
{
    assert( top != NULL );
    assert( blockFirst != NULL );
    if ( top != NULL && blockFirst != NULL )
    {
        traverse = top;
        while ( traverse != NULL && blockFirst != traverse->start )
        {
            traverse = traverse->next;
        }
    }
    return traverse;
} //blockSearch
