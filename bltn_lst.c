#include "shell.h"

/**
 * bltn_lst - find a match, then use the built-in association
 * @data_ptr: the pointer of the program's data
 * Return: If a match is found, the function's return value
 * is returned; otherwise, -1 is returned.
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

	for (i = 0; opts[i].bltn != NULL; i++)
	{
		if (string_cmpr(opts[i].bltn, data_ptr->cmd_name, 0))
		{
			return (opts[i].func(data_ptr));
		}
	}
	return (-1);
}
