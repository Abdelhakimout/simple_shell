#include "rakia_hakim.h"

/**
 * main - Entry point of the program.
 *
 * Return: Always 0.
 */
int main(void)
{
	char *prompt = "$ ";
	char *exit_message = "Exiting..\n";
	const char *delimiter = " \n";
	char *input_buffer = NULL, *input_copy = NULL, *token;
	char **arguments;
	size_t buffer_size = 0;
	ssize_t chars_read;
	int token_count = 0, j;

	while (1)
	{
		printf("%s", prompt);
		chars_read = getline(&input_buffer, &buffer_size, stdin);
		if (chars_read == -1)
		{
			printf("%s", exit_message);
			continue;
		}
		input_copy = strdup(input_buffer);
		if (input_copy == NULL)
		{
			perror("malloc failed");
			continue;
		}

		token = strtok(input_buffer, delimiter);
		while (token != NULL)
		{
			token_count++;
			token = strtok(NULL, delimiter);
		}
		token_count++;

		arguments = malloc(sizeof(char *) * token_count);

		token = strtok(input_copy, delimiter);
		for (j = 0; token != NULL; j++)
		{
			arguments[j] = strdup(token);
			if (arguments[j] == NULL)
			{
				perror("malloc failed");
				return (-1);
			}
			token = strtok(NULL, delimiter);
		}
		arguments[j] = NULL;
		execute_command(arguments);

		for (j = 0; j < token_count; j++)
		{
			free(arguments[j]);
		}
		free(arguments);
		free(input_copy);
	}
	return (0);
}
