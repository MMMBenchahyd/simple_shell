#include "shell.h"
/**
 * main - initialize the variables of the program
 * @argc: number of values received from the command line
 * @argv: values received from the command line
 * @env: number of values received from the command line
 * Return: zero on succes.
 */
int main(int argc, char *argv[], char *env[])
{
	prog_s_data _structt = {NULL}, *data_ptr = &_structt;
	char *prmt = "";

	ini_the_data(data_ptr, argc, argv, env);

	signal(SIGINT, ctrl_c_handler);

	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && argc == 1)
	{/* We are in the terminal, interactive mode */
		errno = 2;
		prmt = PROMPT;
	}
	errno = 0;
	inf_loop_rn(prmt, data_ptr);
	return (0);
}

/**
 * ctrl_c_handler - print the prompt in a new line
 * when the signal SIGINT (ctrl + c) is send to the program
 * @UNUSED: option of the prototype
 */
void ctrl_c_handler(int opr UNUSED)
{
	_print_str("\n");
	_print_str(PROMPT);
}

/**
 * ini_the_data - inicialize the struct with the info of the program
 * @data_ptr: pointer to the structure of data
 * @argv: array of arguments pased to the program execution
 * @env: environ pased to the program execution
 * @argc: number of values received from the command line
 */
void ini_the_data(prog_s_data *data_ptr, int argc, char *argv[], char **env)
{
	int i = 0;

	data_ptr->name_of_prog = argv[0];
	data_ptr->in_ln = NULL;
	data_ptr->cmd_name = NULL;
	data_ptr->execut_count = 0;
	/* define the file descriptor to be readed*/
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
 * inf_loop_rn - its a infinite loop that shows the prompt
 * @prmt: prompt to be printed
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
			exit(errno); /* if EOF is the fisrt Char of string, exit*/
		}
		if (str_lent >= 1)
		{
			xpnd_alias(data_ptr);
			xpnd_var(data_ptr);
			_tkniz(data_ptr);
			if (data_ptr->tkn[0])
			{ /* if a text is given to prompt, execute */
				err_c = exect(data_ptr);
				if (err_c != 0)
					_print_err(err_c, data_ptr);
			}
			free_thr_data(data_ptr);
		}
	}
}
