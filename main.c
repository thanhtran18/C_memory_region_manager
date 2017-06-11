//-----------------------------------------------------------------------------------
// NAME:           CONG THANH TRAN
// STUDENT NUMBER: 7802106
// COURSE:         COMP2160, SECTION: A01
// INSTRUCTOR:     FRANKLIN BRISTOW
// ASSIGNMENT:     assignment 4 - MEMORY REGIONS
// 
// REMARKS: This program contains all function implementation for all the function signatures
//          in the given regions.h header file
//-----------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "regions.h"
#include "blocks.h"

//-------------------------------------------------------------------------------------
// VARIABLES
//-------------------------------------------------------------------------------------
static int testsExecuted = 0;
static int testsFailed = 0;

//-------------------------------------------------------------------------------------
// PROTOTYPES
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
// FUNCTIONS
//-------------------------------------------------------------------------------------



//-----------------------------------------------------------------------------------
// testResults
//
// PURPOSE: this function will print out the test results of the test unit
//-----------------------------------------------------------------------------------
void testResults()
{
    if ( testsFailed == 0 )
    {
        printf( "\nI'm DONE TESTING! The whole memory regions thing worked!!!\n" );
    }
    else
    {
        printf( "\nHmm, there are still some problems with the programs. I need to re-check everything!\n" );
    }
    printf( "\nTests executed: %d.\n", testsExecuted );
    printf( "Tests passed: %d. (✓)\n", ( testsExecuted - testsFailed ) );
    printf( "Tests failed: %d.\n¯\\_(ツ)_/¯\n", testsFailed );
} //testResults

//-----------------------------------------------------------------------------------
// test
//
// PURPOSE: this function will test two given boolean variables
//-----------------------------------------------------------------------------------
void test( Boolean result, Boolean expected )
{
    if ( result != expected )
    {
        testsFailed++;
    }
    testsExecuted++;
} //test

//-----------------------------------------------------------------------------------
// testRinit
//
// PURPOSE: this function will test the function rinit() from regions.c
//
// PARAMETERS:
//     name        - a parameter of rinit()
//     region_size - a parameter of rinit()
//     expected    - expected boolean value of the test
//-----------------------------------------------------------------------------------
void testRinit( const char * name, r_size_t region_size, Boolean expected )
{
    Boolean result = rinit( name, region_size );
    test( result, expected );
} //testRinit

//-----------------------------------------------------------------------------------
// testRchoose
//
// PURPOSE: this function will test the function rchoose() from regions.c
//
// PARAMETERS:
//     name        - a parameter of rchoose()
//     expected    - expected boolean value of the test
//-----------------------------------------------------------------------------------
void testRchoose( const char * name, Boolean expected )
{
    Boolean result = rchoose( name );
    test( result, expected );
} //testRchoose

//-----------------------------------------------------------------------------------
// testRchosen
//
// PURPOSE: this function will test the function rchosen() from regions.c
//
// PARAMETERS:
//     name        - name will be compared
//     expected    - expected boolean value of the test
//-----------------------------------------------------------------------------------
void testRchosen( const char * name, Boolean expected )
{
    Boolean result;
    if ( 0 != strcmp( rchosen(), name ) )
    {
        result = false;
    }
    else
    {
        result = true;
    }
    test( result, expected );
} //testRchosen

//-----------------------------------------------------------------------------------
// testRfree
//
// PURPOSE: this function will test the function rfree() from regions.c
//
// PARAMETERS:
//     block_ptr - a parameter of rfree()
//     expected  - expected boolean value of the test
//-----------------------------------------------------------------------------------
void testRfree( void * block_ptr, Boolean expected )
{
    Boolean result = rfree( block_ptr );
    test( result, expected );
} //testRfree

//-----------------------------------------------------------------------------------
// testRsize
//
// PURPOSE: this function will test the function rsize() from regions.c
//
// PARAMETERS:
//     block_ptr - a parameter of rsize()
//     expected  - expected boolean value of the test
//-----------------------------------------------------------------------------------
void testRsize( void * block_ptr, r_size_t expected )
{
    Boolean result = rsize( block_ptr ) == expected;
    test( result, true );
} //testRsize

//-----------------------------------------------------------------------------------
// testRalloc
//
// PURPOSE: this function will test the function ralloc() from regions.c
//
// PARAMETERS:
//     block_size - a parameter of ralloc()
//     expected   - expected boolean value of the test
//-----------------------------------------------------------------------------------
void testRalloc( r_size_t block_size, void * expected )
{
    void * result = ralloc( block_size );
    if ( result != expected )
    {
        testsFailed++;
    }
    testsExecuted++;
}

//-----------------------------------------------------------------------------------
// generalChecking
//
// PURPOSE: this function will check the input boolean value if it's true
//
// PARAMETERS:
//     result - input boolean value of the test
//-----------------------------------------------------------------------------------
void generalChecking( Boolean result )
{
    if ( result == false )
    {
        testsFailed++;
    }
    testsExecuted++;
} //generalChecking

//-----------------------------------------------------------------------------------
// freeAllBlocks
//
// PURPOSE: this function will call testRfree() to test rfree() and free all blocks
//
// PARAMETERS:
//     blocks - all blocks
//-----------------------------------------------------------------------------------
Boolean freeAllBlocks( void * blocks[] )
{
    int i = 0;
    Boolean passed = true;
    while ( blocks[i++] != NULL )
    {
        if ( rsize( blocks[i - 1] ) > 0 )
        {
            testRfree( blocks[i - 1], true );
        }
        if ( rsize( blocks[i - 1] ) != 0 )
        {
            passed = false;
        }
    } //while
    return passed;
} //freeAllBlocks

//-----------------------------------------------------------------------------------
// normalCases
//
// PURPOSE: this function contains many tests (normal cases). Each test is discribed 
//          by the commands next to it.
//-----------------------------------------------------------------------------------
void normalCases()
{
    OneBlock * blockPtr;
    unsigned short position;
    void * blocks[128];

    printf( "NORMAL CASES TESTING\n" );
    printf( "--------------------" );

    //test rchoose() and rchosen() before and after rdestroy()
    testRinit( "1st Region", 120, true );
    testRchosen( "1st Region", true );
    testRinit( "2nd Region", 160, true );
    testRchosen( "2nd Region", true );
    testRchoose( "1st Region", true );
    testRchosen( "1st Region", true );
    testRchoose( "2nd Region", true );
    testRchosen( "2nd Region", true );
    rdestroy( "1st Region" );
    rdestroy( "2nd Region" );
    testRchoose( "1st Region", false );
    testRchoose( "2nd Region", false );
    generalChecking( rchosen() == NULL );

    //test with a non-multiple-of-8 size, it should return a greater-nearest multiple of 8
    testRinit( "Not-a-multiple-of-8", 9, true );
    blocks[0] = ralloc(9);
    testRsize( blocks[0], 16 ); //should be true
    rdestroy( "Not-a-multiple-of-8" );
    generalChecking( rchosen() == NULL );

    //test with one sample region
    testRinit( "Region 1", 1024, true );
    testRchosen( "Region 1", true );
    //this block will be filled with 8-byte blocks
    printf( "\nCreating a region and fill it with 8-byte blocks...\n");
    for ( int i = 0; i < 1024/8; i++ )
    {
        blocks[i] = ralloc(1);
        Boolean checkingResult = NULL != blocks[i];
        generalChecking( checkingResult );
        testRsize( blocks[i], 8 );
    }

    printf( "\nCan I add more if the region is full?\n" );
    testRalloc( 1, NULL );

    printf( "\nFree a certain 8-byte block, I'm trying to replace it with a 32-byte block..\n");
    testRfree( blocks[30], true );
    testRsize( blocks[30], 0 ); //check if the block was freed
    testRalloc( 32, NULL );
    printf( "Well, I think I failed doing that..Which is good.\n" );

    printf( "\nWhat if I create some empty blocks in the middle? Let's make it a 40-byte empty block.\n" );
    testRfree( blocks[62], true );
    testRfree( blocks[63], true );
    testRfree( blocks[64], true );
    testRfree( blocks[65], true );
    testRfree( blocks[66], true );
    //replace four 8-byte blocks in the middle by one 32-byte block
    blocks[62] = ralloc(32);
    testRsize( blocks[62], 32 );

    printf( "Now the region has some empty blocks, let's free all the remaining!\n");
    generalChecking( freeAllBlocks( blocks ) );
    testRsize( blocks, 0 );

    printf( "Now is the time to destroy the whole region!\n" );
    rdestroy( "Region 1" );
    Boolean nullChecking = rchosen() == NULL;
    if ( nullChecking == true )
    {
        printf( "->Done, all have been set to NULL.\n");
    }
    else
    {
        printf( "->Something's wrong (x).\n" );
    }

    //create 2 different regions with different sizes, and then choose each region respectively to work with
    printf( "Create two different regions with different sizes, choose each of them respectively to work with. And destroy them after...\n" );
    testRinit( "Region 001", 2048, true ); //1024*2
    testRinit( "Region 002", 3072, true );
    testRchoose( "Region 001", true );
    testRchosen( "Region 001", true );
    //fill this with 8-byte blocks
    for ( int j = 0; j < 2048/8; j++ )
    {
        ralloc(1);
    }
    rdestroy( "Region 001" ); //destroy after testing
    testRchoose( "Region 001", false );
    generalChecking( rchosen() == NULL );

    testRchoose( "Region 002", true );
    testRchosen( "Region 002", true );
    //fill this with 8-byte blocks
    for ( int j = 0; j < 3072/8; j++ )
    {
        ralloc(1);
    }
    rdestroy( "Region 002" ); //destroy after testing
    testRchoose( "Region 002", false );
    generalChecking( rchosen() == NULL );
    
    printf( "\nCreate a block that has the same size with the one just has been freed, see if they have the same starting address in the memory\n" );
    testRinit( "Region 003", 128, true );
    generalChecking( ralloc(32) != NULL );
    blockPtr = ralloc(32);
    generalChecking( blockPtr != NULL );
    generalChecking( ralloc(64) != NULL );
    position = ( unsigned short ) blockPtr->start; //get the position of the block
    testRfree( blockPtr, true ); //free this block
    blockPtr = NULL;
    blockPtr = ralloc(32); //create another block of the same size to see if they have the same starting address
    generalChecking( blockPtr != NULL );
    generalChecking( position == ( unsigned short ) blockPtr->start ); //they should have the same starting address
    if ( position == ( unsigned short ) blockPtr->start )
    {
        printf( "->Yes, they do have the same starting address!\n" );
    }
    else
    {
        printf( "Hmm, it doesn't seem like they do. Recheck it please!\n" );
    }
    rdestroy( "Region 003" );
    generalChecking( rchosen() == NULL );

    //Test first fit strategy
    printf( "\nNow we should test if the first fit algorithm works by adding and creating some blocks with a specific size in the region\n" );
    printf( "This includes a lot of deleting and adding blocks when there is not enough contiguous space.\n" );
    //create a region with the size of 256 bytes
    testRinit( "Region 004", 256, true );
    testRchosen( "Region 004", true );
    //divided the region into 3 blocks with 64, 128 and 64 bytes
    //the region now looks like this:  [ blocks[0] | blocks[1] | blocks[2] ]
    //                                 [  64 bytes | 128 bytes | 64 bytes  ]
    blocks[0] = ralloc(64);
    testRsize( blocks[0], 64 );
    blocks[1] = ralloc(128);
    testRsize( blocks[1], 128 );
    blocks[2] = ralloc(64);
    testRsize( blocks[2], 64 );
    testRalloc( 10, NULL ); //there is no space to add
    testRfree( blocks[1], true ); //free the middle block
    blocks[1] = ralloc(10);
    testRsize( blocks[1], 16 );
    testRalloc( 128, NULL ); //not enough space
    blocks[3] = ralloc(8); //add a 8-byte block right after block 1, now there is 104 bytes left in the middle part
    //the region now looks like this: [ blocks[0] | blocks[1] | blocks[3]| empty     | blocks[2] ]
    //                                [ 64 bytes  | 16 bytes  | 8 bytes  | 104 bytes | 64 bytes  ]
    testRsize( blocks[3], 8 );
    blocks[4] = ralloc(104);
    testRsize( blocks[4], 104 ); //the region is now full again
    testRalloc( 10, NULL ); //no more space to add

    testRfree( blocks[0], true );
    testRfree( blocks[2], true ); //free the beginning and the end blocks
    blocks[0] = ralloc(32); //add a 32-byte block to the beginning, there are 32 bytes remaining in this beginning part
    testRsize( blocks[0], 32 );
    blocks[2] = ralloc(40); //add a 40-byte block after the middle part (the 64-byte ending block which was freed)
    testRsize( blocks[2], 40 ); //this ending block now has 24 empty bytes.
    //the region now looks like this: [ blocks[0] | empty    | blocks[1] | blocks[3]| blocks[4] | blocks[2] | empty    ]
    //                                [ 32 bytes  | 32 bytes | 16 bytes  | 8 bytes  | 104 bytes | 40 bytes  | 24 btyes ]
    blocks[5] = ralloc(24); //it should add a 24-byte block after blocks[0], there is now a 8-byte empty block after blocks[0]
    testRsize( blocks[5], 24 );
    blocks[6] = ralloc(24); //this time it should add a 24-byte block after blocks[2] (the empty end), now this end is full
    testRsize( blocks[6], 24 );
    blocks[7] = ralloc(3); //now it should add a 8-byte block to the empty part after blocks[5]
    testRsize( blocks[7], 8 );
    //now the region "Region 007" should be full
    //the region now looks like this: [ blocks[0] | blocks[5] | blocks[7] | blocks[1] | blocks[3]| blocks[4] | blocks[2] | blocks[6] ]
    //                                [ 32 bytes  | 24 bytes  | 8 bytes   | 16 bytes  | 8 bytes  | 104 bytes | 40 bytes  | 24 btyes  ]
    testRalloc( 1, NULL ); //cannot add anything else
    //destroy the region after testing
    rdestroy( "Region 004" );
    printf( "Passed all relating tests => The first-fit algorithm worked perfectly!" );
    printf("\nNow I'm done with testing normal cases!\n" );

} //normalCases

//-----------------------------------------------------------------------------------
// edgeCases
//
// PURPOSE: this function contains many tests (edge cases). Each test is discribed 
//          by the commands next to it.
//-----------------------------------------------------------------------------------
void edgeCases()
{
    void * hugeBlock;
    void * blocks[8191];
    printf( "\nEDGE CASES TESTING\n" );
    printf( "------------------\n" );

    //try to choose with a non-existent region
    printf( "Trying to choose a region named \"Batman Superman\", which doesn't exist\n" );
    testRchoose( "Batman Superman", false );

    //try to destroy a non-existent region
    printf( "Trying to destroy a region named \"Spiderman Ironman\", which doesn't exist\n" );
    rdestroy( "Spiderman Ironman" );

    //rchoose() and rdestroy() an empty region
    printf( "Trying to choose and destroy an empty region...\n" );
    testRinit( "Empty region", 20, true );
    testRchoose( "Empty region", true );
    testRchosen( "Empty region", true );
    rdestroy( "Empty region" );
    generalChecking( rchosen() == NULL );

    //rchoose() and rdestroy() a full region
    printf( "Trying to choose and destroy a full region...\n" );
    testRinit( "Full region", 128, true );
    generalChecking( ralloc(32) != NULL );
    generalChecking( ralloc(64) != NULL );
    generalChecking( ralloc(32) != NULL ); //the region is now full
    testRalloc( 8, NULL ); //no more space to add
    testRchoose( "Full region", true );
    testRchosen( "Full region", true );
    rdestroy( "Full region" );
    generalChecking( rchosen() == NULL );

    //super long name
    printf( "Testing a super long name...\n" );
    testRinit( "How long is this name? I don't know. Oh these words still belong to the name. I want to stop here. I think this is long enough. OK then. I will stop here\n", 10, true );
    testRchosen( "How long is this name? I don't know. Oh these words still belong to the name. I want to stop here. I think this is long enough. OK then. I will stop here\n", true );
    rdestroy( "How long is this name? I don't know. Oh these words still belong to the name. I want to stop here. I think this is long enough. OK then. I will stop here\n" );
    generalChecking( rchosen() == NULL );

    //a name with a null byte character in the middle
    printf( "Testing a name with a null byte character in the middle...\n" );
    testRinit( "Null byte\0 character", 20, true );
    testRchoose( "Null byte", true );
    testRchoose( "Null byte character", false ); //this is not the name of the region
    testRchoose( "Null byte\0 character", true );
    testRchosen( "Null byte", true );
    rdestroy( "Null byte" );
    generalChecking( rchosen() == NULL );

    //empty name
    printf( "Testing an empty name...\n" );
    testRinit( "", 1, true );
    testRchosen( "", true );
    rdestroy( "" );
    generalChecking( rchosen() == NULL );

    //special character name
    printf( "Testing a region with a name which is a new line character...\n" );
    testRinit( "\n", 1, true );
    testRchosen( "\n", true );
    rdestroy( "\n" );
    generalChecking( rchosen() == NULL );

    //region with -100 size
    printf( "Testing a negative size...\n" );
    testRinit( "Negative size region", -100, true );
    testRchosen( "Negative size region", true );
    OneBlock * negative = ralloc(-100);
    generalChecking( negative != NULL );
    testRsize( negative, 65440 );
    rdestroy( "Negative size region" );
    generalChecking( rchosen() == NULL );

    //How about a really big region with maximum size? The maximum size is 65528 (multiple of 8)
    printf( "Testing a possibly maximum size region...\n" );
    testRinit( "Biggest size", -1, true );
    testRchosen( "Biggest size", true );
    hugeBlock = ralloc(-1); //fill the whole region with a huge block
    testRsize( hugeBlock, 65528 );
    rdestroy( "Biggest size" );
    generalChecking( rchosen() == NULL );

    //create 1 region with max size and fill it with 8-byte blocks, to test rfree() all of them one by one
    printf( "Creating a maximum size region with all 8-byte blocks to rfree() them all one by one\n" );
    testRinit( "Another maximum region", -1, true );
    for ( int i = 0; i < 65528/8; i++ )
    {
        blocks[i] = ralloc(1);
        testRsize( blocks[i], 8 );
    }
    //free one by one
    printf( "Freeing...\n" );
    for ( int i = 0; i < 65528/8; i++ )
    {
        testRfree( blocks[i], true );
        testRsize( blocks[i], 0 );
    }
    printf( "Done freeing!\n" );
    rdestroy( "Another maximum region" );
    generalChecking( rchosen() == NULL );
    
    //Testing false cases with DNDEBUG
    printf( "\n>>>DNDEBUG TESTING. IF -DNDEBUG FLAG IS OFF, THERE WILL BE ASSERTION FAILED!!!<<<\n" );
    printf( "---------------------------------------------------------------------------------\n" );

    //create 2 regions with the same name
    printf( "Trying to create 2 regions with the same name...\n" );
    testRinit( "Same name", 1, true );
    testRinit( "Same name", 1, false ); //cannot create a region with the same name
    rdestroy( "Same name" );

    printf( "Trying to create NULL regions, 0 size regions,... All should be failed\n" );
    testRinit( NULL, 100, false );
    testRinit( "Zero size", 0, false );
    testRinit( NULL, 0, false );
    testRchoose( NULL, false );
    generalChecking( ralloc(0) == NULL );
    testRsize( NULL, 0 );
    testRfree( NULL, false );
    rdestroy( NULL );
    printf( "Trying to allocate a block of 16 bytes when there is no region!\n" );
    generalChecking( rchosen() == NULL );
    generalChecking( ralloc(10) == NULL );

} //edgeCases 

//-----------------------------------------------------------------------------------
// main
//
// PURPOSE: this function will call other functions to perform the tests
//-----------------------------------------------------------------------------------
int main( int argc, char* argv[] )
{
    normalCases();
    edgeCases();
    testResults();
    return EXIT_SUCCESS;
}