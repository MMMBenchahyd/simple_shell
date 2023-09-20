#include "shell.h"

/**
 * env_ky_rm - remove the key from  environment
 * @ky: the key to be removed
 * @data_ptr: the pointer of the program's data
 * Return: 1 if the key was removed, 0 if the key does not exist;
 */
int env_ky_rm(char *ky, prog_s_data *data_ptr)
{
	int i, ky_len = 0;

	/* validate the arguments */
	if (ky == NULL || data_ptr->envirmnt == NULL)
		return (0);

	/* obtains the leng of the variable requested */
	ky_len = string_len(ky);

	for (i = 0; data_ptr->envirmnt[i]; i++)
	{/* iterates through the environ and checks for coincidences */
		if (string_cmpr(ky, data_ptr->envirmnt[i], ky_len) &&
		 data_ptr->envirmnt[i][ky_len] == '=')
		{/* if key already exists, remove them */
			free(data_ptr->envirmnt[i]);

			/* move the others keys one position down */
			i++;
			for (; data_ptr->envirmnt[i]; i++)
			{
				data_ptr->envirmnt[i - 1] = data_ptr->envirmnt[i];
			}
			/* put the NULL value at the new end of the list */
			data_ptr->envirmnt[i - 1] = NULL;
			return (1);
		}
	}
	return (0);
}


/**
 * prnt_env - prints the environ
 * @data_ptr: pointer to the program's data
 * Return: void.
 */
void prnt_env(prog_s_data *data_ptr)
{
	int j;

	for (j = 0; data_ptr->envirmnt[j]; j++)
	{
		_print_str(data_ptr->envirmnt[j]);
		_print_str("\n");
	}
}
