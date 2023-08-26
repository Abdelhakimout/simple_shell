#include "rakia_hakim.h"

/**
 * _strcat - concatenate two strings
 * @destination: string to be appended to
 * @source: string to append
 * Return: concatenated string
 */
char *_strcat(char *destination, char *source)
{
	int dest_len = 0;
	int src_len = 0;
	int total_len = 0;
	int j = 0;

	/* Calculate the total length of both strings for memory reallocation */
	while (destination[dest_len] != '\0')
	{
		dest_len++;
		total_len++;
	}
	while (source[src_len] != '\0')
	{
		src_len++;
		total_len++;
	}

	/* Reallocate memory because the destination was malloced outside of the function */
	destination = _realloc(destination, dest_len, sizeof(char) * (total_len + 1));

	while (source[j] != '\0')
	{
		destination[dest_len] = source[j];
		dest_len++;
		j++;
	}
	destination[dest_len] = '\0';

	return (destination);
}


/**
 * _strcmp - compare two strings
 * @str1: string 1
 * @str2: string 2
 * Return: int that tells num spaces in between,
 * 0 if exactly the same string
 */

int _strcmp(char *str1, char *str2)
{
	int i = 0;

	while (*(str1 + i) == *(str2 + i) && *(str1 + i))
		i++;

	if (*(str2 + i))
		return (*(str1 + i) - *(str2 + i));
	else
		return (0);
}

/**
 * _strcpy - copies the string pointed to by source,
 * including the terminating null byte (\0),
 * to the buffer pointed to by destination
 * @destination: copy source to this buffer
 * @source: this is the source to copy
 * Return: copy of the original source
 */
char *_strcpy(char *destination, char *source)
{
	int i, source_length;

	for (source_length = 0; source[source_length] != '\0'; source_length++)
		;

	for (i = 0; i <= source_length; i++)
		destination[i] = source[i];

	return (destination);
}

/**
 * _strdup - returns a pointer to a newly allocated memory space,
 * containing a duplicate of the provided string
 * @source: string to duplicate
 * Return: pointer to duplicated string in allocated memory
 */
char *_strdup(char *source)
{
	char *duplicate_str;
	int i, source_len = 0;

	if (source == NULL)
		return (NULL);

	while (source[source_len])
		source_len++;
	source_len++; /* Include space for the null terminator */

	duplicate_str = malloc(sizeof(char) * source_len);
	if (duplicate_str == NULL)
		return (NULL);

	i = 0;
	while (i < source_len)
	{
		duplicate_str[i] = source[i];
		i++;
	}

	return (duplicate_str);
}
