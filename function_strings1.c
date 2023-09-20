#include "shell.h"

/**
 * string_len - returns length of a given string.
 * @str: pointer to a given string.
 * Return: length of a given string.
 */
int string_len(char *str)
{
	int len = 0;

	if (str == NULL)
		return (0);

	while (str[len++] != '\0')
	{
	}
	return (--len);
}

/**
 * string_dup - duplicates a given string
 * @str: String to be duplicated
 * Return: pointer to the string
 */
char *string_dup(char *str)
{
	char *rslt;
	int len, i;

	if (str == NULL)
		return (NULL);

	len = string_len(str) + 1;

	rslt = malloc(sizeof(char) * len);

	if (rslt == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return (NULL);
	}
	for (i = 0; i < len ; i++)
	{
		rslt[i] = str[i];
	}

	return (rslt);
}

/**
 * string_cmpr - Compare two strings
 * @str1: String one
 * @str2: String two
 * @numb: number of characters to be compared, 0 if infinite
 * Return: 0 if they are different, 1 if they are equals
 */
int string_cmpr(char *str1, char *str2, int numb)
{
	int itr;

	if (str1 == NULL && str2 == NULL)
		return (1);

	if (str1 == NULL || str2 == NULL)
		return (0);

	if (numb == 0)
	{
		if (string_len(str1) != string_len(str2))
			return (0);
		for (itr = 0; str1[itr]; itr++)
		{
			if (str1[itr] != str2[itr])
				return (0);
		}
		return (1);
	}
	else
	{
		for (itr = 0; itr < numb ; itr++)
		{
			if (str1[itr] != str2[itr])
			return (0);
		}
		return (1);
	}
}
