#include "node.h"
#include "tree.h"
#include "functions.h"

TREE *fileSystem;
NODE *cwd;
NODE *root; 
// other global variables

int main() 
{
	char pathName[64] = "/A/B/C/D";
	char dirnameOutput[64];
	char basenameOutput[64];

	SplitPath(pathName, dirnameOutput, basenameOutput);

	printf("Path: %s\n", pathName);
	printf("Dirname: %s\n", dirnameOutput);
	printf("Basename: %s\n", basenameOutput);

	return 0;
}

