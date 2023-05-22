#ifndef MAIN_H
#define MAIN_H

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

char *lptr;
int in;
int out;
int er;
char **argv;
pid_t child_pid;
char **_environ;
extern char **environ;
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
void interact(int mode);
char **arc;
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

#endif
