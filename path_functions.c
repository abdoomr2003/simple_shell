#include "aishell.h"
/**
 * check_current_directory - Check if a command exists.
 * @command: A pointer to a character string representing the command.
 *
 * Return: If the file/command exists in the current directory,
 *			return a pointerto the same command. Otherwise, return NULL.
*/
char *check_current_directory(char *command)
{
	int exist;

	if (command == NULL)
		return (NULL);
	exist = access(command, F_OK);
	if (exist == 0)
		return (command);
	return (NULL);
}
/**
 * search_in_path - Search for a command in the directories listed in PATH.
 * @command: A pointer to a char str represent the command that search for.
 * @path: A pointer to a char str contain the PATH variable.
 *
 * Return: If the command is found in any of the directories in PATH, return
 *         a pointer to the full path of the command. else, return NULL.
 */
char *search_in_path(char *command, char *path)
{
	char *path_copy, *path_token, *file_path;
	size_t file_path_len;

	if (command == NULL || path == NULL)
		return (NULL);
	path_copy = _strdup(path);
	if (path_copy == NULL)
		return (NULL);
	path_token = _strtok(path_copy, ":");
	while (path_token != NULL)
	{
		file_path_len = _strlen(path_token) + _strlen(command) + 2;
		file_path = (char *)malloc(file_path_len);

		if (file_path == NULL)
		{
			free(path_copy);
			return (NULL);
		}

		_strcpy(file_path, path_token);
		_strcat(file_path, "/");
		_strcat(file_path, command);

		if (access(file_path, F_OK) == 0)
		{
			free(path_copy);
			return (file_path);
		}

		path_token = _strtok(NULL, ":");
		free(file_path);
	}
	free(path_copy);
	return (NULL);
}

