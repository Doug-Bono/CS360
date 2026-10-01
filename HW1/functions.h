#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "cacheline.h"

extern int s, E, b;
extern bool verbose;
extern Cacheline** Cache;
extern int hitCount, missCount, replaceCount;
extern size_t accessCount;

void print_summary(int hits, int misses, int evictions);

void print_usage(char* argv[]);

bool VerboseCheck();

/*
 * Reads the trace file
*/
void ReadTrace(FILE* traceInput, char* line);

/*
 * Used in ReadTrace(), input is a memory address. decides if the access was a hit, miss or miss eviction
 * Needs to update cache state and global counters and return what happened to ReadTrace() so that it
 *  can print the verbose output.
*/
int AccessCache(size_t tgtAddress, Cacheline** tgtCache);

void ParseAddress(size_t tgtAddress, size_t* setIndex, size_t* tag);

#endif