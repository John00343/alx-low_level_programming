#include "shell.h"

/**
 * interactive - Checks if the shell is in Interactive mode
 * @info: struct address
 *
 * Return (1) if true
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - checks for delimiter character
 * @a: the char to check
 * @delim: the delimiter string
 *
 * Return: 1 if true, 0 if false
 */
int is_delim(char a, char *delim)
{
	while (*delim) {
	if (*delim++ == a)
		return (1);
	}
	return (0);
}

/**
 * _isalpha - checks for alphabetic character
 * @c: The character to input
 *
 * Return: (1) if a is alphabet
 */
int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - converts a string to integer
 * @t: the string to convert
 *
 * Return: 0 if no numbers in string, otherwise converted number
 */
int _atoi(char *t)
{
	int i, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (i = 0; t[i] != '\0' && flag != 2; i++) {
		if (t[i] == '-')
			sign *= -1;

		if (t[i] >= '0' && t[i] <= '9') {
			flag = 1;
			result *= 10;
			result += (t[i] - '0');
		}
		else if (flag == 1) {
			flag = 2;
		}
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}

