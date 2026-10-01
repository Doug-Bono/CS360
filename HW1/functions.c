#include "functions.h"

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

void PrintAccessResult(int accessResult) // ADD THIS TO HEADER FILE AND REPLACE print_result() WITH THIS FUNCTION INSTEAD
{
    if (accessResult == 0)
    {
        printf(" hit\n");
    }
    else if (accessResult == 1)
    {
        printf(" miss\n");
    }
    else
    {
        printf(" miss eviction\n");
    }
}
bool VerboseCheck()
{
    return verbose == true;
}

/*
 * Replays trace REWRITE THIS ****************************
*/
void ReadTrace(FILE* traceInput, char* lineBuf)
{
    while (fgets(lineBuf, sizeof(lineBuf), traceInput) != NULL)
    {
        if (lineBuf[0] == 'I')
        {
            continue; // Ignores the instruction line
        }

        char operation; // Denotes type of memory access
        size_t address; // 64-bit hexadecimal memory address
        int size; // number of bytes accessed by the operation

        if (VerboseCheck())
        {
            printf("%c %zu, %d", operation, address, size);
        }

        if (operation == 'L' || operation == 'S') // L = data load, S = data store
        {
            // access_result r = AccessCache((uint64_t)addr);
            int accessResult = AccessCache(address, Cache);

            if (VerboseCheck())
            {
                // print_result(r);
                // printf("\n");
                PrintAccessResult(accessResult);
            }
        }
        
        else if (operation == 'M') // M = data modify (i.e. data load then store)
        {
            // access_result r1 = AccessCache((uint64_t)addr);
            // access_result r2 = AccessCache((uint64_t)addr);
            int accessResult1 = AccessCache(address, Cache);
            int accessResult2 = AccessCache(address, Cache);

            if (VerboseCheck())
            {
                // print_result(r1);
                // print_result(r2);
                // printf("\n");
                PrintAccessResult(accessResult1);
                PrintAccessResult(accessResult2);
            }
        } 
    }
}

/*
    LEFT OFF HERE, ALMOST FINISHED IMPLEMENTING AccessCache() NEED TO EDIT THE COMMENTS, REWRITE THE CODE FOR THE IF STATEMENT if (victim == -1)
        ADDED THE FUNCTION PrintAccessResult() THAT PRINTS IF WE HIT, MISS, OR MISS EVICTION.
*/

// 0 = Hit, 1 = Miss, 2 = Miss_Eviction
int AccessCache(size_t tgtAddress, Cacheline** tgtCache)
{
    // size_t setIndex = (tgtAddress >> b) % (1 << s); // Shift tgtAddress RIGHT by b bits, discards rightmost btis (offset bits). Then shift 1 LEFT by the value of s. Modding the address by (1 << s) gives the remainder after dividing by (1 << s), which gives the value of the lowest s bits.
    // size_t tag = tgtAddress >> (s + b); // Shift tgtAddress RIGHT by s + b bits which discards everything but the tag.
    
    // IF IT DOESNT WORK, UNCOMMENT THE TOP 2 LINES AND COMMENT THESE TWO LINES BELOW
    size_t setIndex, tag;
    ParseAddress(tgtAddress, &setIndex, &tag);
    
    Cacheline* tgtLines = tgtCache[setIndex]; // setIndex points to the set the address maps to, tgtLines points to the E lines of that one set. REVISE THIS IF NEEDED*******
   
    accessCount++; // Every time we access, increment. 
   
    int victim = -1; // variable for the index of the line within the set that will be overwritten to make room for the new block.
                    // tgtLines[victim] is the line that gets new data.
    int accessResult;

    for (int i = 0; i < E; i++)
    {
        if (tgtLines[i].valid == true)
        {
            if (tgtLines[i].tag == tag) // Hit: Line in this set with a matching tag was found
            {
                hitCount++;
                tgtLines[i].usageCount = accessCount;

                return accessResult = 0; // If we got a hit, we return 0 which indicates a hit. No need to keep looping
            }
        }
        else if (tgtLines[i].valid == false) // First empty line. Remember it so that we can set this empty line as the victim and keep scanning
        {
            // Find a place to put the new block, first looking for an empty line.
            // If theres an invalid line, we fill it. No eviction needed.
            victim = i; // Set the victim (line we want to overwrite) as the first empty line we found.
        }
    }

    missCount++; // If we reached here, it means we had a miss so count the miss.
    accessResult = 1; // Set the result as 1 which indicates a miss.

    // No empty line was found so evict the least recently used (smallest timestamp)
    if (victim == -1) // If victim is still -1, it means that every line in the set is occupied so we have to evict someone
                      // If victim already holds a real index (victim = i), we skip the whole block b/c theres no need to evict. 
    {
        // If we entered this statment, we know the set is full so we need to find the LRU line. 
        int lruIndex = 0; // Variable is set to the first line (oldest line) in the set. Gets compared against all other lines to find the LRU.

        for (int i = 1; i < E; i++)
        {
            if (tgtLines[i].usageCount < tgtLines[lruIndex].usageCount)
            {
                lruIndex = i; // Found an older one, so it becomes the candidate
            }
        }

        victim = lruIndex; // Set the victim to the LRU line we found. 
        replaceCount++;
        accessResult = 2; // Set result to 2 which indicates a miss with eviction.
    }

    // 4. Install the new block into the chosen line
    tgtLines[victim].valid = true;
    tgtLines[victim].tag = tag;
    tgtLines[victim].usageCount = accessCount;

    return accessResult;
}

void ParseAddress(size_t tgtAddress, size_t* setIndex, size_t* tag)
{
    *setIndex = (tgtAddress >> b) % (1 << s); // Shift tgtAddress RIGHT by b bits, discards rightmost btis (offset bits). Then shift 1 LEFT by the value of s. Modding the address by (1 << s) gives the remainder after dividing by (1 << s), which gives the value of the lowest s bits.
    *tag = tgtAddress >> (s + b); // Shift tgtAddress RIGHT by s + b bits which discards everything but the tag.
}