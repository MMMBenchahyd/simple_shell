#include "shell.h"

/**
 * bltn_env - displays the environment in which the shell is running.
 * @data_ptr: structure for the data of the program
 * Return: rtrn 0 if sucess, other number if it declared in the arguments
 */
int bltn_env(prog_s_data *data_ptr)
{
	int i;
	char cpn[50] = {'\0'};
	char *var_cp = NULL;

	if (data_ptr->tkn[1] == NULL)
		prnt_env(data_ptr);
	else
	{
		for (i = 0; data_ptr->tkn[1][i]; i++)
		{
			if (data_ptr->tkn[1][i] == '=')
			{
				var_cp = string_dup(env_ky_gt(cpn, data_ptr));
				if (var_cp != NULL)
					env_ky_st(cpn, data_ptr->tkn[1] + i + 1, data_ptr);


				prnt_env(data_ptr);
				if (env_ky_gt(cpn, data_ptr) == NULL)
				{
					_print_str(data_ptr->tkn[1]);
					_print_str("\n");
				}
				else
				{
					env_ky_st(cpn, var_cp, data_ptr);
					free(var_cp);
				}
				return (0);
			}
			cpn[i] = data_ptr->tkn[1][i];
		}
		errno = 2;
		perror(data_ptr->cmd_name);
		errno = 127;
	}
	return (0);
}

/**
 * bltn_st_env - funct that do the job
 * @data_ptr: structure for the data program
 * Return: rtrn 0 if sucess, other number if it declared in the arguments
 */
int bltn_st_env(prog_s_data *data_ptr)
{
	if (data_ptr->tkn[1] == NULL || data_ptr->tkn[2] == NULL)
		return (0);
	if (data_ptr->tkn[3] != NULL)
	{
		errno = E2BIG;
		perror(data_ptr->cmd_name);
		return (5);
	}

	env_ky_st(data_ptr->tkn[1], data_ptr->tkn[2], data_ptr);

	return (0);
}

/**
 * bltn_nst_env - do thier own job taraa
 * @data_ptr: this struct for the data of program
 * Return: rtrn 0 if sucess, other number if it declared in the arguments
 */
int bltn_nst_env(prog_s_data *data_ptr)
{
	if (data_ptr->tkn[1] == NULL)
		return (0);
	if (data_ptr->tkn[2] != NULL)
	{
		errno = E2BIG;
		perror(data_ptr->cmd_name);
		return (5);
	}
	env_ky_rm(data_ptr->tkn[1], data_ptr);

	return (0);
}
