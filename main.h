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

char **lptr = NULL;
int in = STDIN_FILENO;
int out = STDOUT_FILENO;
int er = STDERR_FILENO;
pid_t child_pid;

#endif
