#ifndef _REGIONSLIST_H
#define _REGIONSLIST_H

typedef struct REGION_NODE regionNode;

struct REGION_NODE
{
    char * name; //name
    void * data;
    void * block; //block_list
    regionNode * next;
    r_size_t size;
    r_size_t usedBytes; //bytes_used
};

regionNode * insert();
boolean delete( const char * key );
//found = search
boolean found( const char * key ); //key = target
//= return_region
regionNode search( const char * key ); // = target
//= first_region
regionNode * returnFirst();
// = next_region
regionNode * returnNext();

#endif
