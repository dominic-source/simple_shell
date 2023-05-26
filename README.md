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
