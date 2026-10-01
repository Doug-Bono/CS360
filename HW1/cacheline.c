#include "cacheline.h"

Cacheline** CreateCache(int NumSets, int E)
{
    Cacheline** Newcache = malloc(NumSets * sizeof(Cacheline*));
    
    for (unsigned i = 0; i < NumSets; i++)
    {
        Newcache[i] = malloc(E * sizeof(Cacheline)); // E is the number of lines per set

        for (unsigned j = 0; j < E; j++)
        {
            Newcache[i][j].valid = false;
            Newcache[i][j].tag = 0;
            Newcache[i][j].usageCount = 0;
        }
    }

    return Newcache;
    // Newcache[set][line].
    // in each [set] we have E # of [line]
    // So if we want to access set #2's 6th line, we would use Newcache[2][5]. I THINK *********
}
