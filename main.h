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
int _strcmp(const char *s1, const char *s2);
int _strncmp(const char *s1, const char *s2, size_t n);
size_t _strlen(const char *str);
void noninteract(int interractive);
char *_strcpy(char *restrict dest, const char *src);


#endif
