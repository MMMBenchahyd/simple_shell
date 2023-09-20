#include "shell.h"

int file_chk(char *ful_pth);

/**
 * find_th_prog - find a program in path
 * @data_ptr: a pointer to the program's data
 * Return: 0 if success, errcode otherwise
 */

int find_th_prog(prog_s_data *data_ptr)
{
	int i = 0, re_c = 0;
	char **dirs;

	if (!data_ptr->cmd_name)
		return (2);

	/**if is a full_path or an executable in the same path */
	if (data_ptr->cmd_name[0] == '/' || data_ptr->cmd_name[0] == '.')
		return (file_chk(data_ptr->cmd_name));

	free(data_ptr->tkn[0]);
	data_ptr->tkn[0] = string_conc(string_dup("/"), data_ptr->cmd_name);
	if (!data_ptr->tkn[0])
		return (2);

	dirs = tokniz_the_path(data_ptr);/* search in the PATH */

	if (!dirs || !dirs[0])
	{
		errno = 127;
		return (127);
	}
	for (i = 0; dirs[i]; i++)
	{/* appends the function_name to path */
		dirs[i] = string_conc(dirs[i], data_ptr->tkn[0]);
		re_c = file_chk(dirs[i]);
		if (re_c == 0 || re_c == 126)
		{/* the file was found, is not a directory and has execute permisions*/
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
 * tokniz_the_path - tokenize the path in directories
 * @data_ptr: a pointer to the program's data
 * Return: array of path directories
 */

char **tokniz_the_path(prog_s_data *data_ptr)
{
	int i = 0;
	int count_dir = 2;
	char **tkn = NULL;
	char *PTH;

	/* get the PATH value*/
	PTH = env_ky_gt("PATH", data_ptr);
	if ((PTH == NULL) || PTH[0] == '\0')
	{/*path not found*/
		return (NULL);
	}

	PTH = string_dup(PTH);

	/* find the number of directories in the PATH */
	for (i = 0; PTH[i]; i++)
	{
		if (PTH[i] == ':')
			count_dir++;
	}

	/* reserve space for the array of pointers */
	tkn = malloc(sizeof(char *) * count_dir);

	/*tokenize and duplicate each token of path*/
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
 * file_chk - checks if exists a file, if it is not a dairectory and
 * if it has excecution permisions for permisions.
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
	/*if not exist the file*/
	errno = 127;
	return (127);
}
