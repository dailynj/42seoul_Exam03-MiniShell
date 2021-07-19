## minishell
 : Make a simple shell (bash)

## builtins
1. echo with option -n
2. cd with only a relative or absolute path
3. pwd with no options
4. export with no options
5. unset with no options
6. env with no options or arguments
7. exit with no options

## functions
1. Show a prompt when waiting for a new command.
2. Have a working History.
3. Search and launch the right executable (based on the PATH variable or by using relative or absolute path)
4. ' inhibit all interpretation of a sequence of characters.
5. " inhibit all interpretation of a sequence of characters except for $.
6. Redirections:
- < should redirect input.
- > should redirect output.
- “<<” read input from the current source until a line containing only the delimiter is seen. it doesn’t need to update history!
- “>>” should redirect output with append mode.
7. Pipes | The output of each command in the pipeline is connected via a pipe to the
input of the next command.
8. Environment variables ($ followed by characters) should expand to their values.
9. $? should expands to the exit status of the most recently executed foreground
pipeline.
10. ctrl-C ctrl-D ctrl-\ should work like in bash.
11. When interactive:
- ctrl-C print a new prompt on a newline.
- ctrl-D exit the shell.
- ctrl-\ do nothing.
