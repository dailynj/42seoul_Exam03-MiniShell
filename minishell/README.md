## minishell
 : Make a simple shell (bash)

## builtins
### echo with option -n
### cd with only a relative or absolute path
### pwd with no options
### export with no options
### unset with no options
### env with no options or arguments
### exit with no options

## functions
### Show a prompt when waiting for a new command.
### Have a working History.
### Search and launch the right executable (based on the PATH variable or by using relative or absolute path)
### ’ inhibit all interpretation of a sequence of characters.
### " inhibit all interpretation of a sequence of characters except for $.
### Redirections:
- < should redirect input.
- > should redirect output.
- “<<” read input from the current source until a line containing only the delimiter is seen. it doesn’t need to update history!
- “>>” should redirect output with append mode.
### Pipes | The output of each command in the pipeline is connected via a pipe to the
input of the next command.
### Environment variables ($ followed by characters) should expand to their values.
### $? should expands to the exit status of the most recently executed foreground
pipeline.
### ctrl-C ctrl-D ctrl-\ should work like in bash.
### When interactive:
- ctrl-C print a new prompt on a newline.
- ctrl-D exit the shell.
- ctrl-\ do nothing.
