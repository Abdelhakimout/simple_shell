#include "rakia_hakim.h"

/**
 * handle_ctrl_c - ignore Ctrl-C input and print prompt again
 * @signal_number: signal number
 */
void handle_ctrl_c(int signal_number)
{
	(void)signal_number;
	write(STDOUT_FILENO, "\n$ ", 3);
}

/**
 * custom_build_in - handles built-in commands
 * (exit, env, cd, setenv, unsetenv)
 * @command_tokens: user's typed command tokens
 * @env_list: environmental variables linked list
 * @command_line_num: nth user command typed for error message
 * @original_command: original command to be freed
 * Return: 1 if handled as a builtin, 0 if not
 */
int custom_build_in(char **command_tokens, list_t *env_list, int command_line_num, char **original_command)
{
	int result = 0;

	if (_strcmp(command_tokens[0], "exit") == 0)
	{
		result = custom_exit_command(command_tokens, env_list, command_line_num, original_command);
	}
	else if (_strcmp(command_tokens[0], "env") == 0)
	{
		print_env(command_tokens, env_list);
		result = 1;
	}
	else if (_strcmp(command_tokens[0], "cd") == 0)
	{
		result = custom_cd(command_tokens, env_list, command_line_num);
	}
	else if (_strcmp(command_tokens[0], "setenv") == 0)
	{
		_setenv(&env_list, command_tokens);
		result = 1;
	}
	else if (_strcmp(command_tokens[0], "unsetenv") == 0)
	{
		custom_unsetenv(&env_list, command_tokens);
		result = 1;
	}
	return (result);
}

/**
 * remove_leading_space - returns string without leading spaces
 * @str: input string
 * Return: new string
 */
char *remove_leading_space(char *str)
{
	while (*str == ' ')
		str++;
	return (str);
}

/**
 * handle_ctrl_D - exits the program if Ctrl-D was pressed
 * @char_count: number of characters read via get_line
 * @command: user's typed command
 * @env_list: environmental variables linked list
 */
void handle_ctrl_D(int char_count, char *command, list_t *env_list)
{
	if (char_count == 0)
	{
		free(command);
		free_linked_list(env_list);
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "\n", 1);
		exit(0);
	}
}

/**
 * shell_prompt - repeatedly prompts user, processes
 * and executes commands
 * @environment: environment variables
 * Return: 0 on success
 */
int shell_prompt(char **environment)
{
	list_t *env_list;
	size_t char_count = 0, index = 0;
	int command_line_num = 0, exit_status = 0;
	char *command, *new_command, **command_tokens;

	env_list = create_env_linked_list(environment);
	do {
		command_line_num++;
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "$ ", 2);
		else
			handle_non_interactive(env_list);
		signal(SIGINT, handle_ctrl_c);
		command = NULL;
		char_count = 0;
		char_count = custom_get_line(&command);
		handle_ctrl_D(char_count, command, env_list);
		new_command = command;
		command = remove_leading_space(command);
		index = 0;
		while (command[index] != '\n')
			index++;
		command[index] = '\0';
		if (command[0] == '\0')
		{
			free(new_command);
			continue;
		}
		command_tokens = NULL;
		command_tokens = _strtok(command, " ");
		if (new_command != NULL)
			free(new_command);
		exit_status = custom_build_in(command_tokens, env_list, command_line_num, NULL);
		if (exit_status)
			continue;
		exit_status = execute_command(command_tokens, env_list, command_line_num);
	} while (1);
	return (exit_status);
}
