#include "aishell.h"
/**
 * main - Entry point for the aishell program
 * @argc: The number of command-line arguments
 * @argv: An array of command-line argument strings
 *
 * Return: Always 0
 */
int main(int argc, char *argv[])
{
	int interactive, num_loop = 1, result, cmp;
	char *command = NULL;
	(void)argc;
	interactive = isatty(0);
	while (1)
	{
		if (interactive)
		display_prompt();
		command = (interactive) ? read_command() : non_inter_read_command();
		if (command == NULL)
		{
			if (interactive)
			write(STDOUT_FILENO, "\n", 1);
			break;
		} cmp = _strcmp(command, "exit");
			if (_strcmp(command, "exit") == 0)
			{
				free(command);
				handle_exit();
			} cmp = _strcmp(command, "env");
		if (_strcmp(command, "env") == 0)
		{
			handle_env();
			free(command);
			continue;
		} cmp = _strcmp(command, "clear");
			if (cmp == 0)
			{
				free(command);
				write(STDOUT_FILENO, "\033[H\033[J", 6);
				continue;
			} else
		{
			result = execute_command(command, num_loop, argv[0]);
			if (result == -1)
				perror("fork");
		} free(command);
			num_loop++;
			} free(command);
			return (0);
}
