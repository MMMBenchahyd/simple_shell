#include "shell.h"

int file_chk(char *ful_pth);

/**
 * find_th_prog - a program in the path
 * @data_ptr: a pointer to the program's data
 * Return: 0 if success, errcode if not.
 */

int find_th_prog(prog_s_data *data_ptr)
{
	int i = 0, re_c = 0;
	char **dirs;

	if (!data_ptr->cmd_name)
		return (2);

	if (data_ptr->cmd_name[0] == '/' || data_ptr->cmd_name[0] == '.')
		return (file_chk(data_ptr->cmd_name));

	free(data_ptr->tkn[0]);
	data_ptr->tkn[0] = string_conc(string_dup("/"), data_ptr->cmd_name);
	if (!data_ptr->tkn[0])
		return (2);

	dirs = tokniz_the_path(data_ptr);

	if (!dirs || !dirs[0])
	{
		errno = 127;
		return (127);
	}
	for (i = 0; dirs[i]; i++)
	{
		dirs[i] = string_conc(dirs[i], data_ptr->tkn[0]);
		re_c = file_chk(dirs[i]);
		if (re_c == 0 || re_c == 126)
		{
			errno = 0;
			free(data_ptr->tkn[0]);
			data_ptr->tkn[0] = string_dup(dirs[i]);
			free_arr_ptrs(dirs);
			return (re_c);
		}
	}
	free(data_ptr->tkn[0]);
	data_ptr->tkn[0] = NULL;
	free_arr_ptrs(dirs);
	return (re_c);
}

/**
 * tokniz_the_path - tokenize directories' paths
 * @data_ptr: a pointer to the program's data
 * Return: path directories array
 */

char **tokniz_the_path(prog_s_data *data_ptr)
{
	int i = 0;
	int count_dir = 2;
	char **tkn = NULL;
	char *PTH;

	PTH = env_ky_gt("PATH", data_ptr);
	if ((PTH == NULL) || PTH[0] == '\0')
	{/*path not found*/
		return (NULL);
	}

	PTH = string_dup(PTH);

	for (i = 0; PTH[i]; i++)
	{
		if (PTH[i] == ':')
			count_dir++;
	}

	tkn = malloc(sizeof(char *) * count_dir);

	i = 0;
	tkn[i] = string_dup(ben_string_tok(PTH, ":"));
	while (tkn[i++])
	{
		tkn[i] = string_dup(ben_string_tok(NULL, ":"));
	}

	free(PTH);
	PTH = NULL;
	return (tkn);

}

/**
 * file_chk - determines whether a file is present, whether it is not 
 * a directory, and whether it has execution permissions.
 * @ful_pth: pointer to the full file name
 * Return: 0 on success, or error code if it exists.
 */

int file_chk(char *ful_pth)
{
	struct stat s_b;

	if (stat(ful_pth, &s_b) != -1)
	{
		if (S_ISDIR(s_b.st_mode) ||  access(ful_pth, X_OK))
		{
			errno = 126;
			return (126);
		}
		return (0);
	}
	errno = 127;
	return (127);
}
