#ifndef NODE_H
#define NODE_H

#include <stdio.h>            
#include <stdlib.h>            
// additional headers as needed

typedef struct node {
	char  mName[64];       // node's name string
	char  mType;			  // denotes node type: D for directories, F for files
	struct node *mChild, *mSibling, *mParent;
	// other fields if needed
} NODE;

// Constructor:
NODE* CreateNode(const char* newName, char newType);

// Getters:
char* GetName (NODE* node);
char GetType (NODE* node);
NODE* GetChild(NODE* node);
NODE* GetSibling(NODE* node);
NODE* GetParent(NODE* node);

// Setters:
void SetName (NODE *node, char *newName);
void SetType (NODE *node, char newType);
void SetChild (NODE *node, NODE *childPtr);
void SetSibling (NODE *node, NODE *siblingPtr);
void SetParent (NODE *node, NODE *parentPtr);

// Destructor:
void FreeNode (NODE *node);

#endif