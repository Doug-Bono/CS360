#include <getopt.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <errno.h>
#include "functions.h"
// other headers as needed

/*

Memory trace example: 

I 0400d7d4,8
 M 0421c7f0,4
 L 04f6b868,8

The format is:
[space] <operation> <address>,<size>

"Operation" field denotes the type of memory access.
    I - denotes instruction load
    L - denotes a data load
    S - denotes a data store
    M - denotes a data modify (i.e. data load followed by data store)

Never a space before each "I". Always a space before each M, L, and S.

"Address" field specifies a 64-bit hexadecimal memory address.
"Size" field specifies the # of bytes accessed by the operation.


Developing a Cache Simulator:
    We assume a least recently used (LRU) replacement policy when choosing which cahce line to evict.

    The simulator takes the following command line arguments:

        Usage: ./cachesim [-hv] -s <s> -E <E> -b <b> -t <tracefile>

            • -h: Optional help flag that prints usage info
            • -v: Optional verbose flag that displays trace info
            • -s <s>: Number of set index bits (S = 2^S is the number of sets)
            • -E <E>: Associativity (number of lines per set)
            • -b <b>: Number of block bits (B = 2^b is the block size)
            • -t <tracefile>: Name of the valgrind trace to replay
    
    Example command line argument:

            linux> ./cachesim -s 4 -E 1 -b 4 -t traces/trace02.dat
            hits:4 misses:5 evictions:3

        Verbose Mode:

            linux> ./cachesim -v -s 4 -E 1 -b 4 -t traces/trace02.dat
            L 10,1 miss
            M 20,1 miss hit
            L 22,1 hit
            S 18,1 hit
            L 110,1 miss eviction
            L 210,1 miss eviction
            M 12,1 miss eviction hit
            hits:4 misses:5 evictions:3


For the assignment, we are only interested in data cache performance, so simulator should ignore all instruction cache accesses
 (lines that start with "I"). 

Recall: Trace always contains "I" in the first column (with no space before it) and "M", "L", "S" in the second column
 with a preceeding space.

*/

#define ADDRESS_LENGTH 64  // 64-bit memory addressing

int s = 0, E = 0, b = 0;
bool verbose = false;
Cacheline **Cache = NULL; // Cache[set][line]
int hitCount = 0, missCount = 0, replaceCount = 0;
size_t accessCount = 0;

/*
 * starting point
 */
int main(int argc, char* argv[])
{
	// complete your simulator
    int c;
    char *traceFile = NULL;

    while ((c = getopt(argc, argv, "s:E:b:t:vh")) != -1)
    {
        switch(c)
        {
            case 's':
                s = atoi(optarg);
                break;
            
            case 'E':
                E = atoi(optarg);
                break;

            case 'b':
                b = atoi(optarg);
                break;

            case 't':
                traceFile = optarg;
                break;

            case 'v':
                verbose = true;
                break;
            
            case 'h': // Used code from PA1 documentation
                print_usage(argv);
                exit(0);
            
            default:
                print_usage(argv);
                exit(1);
        }
    }

    Cache = CreateCache(pow(2, s), E); // Initalize cache

    FILE *fileInput = fopen(traceFile, "r");  // Read file 

    char curLine[50];


    //ReadTrace(fileInput, curLine);
    
    while (fgets(curLine, sizeof(curLine), fileInput) != NULL)
    {
        if (curLine[0] == 'I') // Ignore instruction lines ALSO CHANGE *******
        {
            continue;
        }

        char operation;
        size_t address;
        int size;

        operation = 'A';
        address = 123;
        size = 1;

        if (VerboseCheck())
        {
            printf("%c %zu, %d", operation, address, size);
        }

        if (operation == 'L' || operation == 'S')
        {
            // access_result r = access_cache((uint64_t)addr);

            if (VerboseCheck())
            {
                // print_result(r);
                // printf("\n");
            }
        }
        
        else if (operation == 'M')
        {
            // access_result r1 = access_cache((uint64_t)addr);
            // access_result r2 = access_cache((uint64_t)addr);

            if (VerboseCheck())
            {
                // print_result(r1);
                // print_result(r2);
                // printf("\n");               
            }
        }
    }

    fclose(fileInput);
    free(Cache);

    
    // Debugging print statements
    printf("THESE ARE THE VALUES WE HAVE CURRENTLY \n");
    printf("VALUE FOR s: %d \n", s);
    printf("VALUE FOR E: %d \n", E);
    printf("VALUE FOR b: %d \n", b);
    printf("VALUE FOR traceFile: %s \n", traceFile);
    if (VerboseCheck())
    {
        printf("VerboseCheck() is true | verbose == true \n");
    }
    else
    {
        printf("VerboseCheck() is false | verbose != false \n");
    }
    printf("VALUE FOR NumSets: %d \n", (int)pow(2, s));
    
    // output cache hit and miss statistics
    // print_summary(hit_count, miss_count, eviction_count);
    
    // assignment done. life is good!
    return 0;
}
