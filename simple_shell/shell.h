#ifndef _SHELL_H_
#define _SHELL_H

#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

/* 0converting number */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2_

/* Check if using system getline() return 1*/
#define USE_GETLINE 0
#define USE_STRTOK 0

/* To read-write buffer */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* To check command chain*/
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;

/**
 * struct liststr - Is a singly linked list
 * @num: Field for number
 * @str: Is a string
 * @next: directs to Nextnode
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
}
list_t;

/**
 * struct passinfo - Holds pseudo-arg to pass into function,
 * allows uniform prototype for function pointer struct
 * @arg:The string generated from getline contains arg
 * @argv:Is array of strings from arg
 * @path: String path for current command
 * @argc: Is arg count
 * @line_count: Gives error counts
 * @err_num: Error code on exit()s
 * @linecount_flag: if on count this line of input
 * @fname: Is filename to Program
 * @env:  local copy linked list of environ
 * @environ: custom modified copy of environ from LL env
 * @history: Node to history
 * @alias: Node for alias
 * @env_changed: When enveron is changed
 * @status: Return status of the last passed command
 * @cmd_buf: address to pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: the fd from which to read line input
 * @histcount: History line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
}
info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
		0, 0, 0}

/**
 * struct builtin - contain builtin string/related function
 * @type: command flag to builtin command
 * @func: Is function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
}
builtin_table;
int hsh(info_t *, char **);
int find_builtin(info_t *);
void find_cmd(info_t *);
void fork_cmd(info_t *);

void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

char *_strcpy(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

int _strlen(char *);
int _strcmp(char *, char *);
char *starts_with(const char *, const char *);
char *_strcat(char *, char *);

int is_cmd(info_t *, char *);
char *dup_chars(char *, int, int);
char *find_path(info_t *, char *, char *);

int loophsh(char **);

char *_strncpy(char *, char *, int);
char *_strncat(char *, char *, int);
char *_strchr(char *, char);

int interactive(info_t *);
int is_delim(char, char *);
int _isalpha(int);
int _atoi(char *);

void clear_info(info_t *);
void set_info(info_t *, char **);
void free_info(info_t *, int);

int _myexit(info_t *);
int _mycd(info_t *);
int _myhelp(info_t *);

char **strtow(char *, char *);
char **strtow2(char *, char);

int _erratoi(char *);
void print_error(info_t *, char *);
int print_d(int, int);
char *convert_number(long int, int, int);
void remove_comments(char *);

char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);

int _myhistory(info_t *);
int _myalias(info_t *);

char *_getenv(info_t *, const char *);
int _myenv(info_t *);
int _mysetenv(info_t *);
int _myunsetenv(info_t *);
int populate_env_list(info_t *);

char *_memset(char *, char, unsigned int);
void ffree(char **);
void *_realloc(void *, unsigned int, unsigned int);

ssize_t get_input(info_t *);
int _getline(info_t *, char **, size_t *);
void sigintHandler(int);

int bfree(void **);

list_t *add_node(list_t **, const char *, int);
list_t *add_node_end(list_t **, const char *, int);
size_t print_list_str(const list_t *);
int delete_node_at_index(list_t **, unsigned int);
void free_list(list_t **);

char **get_environ(info_t *);
int _unsetenv(info_t *, char *);
int _setenv(info_t *, char *, char *);

size_t list_len(const list_t *);
char **list_to_strings(list_t *);
size_t print_list(const list_t *);
list_t *node_starts_with(list_t *, char *, char);
ssize_t get_node_index(list_t *, list_t *);

int is_chain(info_t *, char *, size_t *);
void check_chain(info_t *, char *, size_t *, size_t, size_t);
int replace_alias(info_t *);
int replace_vars(info_t *);
int replace_string(char **, char *);

#endif
