#ifndef TREE_H
#define TREE_H

#include "node.h"

typedef struct tree {
    NODE* mRoot;
} TREE;

// Constructor:
TREE* CreateTree();

// Getter:
NODE* GetRoot(TREE* curTree);

// Setter:
void SetRoot(TREE *newTree, NODE *newRoot);

// Destructor Helper:
void FreeSubtree(NODE *rootNode);

// Destructor: 
void FreeTree(TREE *curTree);

// Methods:
NODE *FindChild(NODE *parentNode, char *tgtName);

void InsertNode(NODE *parentNode, NODE *newNode);

void RemoveNode(NODE *tgtNode);

#endif