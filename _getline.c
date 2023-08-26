#include "rakia_hakim.h"

/**
 * custom_get_line - reads user input into a dynamically allocated buffer
 * @buffer: buffer to store user input
 * Return: number of characters read
 */
size_t custom_get_line(char **buffer)
{
	ssize_t read_chars = 0, total_size = 0, is_newline = 0, char_index = 0;
	char temp_buffer[1024];

	while (!is_newline && (read_chars = read(STDIN_FILENO, temp_buffer, 1024 - 1)))
	{
		if (read_chars == -1)
			return (-1);

		temp_buffer[read_chars] = '\0';

		char_index = 0;
		while (temp_buffer[char_index] != '\0')
		{
			if (temp_buffer[char_index] == '\n')
				is_newline = 1;
			char_index++;
		}

		if (total_size == 0)
		{
			read_chars++;
			*buffer = malloc(sizeof(char) * read_chars);
			*buffer = _strcpy(*buffer, temp_buffer);
			total_size = read_chars;
		}
		else
		{
			total_size += read_chars;
			*buffer = _strcat(*buffer, temp_buffer);
		}
	}
	return (total_size);
}
