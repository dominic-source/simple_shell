A simple shell project that works similar to sh.

To compile, gcc -Wall -Wextra -Werror -pedantic -std=gnu89 *.c -o hsh

To start shell, type ./hsh and enter.

Project was completed using
C language
Shell
Betty linter

Description
hsh is a simple UNIX command language interpreter that reads commands from either a file or standard input and executes them.

How hsh works
Prints a prompt and waits for a command from the user
Creates a child process in which the command is checked
Checks for built-ins, aliases in the PATH, and local executable programs
The child process is replaced by the command, which accepts arguments
When the command is done, the program returns to the parent process and prints the prompt
The program is ready to receive a new command
To exit: press Ctrl-D or enter "exit" (with or without a status)
Works also in non interactive mode

Invocation
Usage: hsh [filename]

To invoke hsh, compile all .c files in the repository and run the resulting executable.

hsh can be invoked both interactively and non-interactively. If hsh is invoked with standard input not connected to a terminal, it reads and executes received commands in order.

Environment
Upon invocation, hsh receives and copies the environment of the parent process in which it was executed. This environment is an array of name-value strings describing variables in the format NAME=VALUE. A few key environmental variables are:

HOME
The home directory of the current user and the default directory argument for the cd builtin command.
