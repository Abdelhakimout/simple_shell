#include "rakia_hakim.h"

/**
 * _path - function to find the path of a command
 * @cmd: command to find its path
 * Return: path to the command, or NULL if not found
 */
char *_path(char *cmd)
{
	char *path_env, *path_copy, *path_token, *full_path;
	int cmd_len, dir_len;
	struct stat file_stat;

	path_env = _getenvironment("PATH");
	if (path_env)
	{
		path_copy = strdup(path_env);
		cmd_len = strlen(cmd);
		path_token = strtok(path_copy, ":");

		while (path_token != NULL)
		{
			dir_len = strlen(path_token);
			full_path = (char *)malloc(cmd_len + dir_len + 2);
			if (full_path == NULL)
			{
				perror("malloc error");
				free(path_copy);
				return (NULL);
			}
			strcpy(full_path, path_token);
			strcat(full_path, "/");
			strcat(full_path, cmd);
			if ((stat(full_path, &file_stat) == 0) && (S_ISREG(file_stat.st_mode)))
			{
				free(path_copy);
				return (full_path);
			}
			else
			{
				free(full_path);
				path_token = strtok(NULL, ":");
			}
		}
		free(path_copy);
	}

	if (access(cmd, X_OK) == 0)
	{
		full_path = strdup(cmd);
        return full_path;
    }

    return NULL;
}
