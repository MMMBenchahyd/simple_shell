#include "shell.h"

/**
 * xpnd_var - this func expand the variables
 * @data_ptr: ptr to a structure for the data of the program
 *
 * Return: it sets errno but return nothing.
 */
void xpnd_var(prog_s_data *data_ptr)
{
	int i, j;
	char ln[BUFFER_SIZE] = {0}, expan[BUFFER_SIZE] = {'\0'}, *tmp;

	if (data_ptr->in_ln == NULL)
		return;
	buf_ad(ln, data_ptr->in_ln);
	for (i = 0; ln[i]; i++)
		if (ln[i] == '#')
			ln[i--] = '\0';
		else if (ln[i] == '$' && ln[i + 1] == '?')
		{
			ln[i] = '\0';
			numb_to_str(errno, expan, 10);
			buf_ad(ln, expan);
			buf_ad(ln, data_ptr->in_ln + i + 2);
		}
		else if (ln[i] == '$' && ln[i + 1] == '$')
		{
			ln[i] = '\0';
			numb_to_str(getpid(), expan, 10);
			buf_ad(ln, expan);
			buf_ad(ln, data_ptr->in_ln + i + 2);
		}
		else if (ln[i] == '$' && (ln[i + 1] == ' ' || ln[i + 1] == '\0'))
			continue;
		else if (ln[i] == '$')
		{
			for (j = 1; ln[i + j] && ln[i + j] != ' '; j++)
				expan[j - 1] = ln[i + j];
			tmp = env_ky_gt(expan, data_ptr);
			ln[i] = '\0', expan[0] = '\0';
			buf_ad(expan, ln + i + j);
			tmp ? buf_ad(ln, tmp) : 1;
			buf_ad(ln, expan);
		}
	if (!string_cmpr(data_ptr->in_ln, ln, 0))
	{
		free(data_ptr->in_ln);
		data_ptr->in_ln = string_dup(ln);
	}
}

/**
 * xpnd_alias - function to expands all aliases
 * @data_ptr: ptr to a structure for the data of the program
 *
 * Return: it sets errno but return nothing.
 */
void xpnd_alias(prog_s_data *data_ptr)
{
	int i, j, ws_expndd = 0;
	char ln[BUFFER_SIZE] = {0}, expan[BUFFER_SIZE] = {'\0'}, *tmp;

	if (data_ptr->in_ln == NULL)
		return;

	buf_ad(ln, data_ptr->in_ln);

	for (i = 0; ln[i]; i++)
	{
		for (j = 0; ln[i + j] && ln[i + j] != ' '; j++)
			expan[j] = ln[i + j];
		expan[j] = '\0';

		tmp = get_alias(data_ptr, expan);
		if (tmp)
		{
			expan[0] = '\0';
			buf_ad(expan, ln + i + j);
			ln[i] = '\0';
			buf_ad(ln, tmp);
			ln[string_len(ln)] = '\0';
			buf_ad(ln, expan);
			ws_expndd = 1;
		}
		break;
	}
	if (ws_expndd)
	{
		free(data_ptr->in_ln);
		data_ptr->in_ln = string_dup(ln);
	}
}

/**
 * buf_ad - this func will append string at end of the buffer
 * @buf: to be filled up buffer
 * @str_add: to be copied string in the buffer
 * Return: it sets errno but return nothing.
 */
int buf_ad(char *buf, char *str_add)
{
	int len, i;

	len = string_len(buf);
	for (i = 0; str_add[i]; i++)
	{
		buf[len + i] = str_add[i];
	}
	buf[len + i] = '\0';
	return (len + i);
}
