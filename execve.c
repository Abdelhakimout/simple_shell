#include "rakia_hakim.h"
/**
 * execute_command - function to execute command
 * @pt: array of command arguments
 * Return: exit status of the executed command
 */
int execute_command(char **pt)
{
	pid_t pid;
	int status;

	pid = fork();

	if (pid == -1)
	{
		perror("fork() error");
		return (1);
	}
	else if (pid == 0)
	{
		if (execvp(pt[0], pt) == -1)
		{
			perror("execvp error");
			exit(127);
		}
	}
	else
	{
		if (waitpid(pid, &status, 0) == -1)
		{
			perror("waitpid error");
			return (1);
		}

		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
		else
			return (1);
	}
}
