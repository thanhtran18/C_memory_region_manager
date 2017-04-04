#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "regions.h"

Boolean rinit( const char *region_name, r_size_t region_size )
{
    assert( region_size > 0 );
    Boolean success = false;
    //if the size is not a multiple of 8, then round it up to the nearest multiple of 8
    if ( region_size % 8 != 0 )
    {
        int divide = region_size / 8;
        region_size = 8 * ( divide + 1 );
    } //if
    

} //rinit
