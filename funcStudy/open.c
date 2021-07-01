#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    if (open("a.txt", O_RDONLY) == -1)
        printf("wow\n");
    else
        printf("here\n");
}