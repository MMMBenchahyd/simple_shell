#include "shell.h"

/**
 * free_thr_data - in every loop frees the necessary fields
 * @data_ptr: structure for the data of the program
 * Return: void return i.e nothing
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
 * free_all - free every field of the data
 * @data_ptr: structure for the data of the program
 * Return: void return i.e nothing
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
 * free_arr_ptrs - it frees all pointers of a pointers arrays and
 * and also the array
 * @arr: this is an array of pionters
 * Return: void return i.e nothing
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
