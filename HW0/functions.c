#include <stdio.h>
#include <stdlib.h>

char *cmd[] = {"mkdir", "rmdir", "cd", "ls", "pwd", "creat", "rm", "save", "reload", "quit"};  // fill with list of commands

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

/*
    LEFT OFF HERE. UNDERSTAND HOW SPLITPATH() WORKS. ALSO NEED TO FINISH INSERTNODE() IN TREE.C ***********************************

*/
/// @brief Splits the file path (pathname) into "dirname" and "basename". 
/// ABSOLUTE pathname = /a/b/c/d 
///     dirname = /a/b/c
///     basename = d
/// RELATIVE pathname = a/b/c/d 
///     dirname = a/b/c
///     basename = d
/// @param pathname File path designated by the user.
void SplitPath(char *pathname)
{
    char *tempPath[64]; // Use this to store the pathname and then once we determine if the pathname is absolute or relative then fill dirname
    char *dirname[64]; // Holds /a/b/c or a/b/c
    char *basename; // Holds d

    strncpy(tempPath, pathname, sizeof(pathname) -1); // Copy the pathname into a string so that we can modify it. 
    dirname[sizeof(pathname)-1] = '\0';

    char *lastSlash = strchr(pathname, '/');

    if (lastSlash == NULL)
    {
        // If statement for when the pathname is a RELATIVE PATHNAME
        // When the pathname doesn't have a / in it
        dirname[0] = '\0';
        strncpy(basename, tempPath); // If were in this statement it means we inputted something like "A" so theres no dirname so we set it to NULL. As for the basename we set it as the pathname so for here basename = "A".
    }
    else
    {
        strcpy(basename, lastSlash + 1);
        lastSlash = '\0';

        if(tempPath[0] == '\0')
        {
            strcpy(dirname, "/");
        }
        else
        {
            strcpy(dirname, tempPath);
        }
    }
}

void Mkdir(char *newPathname)
{
    // Need a way to check if the directory name is not already made
    // So, we need to traverse our tree and check if the given name already exists
    // Meaning we need to create a tree
}