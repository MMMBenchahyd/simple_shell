#include "shell.h"
/**
 * main - initialize the program's variables
 * @argc: the quantity of values from the command line
 * @argv: from the command line values
 * @env: the quantity of values from the command line
 * Return: 0 if succes.
 */
int main(int argc, char *argv[], char *env[])
{
	prog_s_data _structt = {NULL}, *data_ptr = &_structt;
	char *prmt = "";

	ini_the_data(data_ptr, argc, argv, env);

	signal(SIGINT, ctrl_c_handler);

	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && argc == 1)
	{
		errno = 2;
		prmt = PROMPT;
	}
	errno = 0;
	inf_loop_rn(prmt, data_ptr);
	return (0);
}

/**
 * ctrl_c_handler - the command should appear on a new line.
 * when the program receives the signal SIGINT (ctrl + c)
 * @UNUSED: alternative to the prototype
 */
void ctrl_c_handler(int opr UNUSED)
{
	_print_str("\n");
	_print_str(PROMPT);
}

/**
 * ini_the_data - initialize the struct with the program's information
 * @data_ptr: pointer to the structure of data
 * @argv: array of arguments passed to the execution of the program
 * @env: environment passed before running the program
 * @argc: the quantity of values from the command line
 */
void ini_the_data(prog_s_data *data_ptr, int argc, char *argv[], char **env)
{
	int i = 0;

	data_ptr->name_of_prog = argv[0];
	data_ptr->in_ln = NULL;
	data_ptr->cmd_name = NULL;
	data_ptr->execut_count = 0;

	if (argc == 1)
		data_ptr->fil_dscription = STDIN_FILENO;
	else
	{
		data_ptr->fil_dscription = open(argv[1], O_RDONLY);
		if (data_ptr->fil_dscription == -1)
		{
			_print_e(data_ptr->name_of_prog);
			_print_e(": 0: Can't open ");
			_print_e(argv[1]);
			_print_e("\n");
			exit(127);
		}
	}
	data_ptr->tkn = NULL;
	data_ptr->envirmnt = malloc(sizeof(char *) * 50);
	if (env)
	{
		for (; env[i]; i++)
		{
			data_ptr->envirmnt[i] = string_dup(env[i]);
		}
	}
	data_ptr->envirmnt[i] = NULL;
	env = data_ptr->envirmnt;

	data_ptr->lst_of_alias = malloc(sizeof(char *) * 20);
	for (i = 0; i < 20; i++)
	{
		data_ptr->lst_of_alias[i] = NULL;
	}
}
/**
 * inf_loop_rn - It displays the prompt in an unending loop.
 * @prmt: prompting printing
 * @data_ptr: its a pointer to data
 */
void inf_loop_rn(char *prmt, prog_s_data *data_ptr)
{
	int err_c = 0, str_lent = 0;

	while (++(data_ptr->execut_count))
	{
		_print_str(prmt);
		err_c = str_lent = _getln(data_ptr);

		if (err_c == EOF)
		{
			free_all(data_ptr);
			exit(errno);
		}
		if (str_lent >= 1)
		{
			xpnd_alias(data_ptr);
			xpnd_var(data_ptr);
			_tkniz(data_ptr);
			if (data_ptr->tkn[0])
			{
				err_c = exect(data_ptr);
				if (err_c != 0)
					_print_err(err_c, data_ptr);
			}
			free_thr_data(data_ptr);
		}
	}
}
