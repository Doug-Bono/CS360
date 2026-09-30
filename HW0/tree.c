#include "tree.h"

// Constructor:
TREE* CreateTree()
{
    TREE *newTree = (TREE*)malloc(sizeof(TREE));
    NODE *newRoot = CreateNode("/", 'D'); // Creates root of the tree.

    SetParent(newRoot, newRoot);
    SetSibling(newRoot, newRoot);

    SetRoot(newTree, newRoot);

    return newTree;
}

// Getter:
NODE* GetRoot(TREE* curTree)
{
    return curTree->mRoot;
}

// Setter:
void SetRoot(TREE *newTree, NODE *newRoot)
{
    newTree->mRoot = newRoot;
}

// Destructor Helper:
void FreeSubtree(NODE *tgtNode)
{
    NODE *tempNode = GetChild(tgtNode);

    while (tempNode != NULL)
    {
        NODE *nextNode = GetSibling(tempNode);
        FreeSubtree(tempNode);
        tempNode = nextNode;
    }
    FreeNode(tgtNode);
}

// Destructor:
void FreeTree(TREE *curTree)
{
    FreeSubtree(GetRoot(curTree));
    free(curTree);
}

//Methods:

NODE *FindChild(NODE *parentNode, char *tgtName)
{
    NODE *curNode = GetChild(parentNode);

    while(curNode != NULL)
    {
        if(strcmp(GetName(curNode), tgtName) == 0)
        {
            return curNode;
        }

        curNode = GetSibling(curNode); 
    }

    return NULL;
}

/// @brief Inserts a new node into the tree. Pass in a pointer to a parent node and pointer to the node we are inserting. Inserts the new node as 
//          the parent's child node if the parent does not have any children. If the parent has children, navigate through the chain of sibling nodes
//          and insert the new node at the very end of the chain.
/// @param parentNode The parent node of the new node we are trying to insert.
/// @param newNode New node we are trying to insert.
void InsertNode(NODE *parentNode, NODE *newNode)
{
    SetParent(newNode, parentNode); // Set the new node's parent ptr to point to parentNode
    SetSibling(newNode, NULL);

    if (GetChild(parentNode) == NULL) // If parent has no children, newNode becomes parent's child node
    {
        SetChild(parentNode, newNode);
    }
    else // If parent has a children node, append newNode to the end of the sibling chain
    {
        NODE* tempNode = GetChild(parentNode);

        while (GetSibling(tempNode) != NULL) // Traversal
        {
            tempNode = GetSibling(tempNode);
        }

        SetSibling(tempNode, newNode);
    }
}

void RemoveNode(NODE *tgtNode)
{
    NODE *parentNode = GetParent(tgtNode);

    if (GetChild(parentNode) != tgtNode)
    {
        NODE *curNode = GetChild(parentNode);

        while (GetSibling(curNode) != tgtNode)
        {
            curNode = GetSibling(curNode);
        }
        SetSibling(curNode, GetSibling(tgtNode));
    }
    else
    {
        SetChild(parentNode, GetSibling(tgtNode));
    }
}