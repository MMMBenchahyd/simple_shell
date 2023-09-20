#include "shell.h"

/**
 * print_alias - this func show, add, or remove aliases
 * @data_ptr: this struct is for the data of  program's
 * @alias: the name of the alias that will be printed
 * Return: rtrn 0 if sucess, other number if it declared in the arguments
 */
int print_alias(prog_s_data *data_ptr, char *alias)
{
	int i, j, alias_len;
	char buf[250] = {'\0'};

	if (data_ptr->lst_of_alias)
	{
		alias_len = string_len(alias);
		for (i = 0; data_ptr->lst_of_alias[i]; i++)
		{
			if (!alias || (string_cmpr(data_ptr->lst_of_alias[i], alias, alias_len)
				&&	data_ptr->lst_of_alias[i][alias_len] == '='))
			{
				for (j = 0; data_ptr->lst_of_alias[i][j]; j++)
				{
					buf[j] = data_ptr->lst_of_alias[i][j];
					if (data_ptr->lst_of_alias[i][j] == '=')
						break;
				}
				buf[j + 1] = '\0';
				buf_ad(buf, "'");
				buf_ad(buf, data_ptr->lst_of_alias[i] + j + 1);
				buf_ad(buf, "'\n");
				_print_str(buf);
			}
		}
	}

	return (0);
}

/**
 * get_alias - this will  add,show or  remove aliases
 * @data_ptr: this struct for the data of the program
 * @name: the name of the main requested alias
 * Return: rtrn 0 if sucess, other number if it was declared in the arguments
 */
char *get_alias(prog_s_data *data_ptr, char *name)
{
	int i, alias_len;

	if (name == NULL || data_ptr->lst_of_alias == NULL)
		return (NULL);

	alias_len = string_len(name);

	for (i = 0; data_ptr->lst_of_alias[i]; i++)
	{
		if (string_cmpr(name, data_ptr->lst_of_alias[i], alias_len) &&
			data_ptr->lst_of_alias[i][alias_len] == '=')
		{
			return (data_ptr->lst_of_alias[i] + alias_len + 1);
		}
	}
	return (NULL);

}

/**
 * set_alias - this  will add or override alias
 * @alias_string: the alias that will be seted in the form name='value' )
 * @data_ptr: this struct is  for the program's data
 * Return: rtrn 0 if sucess, other number if it declared in the arguments
 */

int set_alias(char *alias_string, prog_s_data *data_ptr)
{
	int i, j;
	char buf[250] = {'0'}, *temp = NULL;

	if (alias_string == NULL ||  data_ptr->lst_of_alias == NULL)
		return (1);

	for (i = 0; alias_string[i]; i++)
		if (alias_string[i] != '=')
			buf[i] = alias_string[i];
		else
		{
			temp = get_alias(data_ptr, alias_string + i + 1);
			break;
		}

	for (j = 0; data_ptr->lst_of_alias[j]; j++)
		if (string_cmpr(buf, data_ptr->lst_of_alias[j], i) &&
			data_ptr->lst_of_alias[j][i] == '=')
		{
			free(data_ptr->lst_of_alias[j]);
			break;
		}

	if (temp)
	{
		buf_ad(buf, "=");
		buf_ad(buf, temp);
		data_ptr->lst_of_alias[j] = string_dup(buf);
	}
	else
		data_ptr->lst_of_alias[j] = string_dup(alias_string);
	return (0);
}
