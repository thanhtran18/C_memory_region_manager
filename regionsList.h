//-----------------------------------------------------------------------------------
// NAME:           CONG THANH TRAN
// STUDENT NUMBER: 7802106
// COURSE:         COMP2160, SECTION: A01
// INSTRUCTOR:     FRANKLIN BRISTOW
// ASSIGNMENT:     assignment 4 - MEMORY REGIONS
// 
// REMARKS: This module is the header file of regionsList.c. This will be included in
//          other files for further using.
//-----------------------------------------------------------------------------------

//regionsList.h

#include "regions.h"
#ifndef _REGIONSLIST_H
#define _REGIONSLIST_H

typedef struct REGION_NODE RegionNode;

//-----------------------------------------------------------------------------------
// RegionNode - struct
//
// PURPOSE: each RegionNode has a unique name, it contains data, a list of blocks, a pointer
//          to the next region in the list, size and number of used bytes.
//-----------------------------------------------------------------------------------
struct REGION_NODE
{
    char * name;        //a unique name of each region
    void * data;        //data contained in that region
    void * block;       //a list of blocks in that region
    RegionNode * next;  //a pointer to the next region in the list
    r_size_t size;      //size of that region
    r_size_t usedBytes; //number of used bytes in the region
};

//this function will create a new region node in the region list
RegionNode * insertRegion();

//this function will delete a region with the given name
Boolean delete( const char * key );

//this function will scan through the list and find out if a specific region is already in the list
Boolean found( const char * key );

//this function will search for a region with a given name
RegionNode * search( const char * key );

//this function will return the first region (the head node) in the list
RegionNode * returnFirst();

//this function will return the next region in the list
RegionNode * returnNext();

#endif
