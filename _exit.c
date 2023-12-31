#include "rakia_hakim.h"

/**
 * custom_string_to_int - Converts a string to an integer.
 * @input_str: The input string.
 *
 * Return: The int value if success, or -1 if the string contains non-numbers.
 */
int custom_string_to_int(char *input_str)
{
int index = 0;
unsigned int result = 0;

while (input_str[index] != '\0')
{
if (input_str[index] >= '0' && input_str[index] <= '9')
result = result * 10 + (input_str[index] - '0');
if (input_str[index] > '9' || input_str[index] < '0')
return (-1);
index++;
}
return (result);
}

/**
 * custom_exit_command - Frees user input and exits the main program.
 * @args: User's command into the shell (e.g. "exit 99").
 * @environment: Environmental variables to free in case of error.
 * @command_num: Number of the user's command line input.
 * @command_tokens: Command to free.
 *
 * Return: 0 if successful, 2 if failed.
 */
int custom_exit_command(char **args, list_t *environment, int command_num, char **command_tokens)
{
int exit_value = 0;

if (args[1] != NULL)
exit_value = custom_string_to_int(args[1]);

if (exit_value == -1)
{
illegal_number_error(args[1], command_num, environment);
free_double_pointer(args);
return (2);
}
free_double_pointer(args);
free_linked_list(environment);

if (command_tokens != NULL)
free_double_pointer(command_tokens);

exit(exit_value);
}
