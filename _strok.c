#include "rakia_hakim.h"

/**
 * custom_token_length - returns the length of a token for memory allocation
 * @input: input string
 * @position: starting index in the input string
 * @delimiter: delimiter character (e.g. ' ')
 * Return: token length
 */
int custom_token_length(char *input, int position, char delimiter)
{
	int length = 0;

	while ((input[position] != delimiter) && (input[position] != '\0'))
	{
		position++;
		length++;
	}
	return (length);
}

/**
 * token_count - returns the number of tokens, ignoring consecutive delimiters
 * @input: input string
 * @delimiter: delimiter character (e.g. ' ')
 * Return: number of tokens
 */
int token_count(char *input, char delimiter)
{
	int i = 0, delimiter_count = 0;

	while (input[i] != '\0')
	{
		if ((input[i] == delimiter) && (input[i + 1] != delimiter))
		{
			delimiter_count++;
		}
		if ((input[i] == delimiter) && (input[i + 1] == '\0'))
		{
			delimiter_count--;
		}
		i++;
	}
	return (delimiter_count);
}

/**
 * ignore_leading_delimiters - returns a version of the string without leading delimiters
 * @input: input string
 * @delimiter: delimiter character (e.g. ' ')
 * Return: new string with leading delimiters removed
 */
char *ignore_leading_delimiters(char *input, char delimiter)
{
	while (*input == delimiter)
		input++;
	return (input);
}

/**
 * _strtok - tokenizes a string and returns an array of tokens
 * @input: input string
 * @delimiter: delimiter string (e.g. " ")
 * Return: an array of tokens
 */
char **_strtok(char *input, char *delimiter)
{
	int buffer_size = 0, position = 0, token_index = 0, i = 0, token_length = 0, string_end = 0;
	char **tokens = NULL, delimiter_char;

	delimiter_char = delimiter[0];

	input = ignore_leading_delimiters(input, delimiter_char);

	buffer_size = token_count(input, delimiter_char);
	tokens = malloc(sizeof(char *) * (buffer_size + 2));
	if (tokens == NULL)
		return (NULL);

	while (input[string_end] != '\0')
		string_end++;

	while (position < string_end)
	{
		if (input[position] != delimiter_char)
		{
			token_length = custom_token_length(input, position, delimiter_char);
			tokens[token_index] = malloc(sizeof(char) * (token_length + 1));
			if (tokens[token_index] == NULL)
				return (NULL);
			i = 0;
			while ((input[position] != delimiter_char) && (input[position] != '\0'))
			{
				tokens[token_index][i] = input[position];
				i++;
				position++;
			}
			tokens[token_index][i] = '\0';
			token_index++;
		}
		if (position < string_end && (input[position + 1] != delimiter_char && input[position + 1] != '\0'))
			token_index++;
		position++;
	}
	token_index++;
	tokens[token_index] = NULL;
	return (tokens);
}
