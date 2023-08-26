#include "rakia_hakim.h"

/**
 * determine_full_path - expands a command by appending it
 * to a matching PATH directory
 * @command: first command entered by the user in the shell
 * @env_list: environmental variable linked list
 * Return: a copy of the expanded command
 */
char *determine_full_path(char *command, list_t *env_list)
{
	char *path_var, *concatenated = NULL, **path_tokens;
	int i = 0;

	path_var = get_env("PATH", env_list);
	path_tokens = custom_str_tok(path_var, ":");
	free(path_var);

	i = 0;
	while (path_tokens[i] != NULL)
	{
		if (path_tokens[i][0] == '\0')
			concatenated = getcwd(concatenated, 0);
		else
			concatenated = _strdup(path_tokens[i]);
		concatenated = _strcat(concatenated, "/");
		concatenated = _strcat(concatenated, command);
		if (access(concatenated, F_OK) == 0)
		{
			free_double_pointer(path_tokens);
			return (concatenated);
		}
		free(concatenated);
		i++;
	}
	free_double_pointer(path_tokens);
	return (command);
}
