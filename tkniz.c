#include "shell.h"
/**
 * _tkniz - this function separate the string using a designed delimiter
 * @data_ptr: a pointer to the program's data
 * Return: an array of the different parts of the string
 */
void _tkniz(prog_s_data *data_ptr)
{
	char *del = " \t";
	int i, j, cnt = 2, len;

	len = string_len(data_ptr->in_ln);
	if (len)
	{
		if (data_ptr->in_ln[len - 1] == '\n')
			data_ptr->in_ln[len - 1] = '\0';
	}

	for (i = 0; data_ptr->in_ln[i]; i++)
	{
		for (j = 0; del[j]; j++)
		{
			if (data_ptr->in_ln[i] == del[j])
				cnt++;
		}
	}

	data_ptr->tkn = malloc(cnt * sizeof(char *));
	if (data_ptr->tkn == NULL)
	{
		perror(data_ptr->name_of_prog);
		exit(errno);
	}
	i = 0;
	data_ptr->tkn[i] = string_dup(ben_string_tok(data_ptr->in_ln, del));
	data_ptr->cmd_name = string_dup(data_ptr->tkn[0]);
	while (data_ptr->tkn[i++])
	{
		data_ptr->tkn[i] = string_dup(ben_string_tok(NULL, del));
	}
}
