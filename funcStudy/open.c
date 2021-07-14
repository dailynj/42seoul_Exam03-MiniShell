#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    if (open("stdout", O_RDONLY) == -1)
        printf("wow\n");
    else
        printf("here\n");
}
