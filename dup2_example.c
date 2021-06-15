#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>

int main(void){
        int fd1, ret;

        if ((fd1 = open("file_1.txt", O_RDONLY)) < 0){
			printf("file open error\n");
			exit(0);
        }

        //fd1의 파일 디스크립터가 명시한 STDOUT_FILENO의 파일 디스크립터로
        ret = dup2(fd1, STDOUT_FILENO);

        //fd1으로 출력
        printf("fd1 : %d, ret : %d\n", fd1, ret);

        //STDERR_FILENO 디스크립터가 명시된 fd1으로 복제됨
        ret = dup2(STDERR_FILENO,fd1);

        //fd1은 에러로 출력됨
        write(fd1,"hello!\n",7);

        //stdout이 file로 써짐
        printf("printf를 썼지만 파일에 기록됨 \n");

        close(fd1);
}