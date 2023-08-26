#include "rakia_hakim.h"
/**
 * free_double_pointer - free malloced arrays
 * @str: array of strings
 */
void free_double_pointer(char **str)
{
	int i = 0;

	while (str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	free(str);
}
