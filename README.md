# minishell
minishell 하기싫어..


## To-Do List
- export는 builtin 함수이지만 env는 아니다.. 따라서 내부 PATH를 지우면 export는 정상적으로 동작하지만 env는 동작하지 않는다.

- cd
v	-> . .. 
v	-> cd / cd ~ 
v	-> 환경변수
ㅁ	-> 에러메세지

- error
	-> syntax
	-> " 안닫긴거 에러처리
	-> parsing (;  ` -> unexpected argument)

- export a=b 나왔을때 Insert하기
- export가 a=b 형태가 아니라 a 형태로 나왔을 때 출력문 제대로 처리하기

- signal 처리 ctrl + c, ctrl + d, ctrl + \
	-> ctrl + d 물어보기

- $?
	-> https://askubuntu.com/questions/646526/what-is-is-it-a-variable
- $char