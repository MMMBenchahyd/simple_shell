#include "shell.h"

/**
 * env_ky_gt - gets the value of an environment variable
 * @ky: the environment variable of interest
 * @data_ptr: struct of the program's data
 * Return: a pointer to the value of the variable or NULL if it doesn't exist
 */
char *env_ky_gt(char *ky, prog_s_data *data_ptr)
{
	int i, ky_len = 0;

	/* validate the arguments */
	if (ky == NULL || data_ptr->envirmnt == NULL)
		return (NULL);

	/* obtains the leng of the variable requested */
	ky_len = string_len(ky);

	for (i = 0; data_ptr->envirmnt[i]; i++)
	{/* Iterates through the environ and check for coincidence of the vame */
		if (string_cmpr(ky, data_ptr->envirmnt[i], ky_len) &&
		 data_ptr->envirmnt[i][ky_len] == '=')
		{/* returns the value of the ky NAME=  when find it*/
			return (data_ptr->envirmnt[i] + ky_len + 1);
		}
	}
	/* returns NULL if did not find it */
	return (NULL);
}

/**
 * env_ky_st - overwrite the value of the environment variable
 * or create it if does not exist.
 * @ky: name of the variable to set
 * @val: new value
 * @data_ptr: struct of the program's data
 * Return: 1 if the parameters are NULL, 2 if there is an erroror 0 if sucess.
 */

int env_ky_st(char *ky, char *val, prog_s_data *data_ptr)
{
	int i, ky_len = 0, nu_ky = 1;

	/* validate the arguments */
	if (ky == NULL || val == NULL || data_ptr->envirmnt == NULL)
		return (1);

	/* obtains the leng of the variable requested */
	ky_len = string_len(ky);

	for (i = 0; data_ptr->envirmnt[i]; i++)
	{/* Iterates through the environ and check for coincidence of the vame */
		if (string_cmpr(ky, data_ptr->envirmnt[i], ky_len) &&
		 data_ptr->envirmnt[i][ky_len] == '=')
		{/* If key already exists */
			nu_ky = 0;
			/* free the entire variable, it is new created below */
			free(data_ptr->envirmnt[i]);
			break;
		}
	}
	/* make an string of the form key=value */
	data_ptr->envirmnt[i] = string_conc(string_dup(ky), "=");
	data_ptr->envirmnt[i] = string_conc(data_ptr->envirmnt[i], val);

	if (nu_ky)
	{/* if the variable is new, it is create at end of actual list and we need*/
	/* to put the NULL value in the next position */
		data_ptr->envirmnt[i + 1] = NULL;
	}
	return (0);
}

/**
 * env_ky_rm - remove a key from the environment
 * @ky: the key to remove
 * @data_ptr: the sructure of the program's data
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
 * prnt_env - prints the current environ
 * @data_ptr: struct for the program's data
 * Return: nothing
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
