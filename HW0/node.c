#include "node.h"

NODE* CreateNode(const char* newName, char newType)
{
	NODE* newNode = (NODE*)malloc(sizeof(NODE));

	SetName(newNode, newName);
	SetType(newNode, newType);
	SetChild(newNode, NULL);
	SetSibling(newNode, NULL);
	SetParent(newNode, NULL);

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
void SetName(NODE *curNode, const char* newName)
{
	strcpy(curNode->mName, newName);
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
		free(curNode);
	}
}