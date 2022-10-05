# minishell

Functional bash terminal. Developed from scratch on macOS Mojave and Catalina.

Use of pipes and creation of child processes to create system redirects and pipes.

List of environment variables obtained from the runtime environment.

The developed commands not executed by the system are:
echo with the "-n" flag, cd, pwd, exit with and without arguments, env, export with and without arguments and unset

The rest of the commands are executed by the system. Parentheses, "&&", "||" and wildcards such as "*" are not implemented.

All instructions for compiling the program are in the "Makefile" file. To compile download the repository and run "make" in the terminal, this will generate the executable "minishell".
To execute run "./minishell".
It is possible that the program does not compile in environments other than mac due to the readline library path.
