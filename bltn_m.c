#include "shell.h"

/**
 * bltn_xt - program exit with the current status
 * @data_ptr: the pointer of the program's data
 * Return:If successful, 0; else, a defined number in the arguments
 */
int bltn_xt(prog_s_data *data_ptr)
{
	int j;

	if (data_ptr->tkn[1] != NULL)
	{
		for (j = 0; data_ptr->tkn[1][j]; j++)
			if ((data_ptr->tkn[1][j] < '0' || data_ptr->tkn[1][j] > '9')
				&& data_ptr->tkn[1][j] != '+')
			{
				errno = 2;
				return (2);
			}
		errno = _arr_to_int(data_ptr->tkn[1]);
	}
	free_all(data_ptr);
	exit(errno);
}

/**
 * bltn_cd - the current directory be modified
 * @data_ptr: the pointer of the program's data
 * Return: If successful, 0; else, a defined number in the arguments
 */
int bltn_cd(prog_s_data *data_ptr)
{
	char *home_dir = env_ky_gt("HOME", data_ptr), *old_dir = NULL;
	char oldd_dir[128] = {0};
	int err_code = 0;

	if (data_ptr->tkn[1])
	{
		if (string_cmpr(data_ptr->tkn[1], "-", 0))
		{
			old_dir = env_ky_gt("OLDPWD", data_ptr);
			if (old_dir)
				err_code = st_wrkn_dir(data_ptr, old_dir);
			_print_str(env_ky_gt("PWD", data_ptr));
			_print_str("\n");

			return (err_code);
		}
		else
		{
			return (st_wrkn_dir(data_ptr, data_ptr->tkn[1]));
		}
	}
	else
	{
		if (!home_dir)
			home_dir = getcwd(oldd_dir, 128);

		return (st_wrkn_dir(data_ptr, home_dir));
	}
	return (0);
}

/**
 * st_wrkn_dir - the work directory setting
 * @data_ptr: the pointer of the program's data
 * @nu_dir: set the work directory path
 * Return: If successful, 0; else, a defined number in the arguments
 */
int st_wrkn_dir(prog_s_data *data_ptr, char *nu_dir)
{
	char oldd_dir[128] = {0};
	int err_code = 0;

	getcwd(oldd_dir, 128);

	if (!string_cmpr(oldd_dir, nu_dir, 0))
	{
		err_code = chdir(nu_dir);
		if (err_code == -1)
		{
			errno = 2;
			return (3);
		}
		env_ky_st("PWD", nu_dir, data_ptr);
	}
	env_ky_st("OLDPWD", oldd_dir, data_ptr);
	return (0);
}

/**
 * bltn_hlp - displays the environment in which the shell is running.
 * @data_ptr: the pointer of the program's data
 * Return: if successful, 0; else, a other number in the arguments
 */
int bltn_hlp(prog_s_data *data_ptr)
{
	int i, len = 0;
	char *mensj[6] = {NULL};

	mensj[0] = HELP_;

	/* validate args */
	if (data_ptr->tkn[1] == NULL)
	{
		_print_str(mensj[0] + 6);
		return (1);
	}
	if (data_ptr->tkn[2] != NULL)
	{
		errno = E2BIG;
		perror(data_ptr->cmd_name);
		return (5);
	}
	mensj[1] = EXIT_HELP;
	mensj[2] = ENV_HELP;
	mensj[3] = SETENV_HELP;
	mensj[4] = UNSETENV_HELP;
	mensj[5] = CD_HELP;

	for (i = 0; mensj[i]; i++)
	{
		len = string_len(data_ptr->tkn[1]);
		if (string_cmpr(data_ptr->tkn[1], mensj[i], len))
		{
			_print_str(mensj[i] + len + 1);
			return (1);
		}
	}
	errno = EINVAL;
	perror(data_ptr->cmd_name);
	return (0);
}

/**
 * bltn_alias - Add, delete, or display aliases
 * @data_ptr: the pointer of the program's data
 * Return: if successful, 0; else, a other number in the arguments
 */
int bltn_alias(prog_s_data *data_ptr)
{
	int k = 0;

	if (data_ptr->tkn[1] == NULL)
		return (print_alias(data_ptr, NULL));

	while (data_ptr->tkn[++k])
	{
		if (char_counter(data_ptr->tkn[k], "="))
			set_alias(data_ptr->tkn[k], data_ptr);
		else
			print_alias(data_ptr, data_ptr->tkn[k]);
	}

	return (0);
}
