#include "tree.h"

// Constructor:
TREE* CreateTree()
{
    TREE* newTree;
    newTree->mRoot = CreateNode("/", "D"); // Creates root of the tree.

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

// Destructor:
void FreeTree(NODE *curTree)
{
    NODE *curNode = curTree->mChild;

    while(curNode != NULL)
    {
        NODE *nextNode = curNode->mSibling;
        FreeTree(curNode);
        curNode = nextNode;
    }

    free(curTree);
}

//Methods:

/// @brief Method that navigates the tree and compares the name of the nodes to that of the new node's name.
/// @param treeRoot Tree that we are navigating.
/// @param tgtName Name of the node that we are trying to add.
/// @return Returns the node with the same name as the node we are trying to add.
NODE *FindNode(NODE *treeRoot, char *tgtName)
{
    NODE *curNode = treeRoot->mChild;

    while(curNode != NULL)
    {
        if(strcmp(curNode->mChild, tgtName) == 0)
        {
            return curNode;
        }

        curNode = curNode->mSibling;
    }

    return NULL;
}

/// @brief Inserts a node into the tree. ChildPtr points to the oldest child, Siblingptr points to the oldest sibling.
/// @param curTree Tree that we are trying to insert the node into.
/// @param newNode Node that we are trying to insert.
void InsertNode(TREE *curTree, NODE* newNode)
{
    // NOT DONE ********************8
    if (curTree->mRoot == NULL) // If tree is empty, set the new node as the root.
    {
        SetRoot(curTree, newNode);
    }
}