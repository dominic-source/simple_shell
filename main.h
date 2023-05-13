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
pid_t child_pid;


#endif
