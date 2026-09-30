#include <getopt.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <errno.h>
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

// other variables as needed


/* 
 * this function provides a standard way for your cache
 * simulator to display its final statistics (i.e., hit and miss)
 */ 
void print_summary(int hits, int misses, int evictions)
{
    printf("hits:%d misses:%d evictions:%d\n", hits, misses, evictions);
}

/*
 * print usage info
 */
void print_usage(char* argv[])
{
    printf("Usage: %s [-hv] -s <num> -E <num> -b <num> -t <file>\n", argv[0]);
    printf("Options:\n");
    printf("  -h         Print this help message.\n");
    printf("  -v         Optional verbose flag.\n");
    printf("  -s <num>   Number of set index bits.\n");
    printf("  -E <num>   Number of lines per set.\n");
    printf("  -b <num>   Number of block offset bits.\n");
    printf("  -t <file>  Trace file.\n");
    printf("\nExamples:\n");
    printf("  linux>  %s -s 4 -E 1 -b 4 -t traces/trace01.dat\n", argv[0]);
    printf("  linux>  %s -v -s 8 -E 2 -b 4 -t traces/trace01.dat\n", argv[0]);
    exit(0);
}

/*
 * starting point
 */
int main(int argc, char* argv[])
{
	// complete your simulator
    int c;
    int s = 0, E = 0, b = 0;
    int verbose = 0;
    char *traceFile = NULL;

    while ((c = getopt(arc, argv, "ab:")) != -1)
    {
        switch(c)
        {
            case 's':
                s = atoi(optarg);
                break;
            
            case 'E':
                s = atoi(optarg);
                break;

            case 'b':
                s = atoi(optarg);
                break;

            case 't':
                traceFile = optarg;
                break;

            case 'v':
                verbose = 1;
                break;
            
            case 'h':
                print_usage(argv);
                exit(0);
            
            default:
                print_usage(argv);
                exit(1);
        }
    }

    // output cache hit and miss statistics
    // print_summary(hit_count, miss_count, eviction_count);
    
    // assignment done. life is good!
    return 0;
}
