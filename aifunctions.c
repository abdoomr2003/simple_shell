#include "aishell.h"
/**
 * display_prompt - function to display "AIprompt$ ".
*/
void display_prompt(void)
{
	write(STDOUT_FILENO, PROMPT, strlen(PROMPT));
}
/**
 * read_command - read input from enteractive
 * Return: line ia a command what user write
*/
char *read_command(void)
{
	char *line = NULL;
	size_t len = 0;

	ssize_t read = getline(&line, &len, stdin);

	if (read == -1)
	{
		free(line);
		return (NULL);
	}

	if (line[read - 1] == '\n')
	{
		line[read - 1] = '\0';
	}
	return (line);
}
/**
 * non_inter_read_command - read from non-enteractive
 * Return: line ia a command what input
*/
char *non_inter_read_command(void)
{
	char *line = NULL;
	size_t len = 0;

	ssize_t read = getline(&line, &len, stdin);

	if (read == -1)
	{
		free(line);
		return (NULL);
	}

	if (line[read - 1] == '\n')
	{
		line[read - 1] = '\0';
	}
	return (line);
}
/**
 * execute_command - check and Execute a command.
 * @command: A ptr to a char str represent the command to execute.
 * @num_loop: An int represent the loop number.
 * @argv: A pointer to a character string representing the name of the program.
 *
 * Return: The exit status of the executed command.
 */
int execute_command(char *command, int num_loop, char *argv)
{
	pid_t child_pid;
	int child_exit = 0, status;
	char *full_path;
	char *exec_args[2];

	full_path = find_path(command);
	if (full_path == NULL)
	{
		handle_exist_error(num_loop, command, argv);
		free(full_path);
		return (127);
	} child_pid = fork();
	if (child_pid == -1)
	{
		perror("fork");
		free(full_path);
		_exit(-1);
	} else if (child_pid == 0)
	{
		exec_args[0] = full_path;
		exec_args[1] = NULL;
		if (execve(full_path, exec_args, NULL) == -1)
		{
			perror("execve");
			free(full_path);
			_exit(127);
		}
	} else if (child_pid > 0)
	{
		if (waitpid(child_pid, &status, 0) == -1)
		{
			perror("waitpid");
			free(full_path);
			_exit(-1);
		} else if (WIFEXITED(status))
			child_exit = WEXITSTATUS(status);
	}
	free(full_path);
	return (child_exit);
}
/**
 *find_path - find path for command
 *@command: command that given by usr
 *
 *Return: A pointer to the full path of the command if found
 *		or NULL if not found.
*/
char *find_path(char *command)
{
	char *path_value = get_environment_variable("PATH");
	char *path_copy, *path_token, *full_path = NULL;

	if (command == NULL || path_value == NULL)
		return (NULL);
	path_copy = _strdup(path_value);
	if (path_copy == NULL)
		return (NULL);
	if (command[0] == '/' || command[0] == '.')
	{
		if (access(command, F_OK) == 0)
			return (_strdup(command));
		return (NULL);
	}
	path_token = strtok(path_copy, ":");
	if (path_token == NULL)
	{
		free(path_copy);
		return (NULL);
	}
	while (path_token != NULL)
	{
		size_t file_path_len = _strlen(path_token) + _strlen(command) + 2;

		full_path = (char *)malloc(file_path_len);
		if (full_path == NULL)
		{
			free(path_copy);
			return (NULL);
		} _strcpy(full_path, path_token);
		_strcat(full_path, "/");
		_strcat(full_path, command);
		if (access(full_path, F_OK) == 0)
		{
			free(path_copy);
			return (full_path);
		} free(full_path);
		path_token = strtok(NULL, ":");
	} free(path_copy);
	return (NULL);
}





