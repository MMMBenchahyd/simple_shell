#include "shell.h"
/**
 * exect - execute a command with its entire path variables.
 * @data_ptr: a pointer to the program's data
 * Return: If sucess returns zero, otherwise, return -1.
 */
int exect(prog_s_data *data_ptr)
{
	int re_val = 0, stts;
	pid_t pd;

	/* check for program in built ins */
	re_val = bltn_lst(data_ptr);
	if (re_val != -1)/* if program was found in built ins */
		return (re_val);

	/* check for program file system */
	re_val = find_th_prog(data_ptr);
	if (re_val)
	{/* if program not found */
		return (re_val);
	}
	else
	{/* if program was found */
		pd = fork(); /* create a child process */
		if (pd == -1)
		{ /* if the fork call failed */
			perror(data_ptr->cmd_name);
			exit(EXIT_FAILURE);
		}
		if (pd == 0)
		{
			re_val = execve(data_ptr->tkn[0], data_ptr->tkn, data_ptr->envirmnt);
			if (re_val == -1) /* if error when execve*/
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
