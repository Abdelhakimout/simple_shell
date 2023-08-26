#include "rakia_hakim.h"

/**
 * count_digits - counts the number of digits in an integer
 * @num: the integer to count digits in
 * Return: the count of digits
 */
int count_digits(int num)
{
	int count = 0;
	int absolute_num = num;

	while (absolute_num > 9 || absolute_num < -9)
	{
		absolute_num /= 10;
		count++;
	}
	return (count);
}

/**
 * int_to_string - converts an integer to a string
 * @number: the integer to be converted
 * Return: a string representation of the integer, or NULL if failed
 */
char *int_to_string(int number)
{
	int num_digits, tens, i = 0, is_negative = 0, x;
	char *result;

	num_digits = number;
	tens = 1;

	if (number < 0)
		is_negative = 1;
	result = malloc(sizeof(char) * (count_digits(num_digits) + 2 + is_negative));
	if (result == NULL)
		return (NULL);
	if (number < 0)
	{
		result[i] = '-';
		i++;
	}
	for (x = 0; num_digits > 9 || num_digits < -9; x++)
	{
		num_digits /= 10;
		tens *= 10;
	}
	for (num_digits = number; x >= 0; x--)
	{
		if (num_digits < 0)
		{
			result[i] = (num_digits / tens) * -1 + '0';
			i++;
		}
		else
		{
			result[i] = (num_digits / tens) + '0';
			i++;
		}
		num_digits %= tens;
		tens /= 10;
	}
	result[i] = '\0';
	return (result);
}
