#include "node.h"

NODE* CreateNode(const char* newName, char newType)
{
	NODE* newNode = (NODE*)malloc(sizeof(NODE));

	strncpy(newNode->mName, newName, sizeof(newNode->mName)-1);
	newNode->mName[sizeof(newNode->mName)-1] = '\0';
	newNode->mType = newType;

	newNode->mChild= newNode->mSibling = newNode->mParent = NULL;

	return newNode;
}

// Getters:
char* GetName (NODE* curNode)
{
	return curNode->mName;
}

char GetType (NODE* curNode)
{
	return curNode->mType;
}

NODE* GetChild(NODE* curNode)
{
	return curNode->mChild;
}

NODE* GetSibling(NODE* curNode)
{
	return curNode->mSibling;
}

NODE* GetParent(NODE* curNode)
{
	return curNode->mParent;
}

// Setters:
void SetName(NODE *curNode, char* newName)
{
	strncpy(curNode->mName, newName, sizeof(curNode->mName) -1);
	curNode->mName[sizeof(curNode->mName)-1] = '\0';
}

void SetType(NODE *curNode, char newType)
{
	curNode->mType = newType;
}

void SetChild (NODE *curNode, NODE *childPtr)
{
	curNode->mChild = childPtr;
}

void SetSibling (NODE *curNode, NODE *siblingPtr)
{
	curNode->mSibling = siblingPtr;
}

void SetParent(NODE *curNode, NODE* parentPtr)
{
	curNode->mParent = parentPtr;
}

// Destructor:
void FreeNode (NODE *curNode)
{
	if(curNode)
	{
		free(curNode->mName);
		free(curNode->mType);
		free(curNode->mChild);
		free(curNode->mSibling);
		free(curNode->mParent);
		free(curNode);
	}
}