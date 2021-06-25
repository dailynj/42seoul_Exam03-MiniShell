# minishell
minishell 하기싫어..

## To-Do List
- export는 builtin 함수이지만 env는 아니다.. 따라서 내부 PATH를 지우면 export는 정상적으로 동작하지만 env는 동작하지 않는다.

- echo $!
  echo $* ... 나오는 것도 있고 그대로 나오는 것도 있음

- $?
	-> https://askubuntu.com/questions/646526/what-is-is-it-a-variable

- pipe

- redirection

- read에서 읽는 문자 char -> int로 자료형 바꾸기(127 이상 값이 들어올 수 있음)

- termios 함수 만들기

- backspace구현해야함! 터미널에 문자가 출력되는 방식을 바꿔야함!
 예를들어 만약 a를 타이핑 했을 때, a가 바로 터미널에 출력되는 echo방식이 아니라 a의 텍스트를 비교하고 a일반적인 문자이면 write해서 보여주는 방식으로 출력해야함
 
 -그래서 문자열을 그대로 넣으면 안되고 지우는 것을 고려해서 넣어줘야함
