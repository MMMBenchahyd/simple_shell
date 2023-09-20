#include "shell.h"

/**
 * bltn_lst - search for match and execute the associate builtin
 * @data_ptr: struct for the program's data
 * Return: Returns the return of the function executed is there is a match,
 * otherwise returns -1.
 **/
int bltn_lst(prog_s_data *data_ptr)
{
	int i;
	bltns opts[] = {
		{"exit", bltn_xt},
		{"help", bltn_hlp},
		{"cd", bltn_cd},
		{"alias", bltn_alias},
		{"env", bltn_env},
		{"setenv", bltn_st_env},
		{"unsetenv", bltn_nst_env},
		{NULL, NULL}
	};

/*walk through the structure*/
	for (i = 0; opts[i].bltn != NULL; i++)
	{
/*if there is a match between the given command and a builtin,*/
		if (string_cmpr(opts[i].bltn, data_ptr->cmd_name, 0))
		{
/*execute the function, and return the return value of the function*/
			return (opts[i].func(data_ptr));
		}
/*if there is no match return -1 */
	}
	return (-1);
}
