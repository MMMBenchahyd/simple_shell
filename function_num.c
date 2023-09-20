#include "shell.h"

/**
 * numb_to_str - converts a number to a string.
 * @num: number to be converten in an string.
 * @str: buffer to save the number as string.
 * @b: base to convert number
 *
 * Return: Void.
 */
void numb_to_str(long num, char *str, int b)
{
	int i = 0, negative = 0;
	long c = num;
	char lttrs[] = {"0123456789abcdef"};

	if (c == 0)
		str[i++] = '0';

	if (str[0] == '-')
		negative = 1;

	while (c)
	{
		if (c < 0)
			str[i++] = lttrs[-(c % b)];
		else
			str[i++] = lttrs[c % b];
		c /= b;
	}
	if (negative)
		str[i++] = '-';

	str[i] = '\0';
	string_rev(str);
}


/**
 * _arr_to_int - convert a string to an integer.
 *
 * @str: pointer to str origen.
 * Return: int of string or 0.
 */
int _arr_to_int(char *str)
{
	int sn = 1;
	unsigned int numb = 0;
	/*1- analisys sign*/
	while (!('0' <= *str && *str <= '9') && *str != '\0')
	{
		if (*str == '-')
			sn *= -1;
		if (*str == '+')
			sn *= +1;
		str++;
	}

	/*2 - extract the number */
	while ('0' <= *str && *str <= '9' && *str != '\0')
	{

		numb = (numb * 10) + (*str - '0');
		str++;
	}
	return (numb * sn);
}

/**
 * char_counter - count the coincidences of character in string.
 *
 * @s: pointer to str origen.
 * @c: string with  chars to be counted
 * Return: int of string or 0.
 */
int char_counter(char *s, char *c)
{
	int i = 0, cer = 0;

	for (; s[i]; i++)
	{
		if (s[i] == c[0])
			cer++;
	}
	return (cer);
}
