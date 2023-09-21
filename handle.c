#include "aishell.h"
/**
 * handle_exit - to handle exit.
*/
void handle_exit(void)
{
	exit(EXIT_SUCCESS);
}
/**
 * handle_env - to handle enviromint.
*/
void handle_env(void)
{

	char **env = environ;

	while (*env)
	{
		write(STDOUT_FILENO, *env, strlen(*env));
		write(STDOUT_FILENO, "\n", 1);
		env++;
	}
}
/**
 * handle_exist_error - Handle and report a command not found error.
 * @num_loop: An int represent the loop number.
 * @command: A ptr to a char str represent the command.
 * @argv: A ptr to a char str represent the program name.
*/
void handle_exist_error(int num_loop, char *command, char *argv)
{
	char *ch_loop_num;

	write(1, argv, _strlen(argv));
	write(1, ": ", 2);
	ch_loop_num = _itoa(num_loop);
	write(1, ch_loop_num, _strlen(ch_loop_num));
	write(1, ": ", 2);
	write(1, command, _strlen(command));
	write(1, ": not found", _strlen(": not found"));
	write(1, "\n", _strlen("\n"));
	free(ch_loop_num);
}

