#include "aishell.h"
/**
 * reverse - Reverse a character array.
 * @str: The character array to be reversed.
 * @length: The length of the character array.
 */
void reverse(char str[], int length)
{
	int start = 0;
	int end = length - 1;

	while (start < end)
	{
		char temp = str[start];

		str[start] = str[end];
		str[end] = temp;
		start++;
		end--;
	}
}
/**
 * _itoa - Convert an integer to a string.
 * @num: The integer to be converted.
 *
 * Return: A pointer to a dynamically allocated string containing the
 *         string representation of the integer.
 */
char *_itoa(int num)
{
	char *str = (char *)malloc(20 * sizeof(char));
	int rem;
	int i = 0;

	if (num == 0)
	{
		str[i++] = '0';
		str[i] = '\0';
		return (str);
	}
	while (num != 0)
	{
		rem = num % 10;
		str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
		num = num / 10;
	}
	str[i] = '\0';
	reverse(str, i);
	return (str);
}
/**
 * get_environment_variable - Retrieve the value of an environment variable.
 * @path_name: The name of the environment variable to retrieve.
 *
 * Return: A pointer to the value of the environment variable if found.
 *	or NULL if the variable is not found or if the input is invalid.
 */
char *get_environment_variable(char *path_name)
{
	int num, cmp;
	char *value_of_environment;

	if (path_name == NULL || environ == NULL)
		return (NULL);
	for (num = 0; environ[num] != NULL; num++)
	{
		cmp = _strncmp(path_name, environ[num], _strlen(path_name));
		if (cmp == 0 && environ[num][strlen(path_name)] == '=')
		{
			value_of_environment = (environ[num] + (strlen(path_name) + 1));
			return (value_of_environment);
		}
	}

	return (NULL);
}
/**
 * _strncmp - Compare two strings up to a maximum number of characters.
 * @s1: The first string to compare.
 * @s2: The second string to compare.
 * @n: The maximum number of characters to compare.
 *
 * Return: 0 if the strings are equal up to the first 'n' characters,
 * else, the difference between the ASCII values of the differing characters.
*/
int _strncmp(const char *s1, const char *s2, size_t n)
{
	while (n > 0 && *s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
		n--;
	}
	if (n == 0)
		return (0);
	else
		return (*(unsigned char *)s1 - *(unsigned char *)s2);
}
/**
 * my_strtok - Tokenize a string using a specified delimiter.
 * @str: The input string to be tokenized.
 * @delim: The delimiter used for tokenization.
 *
 * Return: The next token in the input str or NULL if there are no more tokens.
 */
char *my_strtok(char *str, const char *delim)
{

	static char *token_ptr;
	char *token_start;

	/* If str is provided, update the static pointer */
	if (str)
		token_ptr = str;

	/* If the pointer is NULL, return NULL (no more tokens) */
	if (!token_ptr)
		return (NULL);

	token_ptr = NULL;  /* Keeps track of the last token */
	token_start = str;

	token_ptr = NULL;
	if (!str)
		str = token_ptr;
	while (*token_ptr && strchr(delim, *token_ptr))
		token_ptr++;
	if (*token_ptr == '\0')
		return (NULL);
	token_start = token_ptr;
	while (*token_ptr && !strchr(delim, *token_ptr))
		token_ptr++;
	if (*token_ptr != '\0')
	{
		*token_ptr = '\0';
		token_ptr++;
	if (*str != '\0')
	{
		*str = '\0';
		str++;
	}
	return (token_start);
	}
	return (NULL);
}
