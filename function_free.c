#include "shell.h"

/**
 * free_thr_data - free the fields needed each loop
 * @data_ptr: struct of the program's data
 * Return: Nothing
 */
void free_thr_data(prog_s_data *data_ptr)
{
	if (data_ptr->tkn)
		free_arr_ptrs(data_ptr->tkn);
	if (data_ptr->in_ln)
		free(data_ptr->in_ln);
	if (data_ptr->cmd_name)
		free(data_ptr->cmd_name);

	data_ptr->in_ln = NULL;
	data_ptr->cmd_name = NULL;
	data_ptr->tkn = NULL;
}

/**
 * free_all - free all field of the data
 * @data_ptr: struct of the program's data
 * Return: Nothing
 */
void free_all(prog_s_data *data_ptr)
{
	if (data_ptr->fil_dscription != 0)
	{
		if (close(data_ptr->fil_dscription))
			perror(data_ptr->name_of_prog);
	}
	free_thr_data(data_ptr);
	free_arr_ptrs(data_ptr->envirmnt);
	free_arr_ptrs(data_ptr->lst_of_alias);
}

/**
 * free_arr_ptrs - frees each pointer of an array of pointers and the
 * array too
 * @arr: array of pointers
 * Return: nothing
 */
void free_arr_ptrs(char **arr)
{
	int k;

	if (arr != NULL)
	{
		for (k = 0; arr[k]; k++)
			free(arr[k]);

		free(arr);
		arr = NULL;
	}
}
