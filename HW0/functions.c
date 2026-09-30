#include "functions.h"

char *cmd[] = {"mkdir", "rmdir", "cd", "ls", "pwd", "creat", "rm", "save", "reload", "quit", 0};  // fill with list of commands

int FindCommand(char *userCommand)
{
    int i = 0;
    while (cmd[i])
    {
        if (strcmp(userCommand, cmd[i]) == 0)
        {
            return i;
        }
        i++;
    }
    return -1;
}

/// @brief SplitPath() takes a pathName which will get split into two strings dirnameOutput which will store the directory name
///         and basenameOutput which will store the basename of the file path. Generative AI <Claude> was used when I wrote the lower
///         portion of this function and I have placed my AI acknowledgement as a comment at where Claude was used.
/// if (tempPath[0] == '/')
    {
        curNode = GetRoot(fileSystem);
    }
/// @param pathName File path inputted by the user.
/// @param dirnameOutput Used to return the dirname of the file path.
/// @param basenameOutput Used to return the basename of the file path.
void SplitPath(char *pathName, char *dirnameOutput, char *basenameOutput)
{
    char tempPath[64]; 
    strcpy(tempPath, pathName);

    char *lastSlash = strrchr(tempPath, '/'); // Referenced code from: https://www.ibm.com/docs/sv/i/7.4.0?topic=s-locate-last-occurrence-character-in-string-strrchr
                                              // I was trying to find how to find the last particular value in a string and used this websites code.

    if (lastSlash == NULL) // If the path is just a file or directory, dirname is an empty string and basename would be the filepath.
    {
        dirnameOutput[0] = '\0'; // Makes dirnameOutput an empty string.
        strcpy(basenameOutput, tempPath);
    }
    else // If input is a file path. Set dirname to the path up to last slash. Set basename to the value next to last slash. 
    {
        strcpy(basenameOutput, lastSlash + 1);

        /*
            AI Acknowledgment:
                This lower portion of the SplitPath() function was completed using AI tool <Claude>. Claude originally suggested
                doing a lastSlash == tempPath check for the special case of / being the first value since that would be checking if
                the address equals the buffer. Since Claude already provided me with how to cut a string at a specific spot, I used my own
                if-else statement but used Claude's line which was: "strcpy(dirnameOutput, "/");".

            Prompts that were used:
                "In C, how can I split pathName at where lastSlash is pointing to into two strings."
                "If the very first value of pathName is a slash, how can I store the slash in dirnameOutput instead of it being an empty string."
        */
        *lastSlash = '\0'; // Sets the value of that last slash is pointing to to empty.

        if(tempPath[0] == '\0') // Special case when slash is the first character.
        {
            strcpy(dirnameOutput, "/");
        }
        else
        {
            strcpy(dirnameOutput, tempPath);
        }
    }
}

NODE *FindNode(char *filePath)
{
    char tempPath[64];
    strcpy(tempPath, filePath);

    NODE *curNode;

    if (tempPath[0] == '/')
    {
        curNode = GetRoot(fileSystem);
    }
    else
    {
        curNode = cwd;
    }

    char *token = strtok(tempPath, "/");

    while (token != NULL)
    {
        if (strcmp(token, "..") == 0)
        {
            curNode = GetParent(curNode);
        }
        else
        {
            curNode = FindChild(curNode, token);
            
            if (curNode == NULL)
            {
                break;
            }
        }
        token = strtok(NULL, "/");
    }

    return curNode;
}

// mkdir pathname: make a new directory for a given pathname
void Mkdir(char *pathName)
{
    char dirName[64], baseName[64];
    SplitPath(pathName, dirName, baseName);

    NODE *curParent = FindNode(dirName);

    if (curParent == NULL || GetType(curParent) != 'D')
    {
        printf("No DIR or file found: %s\n", pathName);
        return;
    }

    if (FindChild(curParent, baseName) != NULL)
    {
        printf("DIR %s already exists!\n", pathName);
        return;
    }

    NODE *newNode = CreateNode(baseName, 'D');
    InsertNode(curParent, newNode);
}

// rmdir pathname: Remove the directory if it is empty.
void Rmdir(char *pathName)
{
    NODE *tgtNode = FindNode(pathName);

    if (tgtNode == NULL || GetType(tgtNode) != 'D')
    {
        printf("DIR %s doesn't exist. Cannot be removed\n", pathName);
        return;
    }

    if (GetChild(tgtNode) != NULL)
    {
        printf("Cannot remove DIR %s (not empty!)\n", pathName);
        return;
    }

    RemoveNode(tgtNode);
    FreeNode(tgtNode);
}

// cd [pathname]: Change CWD to pathname, or to / if no pathname specified.
void Cd(char *pathName)
{
    if (pathName[0] == '\0')
    {
        cwd = GetRoot(fileSystem);
        return;
    }

    NODE *tgtNode = FindNode(pathName);

    if (tgtNode == NULL || GetType(tgtNode) != 'D')
    {
        printf("No such file or directory: %s\n", pathName);
        return;
    }

    cwd = tgtNode;
}
// ls [pathname]: List the directory contents of pathname or CWD (if pathname not specified).
void Ls(char *pathName)
{
    NODE *tgtNode;

    if (pathName[0] == '\0')
    {
        tgtNode = cwd;
    }
    else
    {
        tgtNode = FindNode(pathName);
    }

    if (tgtNode == NULL)
    {
        printf("No such file or directory: %s\n", pathName);
        return;
    }

    NODE *curNode = GetChild(tgtNode);

    while(curNode != NULL)
    {
        printf("%c %s\n", GetType(curNode), GetName(curNode));
        curNode = GetSibling(curNode);
    }
}

void GetPath(NODE *tgtNode, char *pathOut)
{
    char completePath[64];

    if (tgtNode == GetParent(tgtNode))
    {
        strcpy(pathOut, "/");
        return;
    }

    GetPath(GetParent(tgtNode), completePath);

    strcpy(pathOut, completePath);

    if (strcmp(completePath, "/") != 0)
    {
        strcat(pathOut, "/");
    }

    strcat(pathOut, GetName(tgtNode));
}

// Print the (absolute) pathname of CWD.
void Pwd()
{
    char pathName[64];
    GetPath(cwd, pathName);
    printf("%s\n", pathName);
}

// creat pathname: Create a new FILE node.
void Creat(char *pathName)
{
    char dirName[64], baseName[64];
    SplitPath(pathName, dirName, baseName);

    NODE *curParent = FindNode(dirName);

    if (curParent == NULL || GetType(curParent) != 'D')
    {
        printf("No DIR or file found: %s\n", pathName);
        return;
    }

    if (FindChild(curParent, baseName) != NULL)
    {
        printf("%s already exists!\n", pathName);
        return;
    }

    NODE *newNode = CreateNode(baseName, 'F');
    InsertNode(curParent, newNode);
}

// rm pathname: Remove the FILE node specified by pathname
void Rm(char *pathName)
{
    NODE *tgtNode = FindNode(pathName);
    
    if (tgtNode == NULL)
    {
        printf("File %s does not exist!\n", pathName);
        return;
    }

    if (GetType(tgtNode) != 'F')
    {
        printf("Cannot remove %s (not a FILE)!\n", pathName);
        return;
    }

    RemoveNode(tgtNode);
    FreeNode(tgtNode);
}


/*
    LEFT OFF HERE *****************************************************************************************************
    CHECK DOUG2 FOR DETAILS ******************************************************

*/
void SaveHelper(NODE *curNode, FILE *fp)
{

}

// save filename: Save the current filesystem tree in the file filename.
void Save(char *fileName)
{
    FILE *fp = fopen(fileName, "w+");
    SaveHelper(GetRoot(fileSystem, fp));
    fclose(fp);
}

void ReloadHelper()
{
    NODE *tempNode = GetChild(GetRoot(fileSystem));

    while (tempNode != NULL)
    {
        NODE *nextNode = GetSibling(tempNode);
        FreeSubtree(tempNode);
        tempNode = nextNode;
    }

    SetChild(GetRoot(fileSystem), NULL);
    cwd = GetRoot(fileSystem);
}

// reload filename: Reinitialize the filesystem tree from the file "filename"
void Reload(char *fileName)
{
    FILE *tgtFile = fopen(fileName, "r");
    if (tgtFile == NULL)
    {
        printf("Could not open %s!\n", fileName);
        return;
    }

    ReloadHelper();
}