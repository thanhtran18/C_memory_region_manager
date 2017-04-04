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
