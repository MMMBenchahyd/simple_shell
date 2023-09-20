#include "shell.h"

/**
* _getln - recite the first line of the prompt.
* @data_ptr: poiter of the program's data
*
* Return: reading counting bytes.
*/
int _getln(prog_s_data *data_ptr)
{
	char buffer[BUFFER_SIZE] = {'\0'};
	static char *arr_cmnd[10] = {NULL};
	static char arr_opr[10] = {'\0'};
	ssize_t byte_rd, i = 0;


	if (!arr_cmnd[0] || (arr_opr[0] == '&' && errno != 0) ||
		(arr_opr[0] == '|' && errno == 0))
	{
		for (i = 0; arr_cmnd[i]; i++)
		{
			free(arr_cmnd[i]);
			arr_cmnd[i] = NULL;
		}

		byte_rd = read(data_ptr->fil_dscription, &buffer, BUFFER_SIZE - 1);
		if (byte_rd == 0)
			return (-1);

		i = 0;
		do {
			arr_cmnd[i] = string_dup(ben_string_tok(i ? NULL : buffer, "\n;"));
			i = chk_for_logic_oprts(arr_cmnd, i, arr_opr);
		} while (arr_cmnd[i++]);
	}

	data_ptr->in_ln = arr_cmnd[0];
	for (i = 0; arr_cmnd[i]; i++)
	{
		arr_cmnd[i] = arr_cmnd[i + 1];
		arr_opr[i] = arr_opr[i + 1];
	}

	return (string_len(data_ptr->in_ln));
}


/**
* chk_for_logic_oprts - checks and splitting for the operators && and ||.
* @arr_cmnd: a list of commands.
* @i: to be checked is the index in the arr_cmnd.
* @arr_opr: array containing the logical operators for every command before that
*
* Return: index of the last command in the arr_cmnd.
*/
int chk_for_logic_oprts(char *arr_cmnd[], int i, char arr_opr[])
{
	char *tmp = NULL;
	int j;

	for (j = 0; arr_cmnd[i] != NULL  && arr_cmnd[i][j]; j++)
	{
		if (arr_cmnd[i][j] == '&' && arr_cmnd[i][j + 1] == '&')
		{
			tmp = arr_cmnd[i];
			arr_cmnd[i][j] = '\0';
			arr_cmnd[i] = string_dup(arr_cmnd[i]);
			arr_cmnd[i + 1] = string_dup(tmp + j + 2);
			i++;
			arr_opr[i] = '&';
			free(tmp);
			j = 0;
		}
		if (arr_cmnd[i][j] == '|' && arr_cmnd[i][j + 1] == '|')
		{

			tmp = arr_cmnd[i];
			arr_cmnd[i][j] = '\0';
			arr_cmnd[i] = string_dup(arr_cmnd[i]);
			arr_cmnd[i + 1] = string_dup(tmp + j + 2);
			i++;
			arr_opr[i] = '|';
			free(tmp);
			j = 0;
		}
	}
	return (i);
}
