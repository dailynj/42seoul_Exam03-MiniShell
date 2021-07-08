# minishell
minishell 너무쉽당.. 할만하네~ 



## To-Do List
- cat << end 하고 ctrl+C 누르면 cat 실행안하고 $? 를 1로 바꿔줘야 함
				 ctrl+D 누르면 cat 실행하고 0
- a.txt 이름 고치기

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

