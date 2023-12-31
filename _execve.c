#include "rakia_hakim.h"

/**
 * custom_exit - frees memory allocated for user com and link list before exit
 * @user_command: user's typed command
 * @env_list: linked list of environment variables
 */
void custom_exit(char **user_command, list_t *env_list)
{
	free_double_pointer(user_command);
	free_linked_list(env_list);
	_exit(0);
}

/**
 * execute_command - execute the command typed by the user
 * @command: command typed by the user
 * @env_list: environmental variables linked list
 * @command_num: nth user command; used in error message
 * Return: 0 on success
 */
int execute_command(char **command, list_t *env_list, int command_num)
{
	char *command_path;
	int status = 0, is_absolute = 0;
	pid_t pid;
	/* Check if the command has an absolute path */
	if (access(command[0], F_OK) == 0)
	{
		command_path = command[0];
		is_absolute = 1;
	}
	/* Otherwise, determine full path of the command */
	else
		command_path = determine_full_path(command[0], env_list);
	/* If the command is not executable, free resources */
	if (access(command_path, X_OK) != 0)
	{
		command_not_found(command[0], command_num, env_list);
		free_double_pointer(command);
		return (127); /* Return status indicating command not found */
	}
	else /* Otherwise, fork and execute the executable command */
	{
		pid = fork();
		if (pid == 0) /* If child process, execute the command */
		{
			if (execve(command_path, command, NULL) == -1)
			{
				command_not_found(command[0], command_num, env_list); /* Special er mes */
				custom_exit(command, env_list);
			}
		}
		else /* If parent proc, wait for child to complete and then free resourc */
		{
			wait(&status);
			free_double_pointer(command);
			if (!is_absolute)
				free(command_path);
		}
	}
	return (0);
}
