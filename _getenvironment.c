#include "rakia_hakim.h"

/**
 * _getenvironment- function to get env of a global variable
 * @gb_va : var to get its env
 * Return: pointer to env or NULL if fails
*/

char *_getenvironment(char *gb_va)
{
	char *entry, *delimiter;
	size_t name_length;
	int i;

	if (gb_va == NULL)
	{
		return (NULL);
	}

	for (i = 0; environ[i] != NULL; i++)
	{
		entry = environ[i];
		delimiter = strchr(entry, '=');

		if (delimiter == NULL)
		{
			continue;
		}

		name_length = delimiter - entry;

		if (strncmp(entry, gb_va, name_length) == 0)
		{
			return (delimiter + 1);
		}
	}

	return (NULL);
}
