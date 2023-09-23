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
int execute_command(char *command[], int num_loop, char *argv)
{
	pid_t child_pid;
	int child_exit = 0, status;
	char *full_path;

	full_path = find_path(command[0]);
	if (full_path == NULL)
	{
		handle_exist_error(num_loop, command[0], argv);
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
		if (execve(full_path, command, NULL) == -1)
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
