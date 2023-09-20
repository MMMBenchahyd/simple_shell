#include "shell.h"

/**
 * _print_str - writes array of characters in the std output
 * @str: pointer to the array of characters
 * Return: the number of all bytes being writed,
 * else return -1, and errno is set appropriately.
 */
int _print_str(char *str)
{
	return (write(STDOUT_FILENO, str, string_len(str)));
}
/**
 * _print_e - writes an array of charrs in the std error
 * @str: a pointer to the array of characters
 * Return: the number of all bytes being writed,
 * if errors, return -1, and errno is set appropriately.
 */
int _print_e(char *str)
{
	return (write(STDERR_FILENO, str, string_len(str)));
}

/**
 * _print_err - writes an array of characters in the std error
 * @data_ptr: a pointer to the data of the program
 * @err: the error code to be printed
 * Return: the number of all bytes being writed, or
 * if errors, return -1, and errno is set appropriately.
 */
int _print_err(int err, prog_s_data *data_ptr)
{
	char itn_as_str[10] = {'\0'};

	numb_to_str((long) data_ptr->execut_count, itn_as_str, 10);

	if (err == 2 || err == 3)
	{
		_print_e(data_ptr->name_of_prog);
		_print_e(": ");
		_print_e(itn_as_str);
		_print_e(": ");
		_print_e(data_ptr->tkn[0]);
		if (err == 2)
			_print_e(": Illegal number: ");
		else
			_print_e(": can't cd to ");
		_print_e(data_ptr->tkn[1]);
		_print_e("\n");
	}
	else if (err == 127)
	{
		_print_e(data_ptr->name_of_prog);
		_print_e(": ");
		_print_e(itn_as_str);
		_print_e(": ");
		_print_e(data_ptr->cmd_name);
		_print_e(": not found\n");
	}
	else if (err == 126)
	{
		_print_e(data_ptr->name_of_prog);
		_print_e(": ");
		_print_e(itn_as_str);
		_print_e(": ");
		_print_e(data_ptr->cmd_name);
		_print_e(": Permission denied\n");
	}
	return (0);
}
