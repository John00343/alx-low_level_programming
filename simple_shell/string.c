#include "shell.h"

/**
 * _strlen - Indicate string length
 * @s: String to be checked
 *
 * Return: Length of s
 */
int _strlen(char *s)
{
	int i = 0;

	if (!s)
		return (0);

	while (*s++)
		i++;
	return (i);
}

/**
 * _strcmp - Executes lexicogarphic comparison of two strings.
 * @s1: strang 1
 * @s2: strang 2
 *
 * Return: -ve if s1 < s2, +ve if s1 > s2, 0. if s1 == s2
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with - If needle starts with haystack
 * @haystack: string being search
 * @needle: substring found
 *
 * Return: char's address of haystack else NULL
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - Joining two strings
 * @dest: the dest buffer
 * @src: source buffer
 *
 * Return: A pointer to dest buffer
 */
char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}
