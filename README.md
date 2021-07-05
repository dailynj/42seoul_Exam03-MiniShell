# minishell
minishell 너무쉽당.. 할만하네~ 

## To-Do List

- syntax error (<> , > 이후에 아무것도 안들어오면)

- exit 할때, 인자로 0-255 아니면 exit(256) 출력하기

- t_bool

- Norm


### 디펜스
- cmd || cmd : OR 연산 (pipe x)
	https://unix.stackexchange.com/questions/190543/what-does-mean-in-bash

## test
**builtin**
echo
echo -n hello
echo -nnnn hello
echo -naa hello -n
Echo

env
env -j

export -u

cd
cd ..

unset
unset - h


**history**
echo a + echo b + echo c 후 방향키 위아래
echo b 지워보기
echo b -> ls 로 바꾸고 실행
echo a -> echo asdf 바꾸고 실행



**redirection**
cat a > b



**pipe**
cat | ls
ls | cat
echo a | echo b | echo c


**crazy**
echo asdf | cat > b 

