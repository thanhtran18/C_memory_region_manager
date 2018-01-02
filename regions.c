//-----------------------------------------------------------------------------------
// AUTHOR:           CONG THANH TRAN
// 
// REMARKS: This program contains all function implementation for all the function signatures
//          in the given regions.h header file
//-----------------------------------------------------------------------------------

//regions.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "regions.h"
#include "blocks.h"
#include "regionsList.h"

//-------------------------------------------------------------------------------------
// CONSTANTS and TYPES
//-------------------------------------------------------------------------------------
#define MAX_SIZE 65528 //the maximum size that a region can have with unsigned short type size

//-------------------------------------------------------------------------------------
// VARIABLES
//-------------------------------------------------------------------------------------
static RegionNode * currRegion = NULL;

//-------------------------------------------------------------------------------------
// PROTOTYPES
//-------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------
// FUNCTIONS
//-------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------
// roundUp
//
// PURPOSE: this function will round the given size up to a nearest multiple of 8 if,
//          do nothing if it's already a multiple of 8
//
// PARAMETER:
//     size - the size that needs to be rounded
//
// RETURN:
//     this function returns a nearest (larger) multiple of 8 of the given size.
//-----------------------------------------------------------------------------------
r_size_t roundUp( r_size_t size )
{
    assert( size > 0 );
    r_size_t rounded = size; //returned value, as description above
    if ( size > 0 && size <= MAX_SIZE )
    {
        if ( size % 8 != 0 )
        {
            int divide = size / 8;
            size = 8 * ( divide + 1 );
            rounded = size;
        }
        //do nothing if the given size is already a multiple of 8
        else
        {
            rounded = size;
        }
    } //big if
    else if ( size > MAX_SIZE )
    {
        rounded = MAX_SIZE;
    }
    
    //make sure the returned value is now a multiple of 8.
    assert( rounded % 8 == 0 );
    return rounded;
} //roundUp

//-----------------------------------------------------------------------------------
// rinit
//
// PURPOSE: this function will create and initialize a region with the given name and the 
//          given size. The name must be unique, and the size must be greater than 0. Return 
//          false on error. If the call succeeds, choose the newly-created region (rchoose() below)
//
// PARAMETERS:
//     region_name - the given name will be assigned to the new region
//     region_size - the given size will be created for the new region
//
// RETURN
//     this function will return true if a new region is successfully initialized, false otherwise
//-----------------------------------------------------------------------------------
Boolean rinit( const char *region_name, r_size_t region_size )
{
    assert( region_size > 0 );
    assert( region_name != NULL);
    assert( !found( region_name ) );
    Boolean passed = false;  //returned value, as description above
    r_size_t rounded;        //rounded value of the given size to the nearest higher multiple of 8

    //make sure that region_name is unique with !found() condition
    if ( region_size > 0 && region_name != NULL && !found( region_name ) )
    {
        currRegion = insertRegion();
        assert( currRegion != NULL );

        if ( currRegion != NULL )
        {
            currRegion->name = ( char * ) malloc( strlen( region_name ) + 1 );
            assert( currRegion->name != NULL );
            //make sure that the size will be a multiple of 8
            rounded = roundUp( region_size );

            //Initially, the region will have a size which is a multiple of 8, no used byte
            currRegion->size = rounded;
            currRegion->usedBytes = 0;
            currRegion->data = malloc( rounded );
            assert( currRegion->data != NULL );
            
            currRegion->block = createBlocks();
            if ( currRegion->data != NULL && currRegion->name != NULL && currRegion->block != NULL )
            {
                //assign the given name to the name of the new region
                strcpy( currRegion->name, region_name );
                assert( strcmp( currRegion->name, region_name ) == 0 );
                passed = true;
            }
            else
            {
                if ( currRegion->block != NULL )
                {
                    destroyBlocks( currRegion->block );
                    assert( currRegion->block == NULL );
                }
                free( currRegion->data );
                free( currRegion->name );
                free( currRegion );
                currRegion = NULL;
                assert( currRegion == NULL );
            } //else
        } // if currRegion != NULL 
    } //big if with 3 conditions
    return passed;
} //rinit

//-----------------------------------------------------------------------------------
// rchoose
//
// PURPOSE: this function will choose a previously-initialized memory region for subsequent 
//               ralloc , rsize , and rfree calls. Return false on error.
//
// PARAMETERS:
//     region_name - the given name of the region that needs to be chosen
//
// RETURN
//     this function will return true if the new region is successfully chosen, false otherwise
//-----------------------------------------------------------------------------------
Boolean rchoose( const char * region_name )
{
    assert( region_name != NULL );
    Boolean passed = false;     //returned value, as description above
    RegionNode * curr;  //the current node that is being processed
    if ( region_name != NULL )
    {
        //call search() function to search for the region which has that name in the region list
        curr = search( region_name );
        if ( curr != NULL )
        {
            currRegion = curr;
            passed = true;
        }
    }
    return passed;
} //rchoose

//-----------------------------------------------------------------------------------
// rchosen
//
// PURPOSE: this function will return the name of the currently-chosen region, or NULL 
//          if no region is currently chosen.
//
// RETURN
//     Return the name of the currently-chosen region, or NULL if no region is currently chosen.
//-----------------------------------------------------------------------------------
const char * rchosen()
{
    const char * currName = NULL; //returned value, as description above
    if ( currRegion != NULL )
    {
        //make sure the name of the region is not NULL
        assert( currRegion->name != NULL );
        if ( currRegion->name != NULL )
        {
            currName = currRegion->name;
            assert( strcmp( currRegion->name, currName ) == 0 );
        }
    }
    return currName;
} //rchosen

//-----------------------------------------------------------------------------------
// ralloc
//
// PURPOSE: this function will allocate a block that is the given number of bytes large 
//          from the currently-chosen region. Clear its contents to zero. Return a pointer 
//          to the block. Size 0 blocks are not allowed.
//
// PARAMETERS:
//     block_size - the given size of the block that needs to be allocated
//
// RETURN
//     this function will return a pointer to the block, or NULL on error
//-----------------------------------------------------------------------------------
void * ralloc( r_size_t block_size )
{
    assert( block_size > 0 );
    assert( currRegion != NULL );
    assert( currRegion->block != NULL );

    //make sure the size is a multiple of 8
    r_size_t rounded = roundUp( block_size );
    OneBlock * newBlock = NULL; //the new block will be allocated
    void * dataStart = NULL;           //the pointer to that block will be returned
    unsigned char * blockPtr;

    if ( block_size > 0 && currRegion != NULL && currRegion->block != NULL && ( currRegion->size - currRegion->usedBytes ) >= rounded )
    {
        //create a new block with given information
        newBlock = createBlock( currRegion->size, rounded, currRegion->data, currRegion->block );
        if ( newBlock != NULL )
        {
            //increase the number of used bytes in that region after allocating a new block in it.
            currRegion->usedBytes += rounded;

            //clear the contents of this block to zero
            for ( blockPtr = newBlock->start; ( void * ) blockPtr < newBlock->start + newBlock->size; blockPtr++ )
            {
                *blockPtr = 0;
                assert( *blockPtr == 0 );
            }
            dataStart = newBlock->start;
        }
    }
    return dataStart;
} //ralloc

//-----------------------------------------------------------------------------------
// rsize
//
// PURPOSE: this function will find out how many bytes the block of memory pointed to by 
//          the pointer is, in the currently-chosen region. Return that size.
//
// PARAMETERS:
//     block_ptr - the pointer points to the block that we need to know its size
//
// RETURN
//     this function will return the size of that block, 0 on errors.
//-----------------------------------------------------------------------------------
r_size_t rsize( void * block_ptr )
{
    assert( currRegion != NULL );
    
    OneBlock * curr;     //the current block that is being processed in the region
    r_size_t result = 0; //returned value, as description above

    if ( currRegion != NULL && block_ptr != NULL )
    {
        //search for the block
        curr = blockSearch( currRegion->block, block_ptr );
        if ( curr != NULL )
        {
            assert( curr->size > 0 );
            if ( curr->size > 0 )
            {
                //if found then return its size
                result = curr->size;
            }
        }
    } //big if
    return result;
} //rsize

//-----------------------------------------------------------------------------------
// rfree
//
// PURPOSE: this function will free the block identified by the given pointer in the 
//          currently-chosen region. Return if it is successfully freed
//
// PARAMETERS:
//     block_ptr - the pointer points to the block that we need to free
//
// RETURN
//     this function will return true if the block is successfully freed, false otherwise
//-----------------------------------------------------------------------------------
Boolean rfree( void * block_ptr )
{
    assert( block_ptr != NULL );
    assert( currRegion != NULL );

    RegionNode * curr;      //the current region that is being processed
    OneBlock * key = NULL;  //the block that needs to be freed
    int size;               //the size of that block
    Boolean freed = false;  //returned value, as description above

    if ( block_ptr != NULL && currRegion != NULL )
    {
        //start searching from the first region in the list
        curr = returnFirst();
        
        while ( key == NULL && curr != NULL )
        {
            //search for that block in that region, move on to next region if haven't found yet
            key = blockSearch( curr->block, block_ptr );
            curr = returnNext();
        }
        if ( key != NULL )
        {
            size = key->size;
        }
        if ( deleteBlock( currRegion->block, key ) )
        {
            //decrease the number of used bytes after freeing any block
            currRegion->usedBytes -= size;
            freed = true;
        }
    } //big if
    return freed;
} //rfree

//-----------------------------------------------------------------------------------
// rdestroy
//
// PURPOSE: this function will destroy the region with the given name, freeing all memory 
//          associated with it. After calling this function, any library functions that 
//          attempt to access this region should return an error. If the region was chosen, 
//          it will no longer be. After a region is destroyed, its name may be reused later 
//          when calling rinit .
//
// PARAMETERS:
//     region_name - the name of the region that needs to be destroyed
//-----------------------------------------------------------------------------------
void rdestroy( const char * region_name )
{
    assert( region_name != NULL );
    RegionNode * curr; //the current region that is being processed

    if ( region_name != NULL )
    {
        //search for the region with the given name, destroy all blocks in it
        curr = search( region_name );
        if ( curr != NULL )
        {
            if ( strcmp( curr->name, region_name ) == 0 )
            {
                if ( destroyBlocks( curr->block ) )
                {
                    if ( delete( region_name ) )
                    {
                        if ( curr == currRegion )
                        {
                            currRegion = NULL;
                            assert( currRegion == NULL );
                        }
                        curr = NULL;
                        assert( curr == NULL );
                    }
                }
            } //big if passsed
        } //if curr != null
    } //if region_name!=NULL
} //rdestroy

//-----------------------------------------------------------------------------------
// rdump
//
// PURPOSE: this function will print all data structures, but not block contents. Show 
//          the name of each region; underneath each, show the blocks allocated in them 
//          and their block sizes
//-----------------------------------------------------------------------------------
void rdump()
{
    OneBlock * block;                       //the current block that is being processed
    RegionNode * region = returnFirst();    //the current region that is being processed
    double freeSpace;                       //the percentage of free space in the region
    int i = 0;                              //position of the current block in the region
    while ( region != NULL )
    {
        freeSpace = ( 1 - ( ( double ) region->usedBytes / ( double ) region->size ) ) * 100;
        block = getFirstBlock( region->block );
        printf( "------------------------------------------------------------------\n" );
        printf( "Name of the current region: \"%s\"\n", region->name );
        printf( "Total size of the current region (bytes): %d\n", region->size );
        printf( "Number of used bytes of the current region (bytes): %d\n", region->usedBytes );
        printf( "There are %.2f%% free space\n\n", freeSpace );

        if ( block != NULL )
        {
            printf( "Blocks allocated in the region:\n");
        }
        while ( block != NULL )
        {
            i++;
            printf( "\tPointer to the block %d: %p\n", i, block->start );
            printf( "\tSize of the block (bytes): %d\n", block->size );
            block = block->next;
        }
        i = 0;
        printf( "\n" );
        region = returnNext();
    } //big while
    if ( region == NULL )
    {
        printf( "No region to display\n" );
    }
} //rdump

