/* works just like the which command */
#include "main.h"

/**
 * get_location - finds the location of a given command in the system's PATH
 * @command: the command to locate
 *
 * Return: full path if found, else NULL.
*/

char *get_location(char *command)
{
char *path, *path_copy, *path_token, *file_path;
int command_len, directory_len;
struct stat buffer;

path = getenv("PATH");

if (path)
{
/* Duplicate the path string - free up memory for strdup() */
path_copy = strdup(path);
/* Get the length of the command that was passed */
command_len = strlen(command);

/* Split the path into tokens for accessing available directories */
path_token = strtok(path_copy, ":");

while (path_token != NULL)
{
/* get the length of the directory */
directory_len = strlen(path_token);
/* allocate memory for storing the command name and directory name */
file_path = malloc(command_len + directory_len + 2);
/* Concatenate directory path with command for command's path */
strcpy(file_path, path_token);
strcat(file_path, "/");
strcat(file_path, command);
strcat(file_path, "\0");

/* Test file path existence. Return if exists, otherwise try next directory */
if (stat(file_path, &buffer) == 0)
{
/* return 0 if file_path is valid */
free(path_copy);

return (file_path);
}
else
{
/* free file_path memory so we can check another path */
free(file_path);
path_token = strtok(NULL, ":");
}
}

/* if file_path doesn't exist return NULL, but free path_copy */
free(path_copy);

/* see if the command itself is a file_path that exists */
if (stat(command, &buffer) == 0)
{
return (command);
}

return (NULL);
}

return (NULL);
}
