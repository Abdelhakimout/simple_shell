#include "rakia_hakim.h"

/**
 * _strcat - concatenate two strings excluding the first character ("~" in cd)
 * @destination: string to be appended to
 * @source: string to append
 * Return: concatenated string
 */
char *_strcat(char *destination, char *source)
{
	int dest_len = 0;
	int src_len = 0;
	int total_len = 0;
	int j = 0;

	/* Calculate total length of both strings for memory reallocation */
	while (destination[dest_len] != '\0')
	{
		dest_len++;
		total_len++;
	}
	while (source[src_len] != '\0')
	{
		src_len++;
		total_len++;
	}

	/* Reallocate memory for destination string */
	destination = _realloc(destination, dest_len, sizeof(char) * (total_len + 1));

	j = 1; /* Ignore the first character */
	while (source[j] != '\0')
	{
		destination[dest_len] = source[j];
		dest_len++;
		j++;
	}
	destination[dest_len] = '\0';

	return (destination);
}

/**
 * custom_setenv - custom version of _setenv by concatenat strings before set
 * @env_list: environmental variable linked list
 * @var_name: environmental variable name (e.g. "OLDPWD")
 * @dir_path: directory path (e.g. "/home/user/directory")
 * Return: 0 on success (e.g. "OLDPWD=/home/user/directory")
 */
int custom_setenv(list_t **env_list, char *var_name, char *dir_path)
{
	int index = 0, j = 0;
	char *concatenated;
	list_t *node;

	concatenated = _strdup(var_name); /* Create concatenated string */
	concatenated = _strcat(concatenated, "=");
	concatenated = _strcat(concatenated, dir_path);
	index = find_env(*env_list, var_name); /* Get index of env var in link list */

	/* Traverse to the index, free node data, reassign data */
	node = *env_list;
	while (j < index)
	{
		node = node->next;
		j++;
	}
	free(node->var);
	node->var = _strdup(concatenated);
	free(concatenated);
	return (0);
}

/**
 * change_directory_only - change directory to home
 * @env_list: environmental linked list to update PATH and OLDPWD
 * @current_dir: current working directory
 */
void change_directory_only(list_t *env_list, char *current_dir)
{
	char *home_dir = NULL;

	home_dir = get_env("HOME", env_list);
	custom_setenv(&env_list, "OLDPWD", current_dir); /* Update env OLDPWD */
	free(current_dir);
	if (access(home_dir, F_OK) == 0) /* If exists, go to home directory */
		chdir(home_dir);
	current_dir = NULL;
	current_dir = getcwd(current_dir, 0);
	custom_setenv(&env_list, "PWD", current_dir); /* Update env PWD */
	free(current_dir);
	free(home_dir);
}

/**
 * execute_cd - execute the cd command
 * @env_list: environmental linked list to update PATH and OLDPWD
 * @current_dir: current working directory
 * @target_dir: target directory path to change to
 * @arg_str: the first argument to write out an error
 * @line_num: the line number to write out an error
 * Return: 0 if successful, 2 if failed
 */
int execute_cd(list_t *env_list, char *current_dir, char *target_dir, char *arg_str, int line_num)
{
	int exit_status = 0;

	if (access(target_dir, F_OK) == 0)
	{
		custom_setenv(&env_list, "OLDPWD", current_dir); /* Update env OLDPWD */
		free(current_dir);
		chdir(target_dir);
		current_dir = NULL;
		current_dir = getcwd(current_dir, 0);
		custom_setenv(&env_list, "PWD", current_dir); /* Update env PWD */
		free(current_dir);
	}
	else
	{
		report_cd_error(arg_str, line_num, env_list);
		free(current_dir);
		exit_status = 2;
	}
	return (exit_status);
}

/**
 * custom_cd - change directory command
 * @user_input: user's typed-in command
 * @env_list: environmental linked list to retrieve HOME and OLDPWD paths
 * @command_num: nth user command, used for error message
 * Return: 0 if successful, 2 if failed
 */
int custom_cd(char **user_input, list_t *env_list, int command_num)
{
	char *current_dir = NULL, *target_dir = NULL;
	int exit_code = 0;

	current_dir = getcwd(current_dir, 0); /* Store current working directory */
	if (user_input[1] != NULL)
	{
		if (user_input[1][0] == '~') /* Usage: cd ~ */
		{
			target_dir = get_env("HOME", env_list);
			target_dir = _strcat(target_dir, user_input[1]);
		}
		else if (user_input[1][0] == '-') /* Usage: cd - */
		{
			if (user_input[1][1] == '\0')
				target_dir = get_env("OLDPWD", env_list);
		}
		else /* Usage: cd directory1 */
		{
			if (user_input[1][0] != '/')
			{
				target_dir = getcwd(target_dir, 0);
				target_dir = _strcat(target_dir, "/");
				target_dir = _strcat(target_dir, user_input[1]);
			}
			else
				target_dir = _strdup(user_input[1]);
		}
		exit_code = execute_cd(env_list, current_dir, target_dir, user_input[1], command_num);
		free(target_dir);
	}
	else /* Usage: cd */
		change_directory_only(env_list, current_dir);
	free_double_pointer(user_input); /* Free user input */
	return (exit_code);
}
