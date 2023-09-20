#include "shell.h"

/**
 * numb_to_str - converting a giving number to a string.
 * @num: the number to be converted in an string.
 * @str: a buffer to save the giving number as string.
 * @b: the base to convert the number
 *
 * Return: nothing cz its a void func
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
 * _arr_to_int - will convert strings to integers.
 *
 * @str: ptr to str origen aaa.
 * Return: return int of string or zero 0.
 */
int _arr_to_int(char *str)
{
	int sn = 1;
	unsigned int numb = 0;
	while (!('0' <= *str && *str <= '9') && *str != '\0')
	{
		if (*str == '-')
			sn *= -1;
		if (*str == '+')
			sn *= +1;
		str++;
	}

	while ('0' <= *str && *str <= '9' && *str != '\0')
	{

		numb = (numb * 10) + (*str - '0');
		str++;
	}
	return (numb * sn);
}

/**
 * char_counter - calculate the coincidences of charactr in a string.
 *
 * @s: PTR to str origen.aa
 * @c: string with characters to be counted
 * Return: return an int of string or zero 0.
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
