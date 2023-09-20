#include "shell.h"


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

