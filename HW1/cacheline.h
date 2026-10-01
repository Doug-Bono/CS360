#ifndef CACHELINE_H
#define CACHELINE_H

#include <getopt.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <errno.h>
#include <stdbool.h>

typedef struct
{
    bool valid;
    size_t tag;
    unsigned int usageCount;
} Cacheline;


// Creates the cache. NumSets = value of 2^s, E = associativity (number of lines per set).
Cacheline** CreateCache(int NumSets, int E);

#endif