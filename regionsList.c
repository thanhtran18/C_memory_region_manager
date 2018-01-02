//-----------------------------------------------------------------------------------
// AUTHOR:           CONG THANH TRAN
// 
// REMARKS: This module is the data structure used for managing a list of memory regions.
//-----------------------------------------------------------------------------------

//regionsList.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "regionsList.h"

//-------------------------------------------------------------------------------------
// CONSTANTS and TYPES
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
// VARIABLES
//-------------------------------------------------------------------------------------

static RegionNode * traverse = NULL; //the current regions are in process
static RegionNode * head = NULL;     //the head node of the list of regions
static int numRegions = 0;           //number of regions in the list
static int numTraversals = 0;        //the current position of the traversing node

//-------------------------------------------------------------------------------------
// PROTOTYPES
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
// FUNCTIONS
//-------------------------------------------------------------------------------------



//-----------------------------------------------------------------------------------
// validateRegions - invariant
//
// PURPOSE: this function will check to see if the number of regions is zero, then our
//          head node should be NULL, if it's not NULL then the number of regions should
//          be greater than zero.
//
//-----------------------------------------------------------------------------------
static void validateRegions()
{
#ifndef NDEBUG
    RegionNode * currNode = head; //the current region
    int regionCount = 0;          //count of the regions
#endif
    if ( numRegions == 0 )
    {
        assert( head == NULL );
    }
    else if ( numRegions == 1 )
    {
        assert( head->next == NULL );
    }
    else //numRegions > 1
    {
        assert( head != NULL);
        assert( head->next != NULL );
    }

    //this will traverse through the list of regions and make sure the number of nodes we 
    //    count by scanning the list is the same as the number of nodes in our static variable.
#ifndef NDEBUG
    while ( currNode )
    {
        regionCount++;
        currNode = currNode->next;
    }
    assert( regionCount == numRegions );
#endif
} //validateRegions

//-----------------------------------------------------------------------------------
// insertRegion
//
// PURPOSE: this function will create a new region node in the region list
//
// RETURN
//     this function will return the region that just has been created.
//-----------------------------------------------------------------------------------
RegionNode * insertRegion()
{
    int numRegionsBefore = 0;    //used in comparing the number of regions before and after inserting
    numRegionsBefore = numRegions;
    RegionNode * newNode = ( RegionNode * ) malloc( sizeof( RegionNode ) ); //the new node will be created and returned

    validateRegions();
    assert( newNode != NULL );

    if ( newNode != NULL )
    {
        newNode->next = head;
        head = newNode;
        numRegions++;
    } //if

    //either we couldn't insert a new region or the number of regions now should be larger than the old number
    assert( newNode == NULL || numRegionsBefore < numRegions );
    validateRegions();
    return newNode;
} //insertRegion

//-----------------------------------------------------------------------------------
// delete
//
// PURPOSE: this function will delete a region with the given name
//
// PARAMETER: 
//     key - the name of the region that needs to be deleted
//
// RETURN
//     this function will return true if the region is successfully deleted, false otherwise
//-----------------------------------------------------------------------------------
Boolean delete( const char * key )
{
    int numRegionsBefore = 0;  //used in comparing the number of regions before and after deleting
    numRegionsBefore = numRegions;
    RegionNode * curr;         //the current region that is being processed
    RegionNode * prev;         //the previous region of the current one
    Boolean deleted = false;   //returned value-true if successfully deleted, false otherwise
    Boolean passed = false;    //a boolean variable used in other conditions to make sure things run as expected

    validateRegions();
    assert( key != NULL );

    if ( key != NULL )
    {
        curr = head;
        prev = NULL;

        if ( curr != NULL && curr->name != NULL && curr->data != NULL )
        {
            passed = true;
        }
        assert( passed );
        //find the region
        while ( passed && strcmp( curr->name, key ) != 0 )
        {
            prev = curr;
            curr = curr->next;
            if ( curr != NULL && curr->name != NULL && curr->data != NULL )
            {
                passed = true;
            }
        } //while

        if ( passed && strcmp( curr->name, key ) == 0 )
        {
            if ( prev != NULL )
            {
                prev->next = curr->next;
            }
            else
            {
                head = curr->next;
            }

            //free the name, data and the region itself, then set them all to NULL
            free( curr->name );
            curr->name = NULL;
            if ( curr->name == NULL )
            {
                passed = true;
            }
            assert( passed );

            free( curr->data );
            curr->data = NULL;
            
            if ( curr->data == NULL && passed )
            {
                passed = true;
            }
            assert( passed );

            free( curr );
            curr = NULL;
            if ( curr == NULL && passed )
            {
                deleted = !found( key );
                assert( deleted );
                numRegions--;
                validateRegions();
            }
        } //if passed && strcmp
    } //if key != NULL

    //either we couldn't delete the given region or the number of regions now should be smaller than the old number
    assert( deleted == false || numRegionsBefore > numRegions );
    return deleted;
} //delete

//-----------------------------------------------------------------------------------
// found
//
// PURPOSE: this function will scan through the list and find out if a specific region
//          is already in the list
//
// PARAMETER: 
//     key - the name of the region that needs to be searched for
//
// RETURN
//     this function will return true if the region is already in the list, false otherwise
//-----------------------------------------------------------------------------------
Boolean found( const char * key )
{
    assert( key != NULL );

    Boolean result = false; //returned value of the function
    RegionNode * curr;      //the current region is in processing

    if ( key != NULL )
    {
        curr = head;
        while ( curr != NULL && !result && curr->name != NULL )
        {
            if ( strcmp( curr->name, key ) == 0 )
            {
                result = true;
            } //if strcmp
            curr = curr->next;
        } //while
    } //if
    return result;
} //found

//-----------------------------------------------------------------------------------
// search
//
// PURPOSE: this function will search for a region with a given name
//
// PARAMETER: 
//     key - the name of the region that needs to be deleted
//
// RETURN
//     this function will return the region itself if the region is in the list, NULL otherwise
//-----------------------------------------------------------------------------------
RegionNode * search( const char * key )
{
    int searchCount = 0;        //keep track of how far we have gone through in the list
    RegionNode * result = NULL; //returned value, intialized NULL
    RegionNode * curr;          //the current region node that is being processed

    validateRegions();
    assert( key != NULL );

    if ( key != NULL )
    {
        curr = head;
        //traverse through the list until the region is found (if any)
        while ( curr != NULL && curr->name != NULL && result == NULL )
        {
            if ( strcmp( key, curr->name ) != 0 )
            {
                curr = curr->next;
                searchCount++;
            }
            else
            {
                result = curr;
                assert( result != NULL );
                //make sure that we're still in the list
                assert( searchCount <= numRegions );
            }
        } //while
    } //if key != NULL
    
    assert( result == NULL || searchCount <= numRegions );
    return result;
} //search

//-----------------------------------------------------------------------------------
// returnFirst
//
// PURPOSE: this function will return the first region (the head node) in the list
//
// RETURN
//     this function will return the first region itself if it exists, NULL otherwise
//-----------------------------------------------------------------------------------
RegionNode * returnFirst()
{
    validateRegions();

    if ( head == NULL )
    {
        traverse = NULL;
        assert( traverse == NULL );
    }
    else
    {
        traverse = head;
        assert( traverse != NULL );
        numTraversals = 0;
        //make sure that we're still in the list
        assert( numTraversals <= numRegions );
    }
    validateRegions();
    return traverse;
} //returnFirst

//-----------------------------------------------------------------------------------
// returnNext
//
// PURPOSE: this function will return the next region in the list
//
// RETURN
//     this function will return the next region itself if it exists, NULL otherwise
//-----------------------------------------------------------------------------------
RegionNode * returnNext()
{
    validateRegions();

    if ( traverse != NULL )
    {
        traverse = traverse->next;
        numTraversals++;
        assert( numTraversals <= numRegions ); //make sure that we're still in the list
    }
    validateRegions();
    return traverse;
} //returnNext
