#include "shell.h"
/**
 * ben_string_tok - separates strings with delimiters
 * @l: Pointer to a string.
 * @dr: Characters are what we remove in pieces from a string..
 * Return: A pointer to the token
*/
char *ben_string_tok(char *l, char *dr)
{
	int j;
	static char *str;
	char *strin_cp;

	if (l != NULL)
		str = l;
	for (; *str != '\0'; str++)
	{
		for (j = 0; dr[j] != '\0'; j++)
		{
			if (*str == dr[j])
			break;
		}
		if (dr[j] == '\0')
			break;
	}
	strin_cp = str;
	if (*strin_cp == '\0')
		return (NULL);
	for (; *str != '\0'; str++)
	{
		for (j = 0; dr[j] != '\0'; j++)
		{
			if (*str == dr[j])
			{
				*str = '\0';
				str++;
				return (strin_cp);
			}
		}
	}
	return (strin_cp);
}
