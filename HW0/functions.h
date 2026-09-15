#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "node.h"
#include "tree.h"

// Children of the same parent node = sibling node.

char *cmd[] = {"mkdir", "rmdir", "cd", "ls", "pwd", "creat", "rm", "save", "reload", "quit"};  // fill with list of commands

void SplitPath(char *filePath);


#endif