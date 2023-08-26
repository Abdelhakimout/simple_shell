#include "rakia_hakim.h"

/**
 * custom_token_count - returns the number of tokens separated by a delimiter
 * @input_str: user's command typed into the shell
 * @delimiter: delimiter character (e.g. ' ')
 * Return: number of tokens
 */
int custom_token_count(char *input_str, char delimiter)
{
	int i = 0, num_delimiters = 0;

	while (input_str[i] != '\0')
	{
		if (input_str[i] == delimiter)
		{
			num_delimiters++;
		}
		i++;
	}
	return (num_delimiters);
}

/**
 * custom_str_tok - tokenizes a string, even handling consecutive delimiters with empty strings
 * (e.g. path --> ":/bin::/bin/usr" )
 * @input_str: user's command typed into the shell
 * @delimiter: delimiter string (e.g. " ");
 * Return: an array of tokens (e.g. {"\0", "/bin", "\0", "/bin/usr"}
 * (used for commands to search through the current directory if ":")
 */
char **custom_str_tok(char *input_str, char *delimiter)
{
	int buffer_size = 0, token_index = 0, str_index = 0, i = 0, token_length = 0, str_end = 0;
	char **tokens = NULL, delim_char;

	/* Extract the delimiter character from the delimiter string */
	delim_char = delimiter[0];

	/* Calculate the number of pointers needed to store the array of tokens and an additional NULL pointer */
	buffer_size = custom_token_count(input_str, delim_char);
	tokens = malloc(sizeof(char *) * (buffer_size + 2));
	if (tokens == NULL)
		return (NULL);

	/* Find the end index of the input string */
	while (input_str[str_end] != '\0')
		str_end++;

	while (str_index < str_end)
	{
		/* Calculate length for each token pointer in the array */
		token_length = custom_token_length(input_str, str_index, delim_char);
		tokens[token_index] = malloc(sizeof(char) * (token_length + 1));
		if (tokens[token_index] == NULL)
			return (NULL);

		i = 0;
		while ((input_str[str_index] != delim_char) && (input_str[str_index] != '\0'))
		{
			tokens[token_index][i] = input_str[str_index];
			i++;
			str_index++;
		}
		tokens[token_index][i] = '\0'; /* Null-terminate at the end */
		token_index++;
		str_index++;
	}

	tokens[token_index] = NULL; /* Set the last array pointer to NULL */
	return (tokens);
}
