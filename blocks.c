//-----------------------------------------------------------------------------------
// AUTHOR:           CONG THANH TRAN
//
// REMARKS: This module is the data structure used for managing a list of blocks in each region.
//-----------------------------------------------------------------------------------

//blocks.c

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "regions.h"
#include "blocks.h"

//-------------------------------------------------------------------------------------
// CONSTANTS and TYPES
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
// VARIABLES
//-------------------------------------------------------------------------------------
static OneBlock * head = NULL;      //the head node of the list of blocks
static OneBlock * traverse = NULL;  //the current node that is being processed

//-------------------------------------------------------------------------------------
// PROTOTYPES
//-------------------------------------------------------------------------------------



//-------------------------------------------------------------------------------------
// FUNCTIONS
//-------------------------------------------------------------------------------------


//invariant
static void validateBlocks()
{
    if ( head != NULL )
    {
        assert( head->size % 8 == 0 );
    }
} //validateBlocks

void * createBlocks()
{
    validateBlocks();

    OneBlock * parent = ( OneBlock * ) malloc( sizeof( OneBlock ) );
    //set everything to NULL and 0
    parent->start = NULL;
    parent->next = NULL;
    parent->size = 0;
    
    validateBlocks();
    return parent;
} //createBlocks

//-----------------------------------------------------------------------------------
// getFirstBlock
//
// PURPOSE: this function will return the first block in the region
//
// PARAMETER:
//     top - a pointer to blocks in a region
//
// RETURN
//     this function will return the first block in that region, NULL on error
//-----------------------------------------------------------------------------------
OneBlock * getFirstBlock( void * top )
{
    validateBlocks();
    assert( top != NULL );

    OneBlock * curr = NULL; //the current node that is being processed
    
    head = top;
    if ( top != NULL )
    {
        curr = head->next;
    }
    validateBlocks();
    return curr;
} //getFirstBlock

//-----------------------------------------------------------------------------------
// getNextBlock
//
// PURPOSE: this function will return the next block of the given one in the region
//
// PARAMETER:
//     key - we need to find the next block of this one
//
// RETURN
//     this function will return the next block in that region, NULL on error
//-----------------------------------------------------------------------------------
OneBlock * getNextBlock( void * key )
{
    validateBlocks();
    assert( key != NULL );

    if ( key != NULL )
    {
        traverse = head;
        while ( traverse != NULL && traverse->start < key )
        {
            traverse = traverse->next;
        }
    }

    validateBlocks();
    return traverse;
} //getNextBlock

//-----------------------------------------------------------------------------------
// getPrevBlock
//
// PURPOSE: this function will return the previous block of the given one in the region
//
// PARAMETER:
//     key - we need to find the previous block of this one
//
// RETURN
//     this function will return the previous block in that region, NULL on error
//-----------------------------------------------------------------------------------
OneBlock * getPrevBlock( void * key )
{
    validateBlocks();
    assert( key != NULL );

    OneBlock * result = NULL ; //returned value, as description above
    if ( key != NULL )
    {
        traverse = head;
        while ( traverse != NULL && traverse->start < key )
        {
            result = traverse;
            traverse = traverse->next;
        }
        assert( result->start < key );
    }

    validateBlocks();
    return result;
} //getPrevBlock

//-----------------------------------------------------------------------------------
// destroyBlocks
//
// PURPOSE: this function will destroy all blocks in a region
//
// PARAMETER:
//     top - the head node of the block list
//
// RETURN
//     this function will return true if the blocks are successfully destroyed, false otherwise
//-----------------------------------------------------------------------------------
Boolean destroyBlocks( void * top )
{
    validateBlocks();
    assert( top != NULL );

    head = top;
    Boolean destroyed = false; //returned value, as description above
    OneBlock * prev;           //a pointer points to the previous block

    if ( head != NULL )
    {
        if ( head->next != NULL )
        {
            destroyed = true;
        }
        
        if ( !destroyed )
        {
            free( head );
            head = NULL;
            if ( head == NULL )
            {
                destroyed = true;
            }
            assert( destroyed );
        }
        else
        {
            prev = head->next;
            traverse = prev->next;
            prev->next = NULL;
            if ( prev->next == NULL )
            {
                destroyed = true;
            }
            assert( destroyed );

            //destroy block by block
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
                assert( destroyed );
                free( head );
                head = NULL;
                if ( head == NULL )
                {
                    destroyed = true;
                }
                assert( destroyed );
            }
        } //else
    } //big if

    validateBlocks();
    return destroyed;
} //destroyBlocks

//-----------------------------------------------------------------------------------
// firstFitStrategy
//
// PURPOSE: this function will find the first fit block of in a region for a given block
//
// PARAMETER:
//     rSize - the size of the region
//     bSize - the size of the block
//     first - the pointer to the start
//
// RETURN
//     this function will return a pointer to the first fit block in the region, NULL
//     if can't find of any
//-----------------------------------------------------------------------------------
void * firstFitStrategy( r_size_t rSize, r_size_t bSize, void * first )
{
    validateBlocks();
    assert( rSize > 0 );
	assert( bSize > 0 );
    assert( bSize % 8 == 0 );
    assert( first != NULL );
    
    void * firstFitBlock = NULL; //returned value, as description above
    traverse = head->next;
    OneBlock * prev = head;
    unsigned int prevSize;

    if ( rSize > 0 && bSize % 8 == 0 && first != NULL && bSize > 0 )
    {
        prevSize = ( unsigned int ) first;

        //traverse through the region to find out the first fit block
        while ( traverse != NULL && ( bSize > ( ( unsigned int ) traverse->start - prevSize ) ) )
        {
            prev = traverse;
            traverse = traverse->next;
            prevSize = ( unsigned int ) prev->start + ( unsigned int ) prev->size;
        }
        
        if ( prev->size == 0 )
        {
            firstFitBlock = first;
        }
		else if ( bSize <= rSize - ( prevSize - ( unsigned int ) first ) )
        {
            firstFitBlock = prev->start + prev->size;
        }
    } //if
    
    validateBlocks();
    return firstFitBlock;
} //firstFitStrategy

//-----------------------------------------------------------------------------------
// createBlock
//
// PURPOSE: this function will add a new block with given information to a suitable position
//          in the region
//
// PARAMETER:
//     rSize  - the size of the region
//     bSize  - the size of the block
//     first  - the pointer to the start
//     parent - the pointer to the parent (head) of the list of blocks
//
// RETURN
//     this function will return a pointer to the new block if successfully created, NULL otherwise
//-----------------------------------------------------------------------------------
OneBlock * createBlock( r_size_t rSize, r_size_t bSize, void * first, void * parent )
{
    validateBlocks();
    assert( rSize > 0 );
    assert( bSize % 8 == 0 );
    assert( parent != NULL && first != NULL );

    OneBlock * prev;    //a pointer to the previous block
    OneBlock * curr = ( OneBlock * )malloc( sizeof( OneBlock ) ); //the current block that is being processed
    assert( curr != NULL );

    head = parent;

    if ( rSize > 0 && bSize % 8 == 0 && parent != NULL && first != NULL && curr != NULL )
    {
        curr->size = bSize;
        if ( head->next != NULL)
        {
            //find out where to add the new block using first fit strategy
            curr->start = firstFitStrategy( rSize, bSize, first );
            if ( curr->start == NULL )
            {
                free( curr );
                curr = NULL;
                assert( curr == NULL );
            }
            else
            {
                //insert the block to the correct position in the list
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
    
    validateBlocks();
    return curr;
} //createBlock

//-----------------------------------------------------------------------------------
// deleteBlock
//
// PURPOSE: this function will delete a block with given information in the region
//          in the region
//
// PARAMETER:
//     top - the head node of the block list
//     key - the block that needs to be deleted
//
// RETURN
//     this function will return true if the given block is successfully deleted, false otherwise
//-----------------------------------------------------------------------------------
Boolean deleteBlock( void * top, OneBlock * key )
{
    validateBlocks();

    Boolean passed = false;     //returned value, as description above
    OneBlock * prev;    //a ponter to the previous block

    if ( key != NULL && top != NULL )
    {
        passed = true;
        head = top;
        //delete the given block from the list of blocks
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
    
    validateBlocks();
    return passed;
} //deleteBlock

//-----------------------------------------------------------------------------------
// blockSearch
//
// PURPOSE: this function will search for a block with given information in a region
//
// PARAMETER:
//     top        - the head node of the block list
//     blockFirst - the pointer to the block.
//
// RETURN
//     this function will return the block itself if found, NULL otherwise
//-----------------------------------------------------------------------------------
OneBlock * blockSearch( void * top, void * blockFirst )
{
    validateBlocks();
    assert( top != NULL );
    assert( blockFirst != NULL );

    if ( top != NULL && blockFirst != NULL )
    {
        traverse = top;
        //traverse through the region
        while ( traverse != NULL && blockFirst != traverse->start )
        {
            traverse = traverse->next;
        }
    }
    
    validateBlocks();
    return traverse;
} //blockSearch
