#include <unistd.h> // dup header file
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int fd1, fd2;

	if ((fd1 = open("file_1.txt", O_RDONLY)) < 0)
	{
		printf("file open error\n");
		exit(0);
	}

	fd2 = dup(fd1);

	printf("fd1 : %d, fd2 : %d\n", fd1, fd2);
	close(fd1);
	close(fd2);
	return (0);
}