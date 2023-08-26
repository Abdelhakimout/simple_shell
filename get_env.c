#include "rakia_hakim.h"

/**
 * custom_strdup - custom string duplication excluding initial bytes
 * @source: string to duplicate (e.g. environmental variable PATH=/bin:/bin/ls)
 * @exclude_bytes: number of bytes to exclude (e.g. excludes "PATH=")
 * Return: duplicated string (e.g. /bin:/bin/ls)
 */
char *custom_strdup(char *source, int exclude_bytes)
{
	char *duplicate_str;
	int i, source_len = 0;

	if (source == NULL)
		return (NULL);

	while (*(source + source_len))
		source_len++;
	source_len++;

	duplicate_str = malloc(sizeof(char) * (source_len - exclude_bytes));
	if (duplicate_str == NULL)
		return (NULL);

	i = 0;
	while (i < (source_len - exclude_bytes))
	{
		*(duplicate_str + i) = *(source + exclude_bytes + i);
		i++;
	}
	return (duplicate_str);
}

/**
 * get_env - finds and returns a copy of the requested environmental variable
 * @var_name: name of the environmental variable to retrieve
 * @env_list: linked list containing environmental variables
 * Return: copy of the requested environmental variable
 */
char *get_env(char *var_name, list_t *env_list)
{
	int j = 0, exclude_bytes = 0;

	while (env_list != NULL)
	{
		j = 0;
		while ((env_list->var)[j] == var_name[j])
			j++;
		if (var_name[j] == '\0' && (env_list->var)[j] == '=')
			break;
		env_list = env_list->next;
	}

	while (var_name[exclude_bytes] != '\0')
		exclude_bytes++;
	exclude_bytes++;

	return (custom_strdup(env_list->var, exclude_bytes));
}
