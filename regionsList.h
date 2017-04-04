#ifndef _REGIONSLIST_H
#define _REGIONSLIST_H

typedef struct REGION_NODE RegionNode; //=region_node

struct REGION_NODE
{
    char * name; //name
    void * data;
    void * block; //block_list
    RegionNode * next;
    r_size_t size;
    r_size_t usedBytes; //bytes_used
};

RegionNode * insert();
Boolean delete( const char * key );
//found = search
Boolean found( const char * key ); //key = target
//= return_region
RegionNode search( const char * key ); // = target
//= first_region
RegionNode * returnFirst();
// = next_region
RegionNode * returnNext();

#endif
