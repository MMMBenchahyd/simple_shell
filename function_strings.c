#include "shell.h"

/**
 * string_len - returns the length of a string.
 * @str: pointer to string.
 * Return: length of string.
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
 * string_dup - duplicates an string
 * @str: String to be copied
 * Return: pointer to the array
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
 * @str1: String one, or the shorter
 * @str2: String two, or the longer
 * @numb: number of characters to be compared, 0 if infinite
 * Return: 1 if the strings are equals,0 if the strings are different
 */
int string_cmpr(char *str1, char *str2, int numb)
{
	int itr;

	if (str1 == NULL && str2 == NULL)
		return (1);

	if (str1 == NULL || str2 == NULL)
		return (0);

	if (numb == 0) /* infinite longitud */
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
	else /* if there is a number of chars to be compared */
	{
		for (itr = 0; itr < numb ; itr++)
		{
			if (str1[itr] != str2[itr])
			return (0);
		}
		return (1);
	}
}

/**
 * string_conc - concatenates two strings.
 * @str1: String to be concatenated
 * @str2: String to be concatenated
 *
 * Return: pointer to the array
 */
char *string_conc(char *str1, char *str2)
{
	char *rslt;
	int len1 = 0, len2 = 0;

	if (str1 == NULL)
		str1 = "";
	len1 = string_len(str1);

	if (str2 == NULL)
		str2 = "";
	len2 = string_len(str2);

	rslt = malloc(sizeof(char) * (len1 + len2 + 1));
	if (rslt == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return (NULL);
	}

	/* copy of str1 */
	for (len1 = 0; str1[len1] != '\0'; len1++)
		rslt[len1] = str1[len1];
	free(str1);

	/* copy of str2 */
	for (len2 = 0; str2[len2] != '\0'; len2++)
	{
		rslt[len1] = str2[len2];
		len1++;
	}

	rslt[len1] = '\0';
	return (rslt);
}


/**
 * string_rev - reverses a string.
 *
 * @str: pointer to string.
 * Return: void.
 */
void string_rev(char *str)
{

	int i = 0, len = string_len(str) - 1;
	char k;

	while (i < len)
	{
		k = str[i];
		str[i++] = str[len];
		str[len--] = k;
	}
}
