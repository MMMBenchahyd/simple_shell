#include "shell.h"
/**
 * exect - run a command together with all of its path variables.
 * @data_ptr: a pointer to the program's data
 * Return: If sucess returns 0, and if not return -1.
 */
int exect(prog_s_data *data_ptr)
{
	int re_val = 0, stts;
	pid_t pd;

	re_val = bltn_lst(data_ptr);
	if (re_val != -1)
		return (re_val);

	re_val = find_th_prog(data_ptr);
	if (re_val)
	{
		return (re_val);
	}
	else
	{
		pd = fork();
		if (pd == -1)
		{
			perror(data_ptr->cmd_name);
			exit(EXIT_FAILURE);
		}
		if (pd == 0)
		{
			re_val = execve(data_ptr->tkn[0], data_ptr->tkn, data_ptr->envirmnt);
			if (re_val == -1)
				perror(data_ptr->cmd_name), exit(EXIT_FAILURE);
		}
		else
		{
			wait(&stts);
			if (WIFEXITED(stts))
				errno = WEXITSTATUS(stts);
			else if (WIFSIGNALED(stts))
				errno = 128 + WTERMSIG(stts);
		}
	}
	return (0);
}
