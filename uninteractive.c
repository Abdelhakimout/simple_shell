#include "rakia_hakim.h"

/**
 * custom_ignore_spaces_newlines - custom function to ignore leading spaces and newlines
 * (e.g. echo "ls\n ls" | ./a.out)
 * @str: input string
 * Return: new string after ignoring spaces and newlines
 */
char *custom_ignore_spaces_newlines(char *str)
{
	while (*str == ' ' || *str == '\n')
		str++;
	return (str);
}

/**
 * handle_non_interactive - handles commands when users pipe input into the shell
 * (e.g. echo "ls\nls -al\n" | ./a.out)
 * @env_list: environmental variables linked list
 */
void handle_non_interactive(list_t *env_list)
{
	size_t i = 0, n = 0;
	int command_line_num = 0, exit_status = 0;
	char *command_buffer = NULL, *new_command_buffer = NULL, **command_lines, **tokens;

	i = custom_get_line(&command_buffer);
	if (i == 0)
	{
		free(command_buffer);
		exit(0);
	}
	new_command_buffer = command_buffer;
	command_buffer = custom_ignore_spaces_newlines(command_buffer);
	command_lines = _strtok(command_buffer, "\n"); /* Tokenize each command string */
	if (new_command_buffer != NULL)
		free(new_command_buffer);
	n = 0;
	while (command_lines[n] != NULL)
	{
		command_line_num++;
		tokens = NULL; /* Tokenize each command in the array of commands */
		tokens = _strtok(command_lines[n], " ");
		exit_status = custom_built_in(tokens, env_list, command_line_num, command_lines);
		if (exit_status)
		{
			n++;
			continue;
		}
		exit_status = execute_command(tokens, env_list, command_line_num);
		n++;
	}
	free_double_pointer(command_lines);
	free_linked_list(env_list);
	exit(exit_status);
}
