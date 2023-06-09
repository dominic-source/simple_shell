#ifndef MAIN_H
#define MAIN_H

#include <errno.h>
#include <stdlib.h>
#include <stddef.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
char *rm_nwl(char *str);
char *previous_wd;
char *lptr;
int in;
int out;
int er;
int cdc;
char **argv;
pid_t child_pid;
char **_environ;
char **alias;
extern char **environ;
void error_alias(char *message, char *arg);
int set_alias(void);
void print_alias_func(int print_alias);
int cd_d_alias(void);
int _strcmp(const char *s1, const char *s2);
int _strncmp(const char *s1, const char *s2, size_t n);
char *_strcat(char *dest, const char *src);
char *_strtok(char *str, const char *delim);
size_t _strlen(const char *str);
void noninteract(int interractive);
char *_strcpy(char *dest, const char *src);
ssize_t _getline(char **lptr, size_t *n, int fd);
int _setenv(const char *name, const char *value, int overwrite);
void free_mem(char **args, char *a, char *b);
int handle_func_cmd(void);
char **alloc_mem(void);
void hndl_sgnl(int sig);
char *handle_cmd(void);
void interact(void);
char **arc;
int exit_status;
int status;
int _cd(void);
void _echo_expand(void);
int commands_cnt;
void _env(void);
int str_num(char *str);
void print_env(void);
void my_exit(void);
char **_realloc_env(int i);
int _unsetenv(const char *name);
char *num_str(int num, char str[]);
void print_error(char *message);
int interactive;
char *_getenv(const char *name);

#endif
