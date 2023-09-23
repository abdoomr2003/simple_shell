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
	int interactive, num_loop = 1, result, btngan = 0;
	char *command = NULL, *cmd, *av[50] ;
	(void)argc;
	interactive = isatty(0);
	while (num_loop)
	{
		if (interactive)
		display_prompt();
		command = (interactive) ? read_command() : non_inter_read_command();
		if (command == NULL)
		{
			if (interactive)
			{
				write(STDOUT_FILENO, "\n", 1);
				break;
			}
			if (_strcmp(command, "exit") == 0)
			{
				free(command);
				handle_exit();
			}
		}
		if (_strcmp(command, "env") == 0)
		{
			handle_env();
			free(command);
			continue;
		}
		else
		{
			cmd = strtok(command, " \n");
			av[btngan++] = cmd;
			while(cmd != NULL)
			{
				for (;btngan < 50; btngan++)
				{
					cmd = strtok(NULL, " \n");
                    if (cmd == NULL)
                    {
                        av[btngan] = NULL;
                        break;
                    }
                    av[btngan] = cmd;
				}
				result = execute_command(av, num_loop, argv[0]);
				if (result == -1)
					perror("fork");
			}
		}
		free(command);
		num_loop++;
	}
	free(command);
	return (0);
}
