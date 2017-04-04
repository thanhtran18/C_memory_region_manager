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
    

} //rinit
