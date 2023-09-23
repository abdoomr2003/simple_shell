#ifndef AISHELL_H
#define AISHELL_H

#define PROMPT "AIprompt$ "

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <limits.h>
#include <sys/types.h>
#include <string.h>
#include <stddef.h>

/*string_functions*/
int _strcmp(char *s1, char *s2);
char *_strdup(char *str);
char *_strcat(char *dest, char *src);
int _strlen(char *s);
char *_strcpy(char *dest, char *src);
int _strcmp(char *s1, char *s2);
int _strncmp(const char *s1, const char *s2, size_t n);



/*my function*/
char *_itoa(int num);
char *_strtok(char *str, const char *delim);
char *remove_spaces(char *str);

extern char *value_of_environment;
extern char **environ;


void display_prompt(void);
char *read_command(void);
char *non_inter_read_command(void);
void handle_env(void);
void handle_exit(void);
int execute_command(char *command, int num_loop, char *argv);
int execute_path(char *full_path[], char *command);
char *find_path(char *comand);
void handle_exist_error(int num_loop, char *command, char *argv);
char *get_environment_variable(char *path_name);
char *check_current_directory(char *command);
char *search_in_path(char *command, char *path);



#endif /*AISHELL_H*/
