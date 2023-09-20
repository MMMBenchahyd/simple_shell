#include "shell.h"
/**
 * ben_string_tok - separates strings with delimiters
 * @l: It´s pointer to array we receive in getl.
 * @dr: It´s characters we mark off string in parts.
 * Return: A pointer to the created token
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
