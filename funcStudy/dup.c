#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int main(int argc, char **argv, char **envp)
{
    int fd = open("a.txt",  O_WRONLY | O_TRUNC);
    
    dup2(fd, 1);
    // dup2(fd, 0);
    execve("/bin/ls", argv, envp);

    return (0);
}