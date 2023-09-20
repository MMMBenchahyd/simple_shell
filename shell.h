#ifndef SHELL_H
#define SHELL_H

#include <stdio.h> /* for printf*/
#include <unistd.h> /* for fork, execve*/
#include <stdlib.h>
#include <string.h> /* for strtok*/
#include <stddef.h>
#include <errno.h> /* for errno and perror */
#include <sys/types.h> /* for type pid */
#include <sys/wait.h> /* for wait */
#include <sys/stat.h> /* for use of stat function */
#include <signal.h> /* for signal management */
#include <fcntl.h> /* for open files*/

/************* MACROS **************/

#include "macros.h" /* for help and prompt */

/************* STRUCTURES **************/

/**
 * struct info- struct for the program's data
 * @name_of_prog: the name of the executable
 * @in_ln: pointer to the input read for _getline
 * @cmd_name: pointer to the first command typed by the user
 * @exec_counter: number of excecuted comands
 * @fil_dscription: file descriptor to the input of commands
 * @tkn: pointer to array of tokenized input
 * @envirmnt: copy of the environ
 * @lst_of_alias: array of pointers with aliases.
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
 * struct builtins - struct for the builtins
 * @builtin: the name of the builtin
 * @function: the associated function to be called for each builtin
 */
typedef struct builtins
{
	char *bltn;
	int (*func)(prog_s_data *data_ptr);
} bltns;


/************* MAIN FUNCTIONS *************/


/*========  main.c  ========*/

/* Inicialize the struct with the info of the program */
void ini_the_data(prog_s_data *data_ptr, int arc, char *argv[], char **env);

/* Makes the infinite loop that shows the prompt*/
void inf_loop_rn(char *prmt, prog_s_data *data_ptr);

/* Print the prompt in a new line */
void ctrl_c_handler(int opr UNUSED);


/*========  _gtln.c  ========*/

/* Read one line of the standar input*/
int _getln(prog_s_data *data_ptr);

/* split the each line for the logical operators if it exist */
int chk_for_logic_oprts(char *arr_cmnd[], int i, char arr_opr[]);


/*======== expansions.c ========*/

/* expand variables */
void xpnd_var(prog_s_data *data_ptr);

/* expand aliases */
void xpnd_alias(prog_s_data *data_ptr);

/* append the string to the end of the buffer*/
int buf_ad(char *buf, char *str_add);


/*======== str_tok.c ========*/

/* Separate the string in tokens using a designed delimiter */
void _tkniz(prog_s_data *data_ptr);

/* Creates a pointer to a part of a string */
char *ben_string_tok(char *l, char *dr);


/*======== execute.c ========*/

/* Execute a command with its entire path */
int exect(prog_s_data *data_ptr);


/*======== bltn_lst.c ========*/

/* If match a builtin, executes it */
int bltn_lst(prog_s_data *data_ptr);


/*======== find_in_path.c ========*/

/* Creates an array of the path directories */
char **tokniz_the_path(prog_s_data *data_ptr);

/* Search for program in path */
int find_th_prog(prog_s_data *data_ptr);


/************** FUNCTIONS FOR MEMORY MANAGEMENT **************/


/*======== functions_free.c ========*/

/* Frees the memory for directories */
void free_arr_ptrs(char **arr);

/* Free the fields needed each loop */
void free_thr_data(prog_s_data *data_ptr);

/* Free all field of the data */
void free_all(prog_s_data *data_ptr);


/************** BUILTINS **************/


/*======== builtins_more.c ========*/

/* Close the shell */
int bltn_xt(prog_s_data *data_ptr);

/* Change the current directory */
int bltn_cd(prog_s_data *data_ptr);

/* set the work directory */
int st_wrkn_dir(prog_s_data *data_ptr, char *nu_dir);

/* show help information */
int bltn_hlp(prog_s_data *data_ptr);

/* set, unset and show alias */
int bltn_alias(prog_s_data *data_ptr);


/*======== bltn_env.c ========*/

/* Shows the environment where the shell runs */
int bltn_env(prog_s_data *data_ptr);

/* create or override a variable of environment */
int bltn_st_env(prog_s_data *data_ptr);

/* delete a variable of environment */
int bltn_nst_env(prog_s_data *data_ptr);


/************** HELPERS FOR ENVIRONMENT VARIABLES MANAGEMENT **************/


/*======== env_management.c ========*/

/* Gets the value of an environment variable */
char *env_ky_gt(char *name, prog_s_data *data_ptr);

/* Overwrite the value of the environment variable */
int env_ky_st(char *ky, char *val, prog_s_data *data_ptr);

/* Remove a key from the environment */
int env_ky_rm(char *ky, prog_s_data *data_ptr);

/* prints the current environ */
void prnt_env(prog_s_data *data_ptr);


/************** HELPERS FOR PRINTING **************/


/*======== helpers_print.c ========*/

/* Prints a string in the standar output */
int _print_str(char *str);

/* Prints a string in the standar error */
int _print_e(char *str);

/* Prints a string in the standar error */
int _print_err(int err, prog_s_data *data_ptr);


/************** HELPERS FOR STRINGS MANAGEMENT **************/


/*======== helpers_string.c ========*/

/* Counts the number of characters of a string */
int string_len(char *str);

/* Duplicates an string */
char *string_dup(char *str);

/* Compares two strings */
int string_cmpr(char *str1, char *str2, int numb);

/* Concatenates two strings */
char *string_conc(char *str1, char *str2);

/* Reverse a string */
void string_rev(char *str);


/*======== helpers_numbers.c ========*/

/* Cast from int to string */
void numb_to_str(long num, char *str, int b);

/* convert an string in to a number */
int _arr_to_int(char *str);

/* count the coincidences of character in string */
int char_counter(char *s, char *c);


/*======== alias_management.c ========*/

/* print the list of alias */
int print_alias(prog_s_data *data_ptr, char *alias);

/* get the alias name */
char *get_alias(prog_s_data *data_ptr, char *alias);

/* set the alias name */
int set_alias(char *alias_string, prog_s_data *data_ptr);


#endif /* SHELL_H */
