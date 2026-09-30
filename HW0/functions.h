#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "node.h"
#include "tree.h"

extern TREE *fileSystem;
extern NODE *cwd;


// Methods:
int FindCommand(char *userCommand);

void SplitPath(char *pathName, char *dirnameOutput, char *basenameOutput);

NODE *FindNode(char *filePath);

void Mkdir(char *pathName);

void Rmdir(char *pathName);

void Cd(char *pathName);

void Ls(char *pathName);

void GetPath(NODE *tgtNode, char *pathOut);

void Pwd();

void Creat(char *pathName);

void Rm(char *pathName);

void Save(char *fileName);

void ReloadHelper();

void Reload(char *fileName);

#endif