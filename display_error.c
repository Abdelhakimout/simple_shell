#include "rakia_hakim.h"

/**
 * command_not_found - write error message for command not found
 * @command: command that was not found
 * @command_num: nth user's typed command
 * @env_list: environmental variables linked list to retrieve shell name
 */
void command_not_found(char *command, int command_num, list_t *env_list)
{
	int count = 0;
	char *shell, *num;

	shell = get_env("_", env_list);
	while (shell[count] != '\0')
		count++;
	write(STDOUT_FILENO, shell, count);
	free(shell);
	write(STDOUT_FILENO, ": ", 2);
	num = int_to_string(command_num);
	count = 0;
	while (num[count] != '\0')
		count++;
	write(STDOUT_FILENO, num, count);
	free(num);
	write(STDOUT_FILENO, ": ", 2);
	write(STDOUT_FILENO, command, custom_strlen(command));
	write(STDOUT_FILENO, ": ", 2);
	write(STDOUT_FILENO, "not found\n", 10);
}

/**
 * report_cd_error - write error message for cd command
 * @arg: argument provided to the cd command
 * @command_num: nth user's typed command
 * @env_list: environmental variables linked list to retrieve shell name
 */
void report_cd_error(char *arg, int command_num, list_t *env_list)
{
	int count = 0;
	char *shell, *num;

	shell = get_env("_", env_list);
	while (shell[count] != '\0')
		count++;
	write(STDOUT_FILENO, shell, count);
	free(shell);
	write(STDOUT_FILENO, ": ", 2);
	num = int_to_string(command_num);
	count = 0;
	while (num[count] != '\0')
		count++;
	write(STDOUT_FILENO, num, count);
	free(num);
	write(STDOUT_FILENO, ": ", 2);
	write(STDOUT_FILENO, "cd: can't cd to ", 16);
	count = 0;
	while (arg[count] != '\0')
		count++;
	write(STDOUT_FILENO, arg, count);
	write(STDOUT_FILENO, "\n", 1);
}

/**
 * illegal_number_error - write error message for illegal exit number
 * @num_str: argument provided to the exit command
 * @command_num: nth user's typed command
 * @env_list: environmental variables linked list to retrieve shell name
 */
void illegal_number_error(char *num_str, int command_num, list_t *env_list)
{
	int count = 0;
	char *shell = NULL, *num = NULL;

	shell = get_env("_", env_list);
	while (shell[count] != '\0')
		count++;
	write(STDOUT_FILENO, shell, count);
	free(shell);
	write(STDOUT_FILENO, ": ", 2);
	num = int_to_string(command_num);
	count = 0;
	while (num[count] != '\0')
		count++;
	write(STDOUT_FILENO, num, count);
	free(num);
	write(STDOUT_FILENO, ": ", 2);
	write(STDOUT_FILENO, "exit: Illegal number: ", 22);
	count = 0;
	while (num_str[count] != '\0')
		count++;
	write(STDOUT_FILENO, num_str, count);
	write(STDOUT_FILENO, "\n", 1);
}
