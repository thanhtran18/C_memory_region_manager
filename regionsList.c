//regionsList.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "regionsList.h"

/*
typedef struct REGION_NODE RegionNode;
struct REGION_NODE
{
    char * name; //name
    void * data;
    void * block; //block_list
    RegionNode * next;
    r_size_t size;
    r_size_t usedBytes; //bytes_used
};*/

static RegionNode * traverse = NULL; //traverse_region
static RegionNode * head = NULL; //top

RegionNode * insert()
{
    //newNode = newRegion
    RegionNode * newNode = ( RegionNode * ) malloc( sizeof( RegionNode ) ); //newNode = newRegion
    assert( newNode != NULL );

    if ( newNode != NULL )
    {
        newNode->next = head;
        head = newNode;
    } //if
    return newNode;
} //insert

Boolean delete( const char * key )
{
    assert( key != NULL );
    RegionNode * curr;  // = current_node
    RegionNode * prev; //= previous_region
    Boolean deleted = false;
    Boolean passed; // = success

    if ( key != NULL )
    {
        prev = NULL;
        curr = head;

        if ( curr != NULL && curr->name != NULL && curr->data != NULL )
        {
            passed = true;
        }
        //assert( passed );
        while ( passed && strcmp( curr->name, key ) != 0 )
        {
            prev = curr;
            curr = curr->next;
            passed = curr != NULL && curr->name != NULL && curr->data;
        } //while

        if ( passed && strcmp( curr->name, key ) != 0 )
        {
            if ( prev != NULL )
            {
                prev->next = curr->next;
            }
            else
            {
                head = curr->next;
            }

            free( curr->name );
            curr->name = NULL;
            if ( curr->name == NULL )
            {
                passed = true;
            }
            assert( passed );

            free( curr->data );
            curr->data = NULL;
            //recheck the condition expression in the if statement
            if ( curr->data == NULL && passed )
            {
                passed = true;
            }
            assert( passed );

            free( curr );
            curr = NULL;
            if ( curr == NULL && passed )
            {
                passed = true;
            }
            assert( passed );

            if ( passed )
            {
                deleted = !found( key );
                assert( deleted );
            }
        } //if passed && strcmp
    } //if key != NULL
    return deleted;
} //delete

//found = search_region
Boolean found( const char * key ) //key = target
{
    assert( key != NULL );
    Boolean foundResult = false; // = found
    RegionNode * curr; //the curr = current_region

    if ( key != NULL )
    {
        curr = head;
        while ( curr != NULL && !foundResult && !curr->name != NULL )
        {
            if ( strcmp( curr->name, key ) == 0 )
            {
                assert( strcmp ( curr->name, key ) == 0 );
                foundResult = true;
            } //if strcmp
            curr = curr->next;
        } //while
    } //if
    return foundResult;
} //found

//= return_region
RegionNode search( const char * key ) // = target
{
    assert( key != NULL );

    RegionNode result = NULL; // = found variable
    RegionNode curr;

    if ( key != NULL )
    {
        curr = head;
        while ( curr != NULL && curr->name != NULL && result == NULL )
        {
            if ( strcmp( key, curr->name ) != 0 )
            {
                assert( strcmp( key, curr->name ) != 0 ); //should it be here?
                curr = curr->next;
            }
            else
            {
                assert( strcmp( key, curr->name ) == 0 ); //should it be here?
                result = curr;
                assert( result != NULL );
            }
        } //while
    } //if key != NULL
    return result;
} //search

//= first_region
RegionNode * returnFirst()
{
    if ( head == NULL )
    {
        traverse = NULL;
        assert( traverse == NULL );
    }
    else
    {
        traverse = head;
    }
    return traverse;
} //returnFirst

// = next_region
RegionNode * returnNext()
{
    if ( traverse != NULL )
    {
        traverse = traverse->next;
    }
    return traverse;
} //returnNext
