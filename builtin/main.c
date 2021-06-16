#include "builtin.h"

int functions();
int start_shell();
void print_pwd(int type);

int main(int ac, char **av, char **env)
{
	// char *str;
	// t_tree *tmp;

	// tmp = malloc(sizeof(t_tree));
	// printf("addr : %p\n", tmp);
	// m_strcpy(tmp->val, "hello");
	// printf("str : %s\n", tmp->val);

	// free(tmp);
	// t_tree *tmp2 = malloc(sizeof(t_tree));
	// printf("addr : %p\n", tmp);
	// printf("str : %s\n", tmp->val);

	// /*
	write(1, "here!\n", 6);
	init_tree(env);
	insert_tree("kr=ks");
	insert_tree("hB=ks");
	insert_tree("i=asdf");
	insert_tree("d=ks");
	insert_tree("cL=asdf");
	insert_tree("f=pqwer");
	insert_tree("bcde=bcde");
	insert_tree("e=asdf");
	insert_tree("or=ks");
	insert_tree("j=pqwer");
	insert_tree("lB=ks");
	insert_tree("pB=ks");
	insert_tree("gr=ks");
	insert_tree("n=pqwer");
	insert_tree("m=asdf");
	inorder(2, tree());
	printf("------------------------\n");
	delete_tree("i");
	delete_tree("j");
	inorder(2, tree());
	printf("------------------------\n");
	// start_shell();
	return (0);
}

int start_shell()
{
	char *short_pwd;
	char read_buf[BUFFER_SIZE];
	int read_size;

	while (1)
	{
		print_pwd(LONG);
		read_size = read(0, read_buf, BUFFER_SIZE);
		if (!m_strncmp(read_buf, "echo", read_size - 1))
		{
			echo(NULL, "hello");
		}
		else if (!m_strncmp(read_buf, "pwd", read_size - 1))
		{
			pwd();
			// 옵션이 들어오면 invalid option..?
			// 인자가 들어오면 무시
		}
		else if (!m_strncmp(read_buf, "cd", read_size - 1))
		{
			cd(NULL, "/Users/su/Desktop/42Seoul/");
			// 파싱해서 val 보내기
		}
		else if (!m_strncmp(read_buf, "exit", read_size - 1))
		{
			m_exit();
		}
		else if (!m_strncmp(read_buf, "env", read_size - 1))
		{
			m_env();
			// 옵션 들어오면 error 처리
			// 옵션이 아닌 str 들어올때 error 처리
		}
		else if (!m_strncmp(read_buf, "export", read_size - 1))
		{
			m_export();
			// 1개 들어오면 search 하기
			// 0개 들어오면 전체 출력
			// 옵션 error
			// str error 처리
		}
		else if (!m_strncmp(read_buf, "unset", read_size - 1))
		{
			m_unset("LL");
			// 파싱해서 환경변수 이름 넣어주기
			// 옵션 error
			// str error
		}
		m_memset(read_buf, 0, BUFFER_SIZE);
	}
	return (0);
}

void print_pwd(int type)
{
	char cwd[PATH_MAX];
	char *temp;
	int cnt;
	int color;
	int max;

	max = type * 99999;
	temp = cwd;
	cnt = 0;
	color = 1;
	m_memset(cwd, 0, PATH_MAX);
	if (getcwd(cwd, sizeof(cwd)) == NULL)
		return ;
	printf("\033[0mSuNaSHELL🦀 ");
	while (*temp)
	{
		++cnt;
		if (*temp == '/')
		{
			cnt = 0;
			color++;
		}
		if (cnt < max)
			printf("\033[0;3%dm%c", color % 7, *temp);
		++temp;
	}
	printf("\033[0;3%dm\n", (color + 1) % 7);
	write(1, "> ", 3);
}
