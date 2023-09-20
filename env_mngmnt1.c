#include "shell.h"

/**
 * env_ky_gt - obtains a variable's value in the environment
 * @ky: the relevant environment variable
 * @data_ptr: the pointer of the program's data
 * Return: a pointer to the variable's value or NULL if it isn't there.
 */
char *env_ky_gt(char *ky, prog_s_data *data_ptr)
{
	int i, ky_len = 0;


	if (ky == NULL || data_ptr->envirmnt == NULL)
		return (NULL);

	ky_len = string_len(ky);

	for (i = 0; data_ptr->envirmnt[i]; i++)
	{
		if (string_cmpr(ky, data_ptr->envirmnt[i], ky_len) &&
		 data_ptr->envirmnt[i][ky_len] == '=')
		{
			return (data_ptr->envirmnt[i] + ky_len + 1);
		}
	}
	return (NULL);
}

/**
 * env_ky_st - replace the environment variable's value with 
 * a new one or, if necessary, create one.
 * @ky: the variable's name to set
 * @val: new value
 * @data_ptr: the pointer of the program's data
 * Return: 1 if the parameters are NULL, 2 if there is an erroror 0 if sucess.
 */

int env_ky_st(char *ky, char *val, prog_s_data *data_ptr)
{
	int i, ky_len = 0, nu_ky = 1;

	if (ky == NULL || val == NULL || data_ptr->envirmnt == NULL)
		return (1);

	ky_len = string_len(ky);

	for (i = 0; data_ptr->envirmnt[i]; i++)
	{
		if (string_cmpr(ky, data_ptr->envirmnt[i], ky_len) &&
		 data_ptr->envirmnt[i][ky_len] == '=')
		{
			nu_ky = 0;
			free(data_ptr->envirmnt[i]);
			break;
		}
	}

	data_ptr->envirmnt[i] = string_conc(string_dup(ky), "=");
	data_ptr->envirmnt[i] = string_conc(data_ptr->envirmnt[i], val);

	if (nu_ky)
	{
		data_ptr->envirmnt[i + 1] = NULL;
	}
	return (0);
}
