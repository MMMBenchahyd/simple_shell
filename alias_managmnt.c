#include "shell.h"

/**
 * print_alias - add, remove or show aliases
 * @data_ptr: struct for the program's data
 * @alias: name of the alias to be printed
 * Return: zero if sucess, or other number if its declared in the arguments
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
 * get_alias - add, remove or show aliases
 * @data_ptr: struct for the program's data
 * @name: name of the requested alias.
 * Return: zero if sucess, or other number if its declared in the arguments
 */
char *get_alias(prog_s_data *data_ptr, char *name)
{
	int i, alias_len;

	/* validate the arguments */
	if (name == NULL || data_ptr->lst_of_alias == NULL)
		return (NULL);

	alias_len = string_len(name);

	for (i = 0; data_ptr->lst_of_alias[i]; i++)
	{/* Iterates through the environ and check for coincidence of the varname */
		if (string_cmpr(name, data_ptr->lst_of_alias[i], alias_len) &&
			data_ptr->lst_of_alias[i][alias_len] == '=')
		{/* returns the value of the key NAME=  when find it */
			return (data_ptr->lst_of_alias[i] + alias_len + 1);
		}
	}
	/* returns NULL if did not find it */
	return (NULL);

}

/**
 * set_alias - add, or override alias
 * @alias_string: alias to be seted in the form (name='value')
 * @data_ptr: struct for the program's data
 * Return: zero if sucess, or other number if its declared in the arguments
 */
int set_alias(char *alias_string, prog_s_data *data_ptr)
{
	int i, j;
	char buf[250] = {'0'}, *temp = NULL;

	/* validate the arguments */
	if (alias_string == NULL ||  data_ptr->lst_of_alias == NULL)
		return (1);
	/* Iterates alias to find = char */
	for (i = 0; alias_string[i]; i++)
		if (alias_string[i] != '=')
			buf[i] = alias_string[i];
		else
		{/* search if the value of the alias is another alias */
			temp = get_alias(data_ptr, alias_string + i + 1);
			break;
		}

	/* Iterates through the alias list and check for coincidence of the varname */
	for (j = 0; data_ptr->lst_of_alias[j]; j++)
		if (string_cmpr(buf, data_ptr->lst_of_alias[j], i) &&
			data_ptr->lst_of_alias[j][i] == '=')
		{/* if the alias alredy exist */
			free(data_ptr->lst_of_alias[j]);
			break;
		}

	/* add the alias */
	if (temp)
	{/* if the alias already exist */
		buf_ad(buf, "=");
		buf_ad(buf, temp);
		data_ptr->lst_of_alias[j] = string_dup(buf);
	}
	else /* if the alias does not exist */
		data_ptr->lst_of_alias[j] = string_dup(alias_string);
	return (0);
}
