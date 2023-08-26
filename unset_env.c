#include "rakia_hakim.h"

/**
 * find_environment_variable - find the given environmental
 * variable in linked list
 * @env_list: linked list of environmental variables
 * @var_name: variable name to search for
 * Return: index of node in linked list, -1 if not found
 */
int find_environment_variable(list_t *env_list, char *var_name)
{
	int index = 0, match = 0;

	while (env_list != NULL)
	{
		match = 0;
		while ((env_list->var)[match] == var_name[match])
			match++;

		if (var_name[match] == '\0')
			break;

		env_list = env_list->next;
		index++;
	}

	if (env_list == NULL)
		return (-1);

	return (index);
}

/**
 * custom_unsetenv - remove a node from the environmental linked list
 * @env_list: linked list of environmental variables
 * @command: user's typed command (e.g. "unsetenv MAIL")
 * Return: 0 on success, -1 on failure
 */
int custom_unsetenv(list_t **env_list, char **command)
{
	int index = 0, j = 0;

	if (command[1] == NULL)
	{
		write(STDOUT_FILENO, "Too few arguments\n", 18);
		free_double_pointer(command);
		return (-1);
	}

	index = find_environment_variable(*env_list, command[1]);
	free_double_pointer(command);

	if (index == -1)
	{
		write(STDOUT_FILENO, "Cannot find\n", 12);
		return (-1);
	}

	j = delete_node_at_index(env_list, index);

	if (j == -1)
	{
		write(STDOUT_FILENO, "Cannot find\n", 12);
		return (-1);
	}

	return (0);
}

/**
 * _setenv - create or modify an existing environmental variable
 * in linked list
 * @env_list: linked list of environmental variables
 * @command: user's typed command (e.g. "setenv USER Superman")
 * Return: 0 on success, -1 on failure
 */
int _setenv(list_t **env_list, char **command)
{
	int index = 0, j = 0;
	char *concatenated;
	list_t *node_holder;

	if (command[1] == NULL || command[2] == NULL)
	{
		write(STDOUT_FILENO, "Too few arguments\n", 18);
		free_double_pointer(command);
		return (-1);
	}

	concatenated = _strdup(command[1]);
	concatenated = _strcat(concatenated, "=");
	concatenated = _strcat(concatenated, command[2]);

	index = find_environment_variable(*env_list, command[1]);

	if (index == -1)
	{
		add_to_end(env_list, concatenated);
	}
	else
	{
		node_holder = *env_list;
		while (j < index)
		{
			node_holder = node_holder->next;
			j++;
		}
		free(node_holder->var);
		node_holder->var = _strdup(concatenated);
	}

	free(concatenated);
	free_double_pointer(command);
	return (0);
}

