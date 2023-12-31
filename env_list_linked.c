#include "rakia_hakim.h"

/**
 * create_env_linked_list - creates a linked list from environmental variables
 * @env_vars: array of environmental variables
 * Return: pointer to the head of the linked list
 */
list_t *create_env_linked_list(char **env_vars)
{
	list_t *head;
	int i = 0;

	head = NULL;
	while (env_vars[i] != NULL)
	{
		add_to_end(&head, env_vars[i]);
		i++;
	}
	return (head);
}

/**
 * print_env - prints environmental variables
 * @user_command: user's command (i.e. "env")
 * @env_list: linked list of environmental variables
 * Return: 0 on success
 */
int print_env(char **user_command, list_t *env_list)
{
	free_double_pointer(user_command);
	display_list(env_list);
	return (0);
}
