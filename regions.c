#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "regions.h"

#include "regionsList.h"

//should we have a maximum size of a region can have? Ask Franklin about this
#define R_SIZE_T_MAX 65528 //should it be this number?

static RegionNode * currRegion; //= chosen_region
currRegion = NULL;

r_size_t roundUp( r_size_t size );

Boolean rinit( const char *region_name, r_size_t region_size )
{
    assert( region_size > 0 );
    assert( region_name != NULL);
    assert( !found( region_name ) );
    Boolean passed = false; // = success
    r_size_t rounded; //= rounded_size

    if ( region_size > 0 && region_name != NULL && !found( region_name ) )
    {
        currRegion = insert();
        assert( currRegion != NULL );

        if ( currRegion != NULL )
        {
            currRegion->name = ( char* ) malloc( strlen( region_name ) + 1 );
            assert( currRegion->name != NULL );
            rounded = roundUp( region_size );

            currRegion->size = rounded;
            currRegion->data = malloc( rounded );
            currRegion->usedBytes = 0;
            assert( currRegion->data != NULL );
            

            //=======line 59
            currRegion->block = createBlocks(); //from blocks.h
            if ( currRegion->data != NULL && currRegion->name != NULL && currRegion->block != NULL )
            {
                strcpy( currRegion->name, region_name );
                assert( strcmp( currRegion->name, region_name ) == 0 );
                passed = true;
            }
            else
            {
                if ( currRegion->block != NULL )
                {
                    //line 72
                    destroyBlocks( currRegion->block );
                    assert( currRegioin->block == NULL );
                }
                free( currRegion->data );
                free( currRegion->name );
                free( currRegion );
                currRegion = NULL;
                assert( currRegion == NULL );
            } //else

        } // if currRegion != NULL 
    } //big if with 3 conditions

} //rinit

Boolean rchoose( const char * region_name )
{
    assert( region_name != NULL );
    Boolean passed = false;
    RegionNode curr; //=chosen_one
    if ( region_name != NULL )
    {
        curr = search( region_name ); //from regionsList.h
        if ( curr != NULL )
        {
            currRegion = curr;
            passed = true;
        }
        else
        {
            passed = false;
        }
    }
    return passed;
} //rchoose

//return the name of the currently chosen region 
const char * rchosen()
{
    const char * currName = NULL;
    assert( currRegion->name != NULL );
    if ( currName != NULL )
    {
        if ( currRegion->name != NULL )
        {
            currName = currRegion->name;
            assert( strcmp( currRegion->name, currName ) == 0 );
        }
    }
    return currName;
} //rchosen

void * ralloc( r_size_t block_size )
{
    assert( block_size > 0 );
    assert( currRegion != NULL );
    assert( currRegion->block != NULL );

    r_size_t rounded = roundUp( block_size );
    OneBlock * newBlock = NULL; //=new_block
    void * dataStart = NULL; //=block_data_start

    if ( block_size > 0 && currRegion != NULL && currRegion->block != NULL && ( currRegion->size - currRegion->usedBytes ) >= rounded )
    {
        newBlock = createBlock( currRegion->size, currRegion->data, rounded, currRegion->block );
        if ( newBlock != NULL )
        {
            currRegion->usedBytes += rounded;
            // zero_block_data
            unsigned char * blockPtr; //ptr
            for ( blockPtr = newBlock->start; ( void * ) blockPtr < newBlock->start; blockPtr++ )
            {
                *blockPtr = 0;
                //assert( *blockPtr == 0 );
            }
            dataStart = newBlock->start;
        }
    } //
    return dataStart;
} //ralloc

r_size_t rsize( void * block_ptr )
{
    assert( currRegion != NULL );
    assert( block_ptr != NULL );
    OneBlock * curr; //=search_block
    r_size_t result;
    if ( currRegion != NULL && block_ptr != NULL )
    {
        curr = blockSearch( currRegion->block, block_ptr );
        if ( curr == NULL )
        {
            result = 0;
        }
        else
        {
            assert( curr->size > 0 );
            if ( curr->size > 0 )
            {
                result = curr->size;
            }
        }
    }
    else
    {
        result = 0;
    }
    return result;
} //rsize

Boolean rfree( void * block_ptr )
{
    assert( block_ptr != NULL );
    assert( currRegion != NULL );
    RegionNode * curr; //=current_region
    OneBlock key = NULL; //=target
    int size; //=block_size

    if ( block_ptr != NULLL && currRegion != NULL )
    {
        curr = returnFirst();
        if ( key != NULL )
        {
            size = key->size;
        }
        while ( key == NULL && currRegion != NULL )
        {
            key = blockSearch( currRegion->block, block_ptr );
        }
        if ( deleteBlock( currRegion->block, block_ptr ) )
        {
            currRegion->usedBytes -= size;
        }
    } //big if
    return passed;
} //rfree

//destroy the region with the given name, free all related memory
void rdestroy( const char * region_name )
{
    assert( region_name !- NULL );
    Boolean passed; //=success
    RegionNode * curr; //=target_region

    if ( region_name != NULL )
    {
        curr = search( region_name );
        if ( curr != NULL )
        {
            if ( strcmp( curr->name, region_name ) == 0 )
            {
                passed = true;
            }
            if ( passed )
            {
                passed = destroyBlocks( curr->block );
                assert( passed );
                if ( passed )
                {
                    passed = delete( region_name );
                    assert( passed );
                    if ( passed )
                    {
                        if ( curr == currRegion )
                        {
                            currRegion = NULL;
                            assert( currRegion == NULL );
                        }
                        currRegion = NULL;
                        assert( currRegion == NULL );
                    }
                }
            } //big if passsed
        } //if curr != null
    } //if region_name!=NULL
} //rdestroy

//print all data structure, but not block contents. Show the name of each region, 
//Show the name of each region; underneath each, show the blocks allocated in them and their block sizes
void rdump()
{
    OneBlock * nowBlock; //=current_block
    RegionNode * nowRegion = returnFirst(); //=current_region
    double freeSpace; //=percent
    
    while ( nowRegion != NULL )
    {
        freeSpace = ( 1 - ( ( double ) nowRegion->usedBytes / ( double ) nowRegion->size ) ) * 100;
        nowBlock = getFirstBlock( nowRegion->block );
        printf( "Name of the current region: %s\n", nowRegion->name );
        printf( "Total size of the current region: %d\n", nowRegion->size );
        printf( "Number of used bytes of the current region: %d\n", nowRegion->usedBytes );
        
        if ( nowBlock != NULL )
        {
            printf( "Blocks allocated in the region:\n");
        }
        while ( nowBlock != NULL )
        {
            printf( "Pointer to the block: %p\n", nowBlock->start );
            printf( "Size of the block: %d\n", nowBlock->size );
        }
        printf( "\n" );
        nowRegion = returnNext();
    } //big while
} //rdump

// = round_to_block
r_size_t roundUp( r_size_t size )
{
    assert( size > 0 );
    r_size_t rounded;
    if ( size > 0 && size % 8 != 0 )
    {
        int divide = size / 8;
        size = 8 * ( divide + 1 );
        rounded = size;
    }
    else if ( size > 0 && size % 8 == 0 )
    {
        rounded = size;
    }

    assert( rounded & 8 == 0 );
    return rounded;
} //roundUp
