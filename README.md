# Installation
**A simple shell project that works similar to sh.**

_To compile, gcc -Wall -Wextra -Werror -pedantic -std=gnu89 *.c -o hsh_

_To start shell, type ./hsh and enter._

# Project completion
**Project was completed using**
+ C language
+ Shell
+ Betty linter

# Description
hsh is a simple UNIX command language interpreter that reads commands from either a file or standard input and executes them.

# How hsh works
+ Prints a prompt and waits for a command from the user
+ Creates a child process in which the command is checked
+ Checks for built-ins, aliases in the PATH, and local executable programs
+ The child process is replaced by the command, which accepts arguments
+ When the command is done, the program returns to the parent process and prints the prompt
+ The program is ready to receive a new command
+ To exit: press Ctrl-D or enter "exit" (with or without a status)
+ Works also in non interactive mode

# Invocation
_Usage: hsh [filename]_

To invoke hsh, compile all .c files in the repository and run the resulting executable.

hsh can be invoked both interactively and non-interactively. If hsh is invoked with standard input not connected to a terminal, it reads and executes received commands in order.

# Environment
Upon invocation, hsh receives and copies the environment of the parent process in which it was executed. This environment is an array of name-value strings describing variables in the format NAME=VALUE. A few key environmental variables are:

## HOME
The home directory of the current user and the default directory argument for the cd builtin command.

## PATH
A colon-separated list of directories in which the shell looks for commands. A null directory name in the path (represented by any of two adjacent colons, an initial colon, or a trailing colon) indicates the current directoryi.

# Command Execution
After receiving a command, hsh tokenizes it into words using " " as a delimiter. The first word is considered the command and all remaining words are considered arguments to that command. hsh then proceeds with the following actions:

If the first character of the command is neither a slash (\) nor dot (.), the shell searches for it in the list of shell builtins. If there exists a builtin by that name, the builtin is invoked.
If the first character of the command is none of a slash (\), dot (.), nor builtin, hsh searches each element of the PATH environmental variable for a directory containing an executable file by that name.
If the first character of the command is a slash (\) or dot (.) or either of the above searches was successful, the shell executes the named program with any remaining given arguments in a separate execution environment.

# Exit Status
hsh returns the exit status of the last command executed, with zero indicating success and non-zero indicating failure.

If a command is not found, the return status is 127; if a command is found but is not executable, the return status is 126.

All builtins return zero on success and one or two on incorrect usage (indicated by a corresponding error message).
