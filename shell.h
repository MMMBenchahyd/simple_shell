#ifndef SHELL_H
#define SHELL_H

#include <stdio.h> /* biblio for printf*/
#include <unistd.h> /* biblio for fork and execve*/
#include <stdlib.h>
#include <string.h> /*biblio for strtok*/
#include <stddef.h>
#include <errno.h> /* biblio for errno and perror use */
#include <sys/types.h> /* biblio for type pid */
#include <sys/wait.h> /* biblio for wait */
#include <sys/stat.h> /* biblio for use of stat function */
#include <signal.h> /* signal management biblio */
#include <fcntl.h> /* biblio for open files */

/*************** MACROS ****************/

#include "macros.h" /* for help and prompt */

/************* STRUCTURES **************/

/**
 * struct informations - structr for the data of the program
 * @name_of_prog: the executable name
 * @in_ln: ptr to the input read for _getline func
 * @cmd_name: pointer to the user first typed command
 * @execut_count: count the number of excecuted comands
 * @fil_dscription: input of commands file's descriptor
 * @tkn: pointer to an array of tokenized inputs
 * @envirmnt: the environ copy process
 * @lst_of_alias: an array of pionterz with aliases.
 */
typedef struct informations
{
	char *name_of_prog;
	char *in_ln;
	char *cmd_name;
	int execut_count;
	int fil_dscription;
	char **tkn;
	char **envirmnt;
	char **lst_of_alias;
} prog_s_data;

/**
 * struct builtins - structure for the builtin s
 * @bltn: the builtin name
 * @func: the associated func called for each builtins
 */
typedef struct builtins
{
	char *bltn;
	int (*func)(prog_s_data *data_ptr);
} bltns;


/************* MAIN FUNCTIIONS *************/


/*=========  main.c  =========*/

/* the struct initializer with the info of the program */
void ini_the_data(prog_s_data *data_ptr, int arc, char *argv[], char **env);

/* the infiniteloop maker that shows the prompt */
void inf_loop_rn(char *prmt, prog_s_data *data_ptr);

/* Printing the prompt in a new single line */
void ctrl_c_handler(int opr UNUSED);


/*========  _getln.c  ========*/

/* Read a single one line of the std input*/
int _getln(prog_s_data *data_ptr);

/* split every line, if it exist, for the logical opeerators  */
int chk_for_logic_oprts(char *arr_cmnd[], int i, char arr_opr[]);


/*======== expansions.c ========*/

/* variables expanding */
void xpnd_var(prog_s_data *data_ptr);

/* aliases expanding */
void xpnd_alias(prog_s_data *data_ptr);

/* string appending to the end of the bufferr */
int buf_ad(char *buf, char *str_add);


/*======== str_tok.c ========*/

/* string separating in tokens by using designed deliimiter */
void _tkniz(prog_s_data *data_ptr);

/* pointer creating to a part of the strinng */
char *ben_string_tok(char *l, char *dr);


/*======== execute.c ========*/

/* command executing with the entire path of it*/
int exect(prog_s_data *data_ptr);


/*======== bltn_lst.c ========*/

/* executes it if thier is a builtin match */
int bltn_lst(prog_s_data *data_ptr);


/*======== find_in_path.c ========*/

/* an array  creation of the directorie's path */
char **tokniz_the_path(prog_s_data *data_ptr);

/* in path searsh for the program */
int find_th_prog(prog_s_data *data_ptr);


/************** FUNCTIONSS FOR MEMORYY MANAGEMENT **************/


/*======== functions_free.c ========*/

/* will Frees the needed memory for directories */
void free_arr_ptrs(char **arr);

/* will free the field s needed for each loop */
void free_thr_data(prog_s_data *data_ptr);

/* Free or clean all field s of the data */
void free_all(prog_s_data *data_ptr);


/************** BUILTTINS **************/


/*======== builtins_more.c ========*/

/* Close close the shell */
int bltn_xt(prog_s_data *data_ptr);

/* will Change the current directory */
int bltn_cd(prog_s_data *data_ptr);

/* will set the working directory */
int st_wrkn_dir(prog_s_data *data_ptr, char *nu_dir);

/* show help infos */
int bltn_hlp(prog_s_data *data_ptr);

/* set , show and unset alias */
int bltn_alias(prog_s_data *data_ptr);


/*======== bltn_env.c ========*/

/* Show s the envir where the shell runs */
int bltn_env(prog_s_data *data_ptr);

/* override or createa variable of envir */
int bltn_st_env(prog_s_data *data_ptr);

/* a variable deleter of envir */
int bltn_nst_env(prog_s_data *data_ptr);


/************** HELPERSs FOR ENVIRONMENT VARIABLES MANAGEMENT **************/


/*========= env_management.c =========*/

/* Gets the value of an envir var */
char *env_ky_gt(char *name, prog_s_data *data_ptr);

/* Overwrite the value of the envir variab */
int env_ky_st(char *ky, char *val, prog_s_data *data_ptr);

/* a key remover from the envir */
int env_ky_rm(char *ky, prog_s_data *data_ptr);

/* it prints the current envir */
void prnt_env(prog_s_data *data_ptr);


/************** HELPERS FOR PRINTING **************/


/*========= helpers_print.c =========*/

/* string printer in the std output */
int _print_str(char *str);

/* string printer in the std error */
int _print_e(char *str);

/* string printer in the std error */
int _print_err(int err, prog_s_data *data_ptr);


/**************** HELPERSs FOR STRINGS MANAGEMENT ****************/


/*========= helpers_string.c =========*/

/* characters counter of a string */
int string_len(char *str);

/* string duplicater */
char *string_dup(char *str);

/* this will Compares two strings */
int string_cmpr(char *str1, char *str2, int numb);

/* two strings Concatenator */
char *string_conc(char *str1, char *str2);

/* string reverser */
void string_rev(char *str);


/*========= helpers_numbers.c =========*/

/* from int to string casting */
void numb_to_str(long num, char *str, int b);

/* from a string to a number converter */
int _arr_to_int(char *str);

/* the coincidences of a char counter in string */
int char_counter(char *s, char *c);


/*========= alias_management.c =========*/

/* it prints alist of alias */
int print_alias(prog_s_data *data_ptr, char *alias);

/* get the name of an alias */
char *get_alias(prog_s_data *data_ptr, char *alias);

/* set the name of an alias */
int set_alias(char *alias_string, prog_s_data *data_ptr);


#endif /* SHELL_H */
