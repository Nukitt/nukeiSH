# OSN Assignment 3

## nukeish - Shell in C

### How to run the code
1. Run `make`.
2. Run `./nukeish`

## Features
1. `main.c` - contains the code for the handling the input tokenization including piping and redirection.
2. `cummands.c` - contains the code for the handling the commands after they are tokenized.
3. `prompt.c` - contains the code to print the prompt which also shows time taken to execute a foreground process.
4. `pwd.c` - contains the code for the present working directory command.
5. `cd.c` - contains the code for the change directory command.
6. `ls.c` - contains the code for the ls command.
7. `echo.c` - contains the code for the echo command.
8. `pinfo.c` - contains the code for the process info command.
9. `fg.c` - contains the code for the bringing background processes into foreground.
10. `bg.c` - contains the code for the executing background processes.
11. `discover.c` - contains the code for searching files and directories.
12. `proc_list.c` - contains the code to make a linked list to handle background processes.
13. `jobs.c` - contains the code for the job command which displays all the background processes by the shell.
14. `sig.c `- contains the code for sig which can signal any process based on the given job number.
15. `sighand.c` - contains the code for handling the ctrl + c and ctrl + z signals.
16. `history.c` - contains the code of history command which can tell us the 10 previously used commands.
17. `makefile` - contains code for the makefile which compiles the full code.