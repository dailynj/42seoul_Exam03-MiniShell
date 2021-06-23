#include "builtin.h"

// 큰 따옴표만 다 없앰
// void	delete_quote(char *buf, char quote)
// {
// 	char	temp[BUFFER_SIZE];
// 	int		idx;
// 	int		tdx;
// 	int flag = 0;
// 	tdx = -1;
// 	idx = -1;
	
// 	m_memset(temp, 0 , BUFFER_SIZE);
// 	while(buf[++idx])
// 	{
// 		// if (buf[idx] == '\'' && flag == 0)
// 		// 	flag = 1;
// 		// else if (buf[idx] == '\'' && flag == 1)
// 		// 	flag = 0;
// 		else if (buf[idx] == quote && flag == 0)
// 		{
// 			while (buf[++idx] != quote)
// 			{
// 				temp[++tdx] = buf[idx];
// 			}
// 		}
// 		else
// 			temp[++tdx] = buf[idx];
// 	}
// 	m_memset(buf, 0, BUFFER_SIZE);
// 	m_strlcpy(buf, temp, BUFFER_SIZE);
// }

char *m_find_env(char *envp)
{
	char	*dirp;
	t_tree	**output;

	dirp = NULL;
	output = search_tree(envp);
	if (output == NULL)
		return (NULL);
	envp = (*output)->val;
	while (*envp)
	{
		if (*envp == '=')
		{
			dirp = ++envp;
			break;
		}
		++envp;
	}
	return (dirp);
}

int 	check_real(char* buf, int idx)
{
	if (buf[idx] == '|')
		return (REAL_PIPE);
	else if (buf[idx] == '<' && buf[idx + 1] == '<')
		return (REAL_LL);
	else if (buf[idx] == '<')
		return (REAL_L);
	else if (buf[idx] == '>' && buf[idx + 1] == '>')
		return (REAL_RR);
	else if (buf[idx] == '>')
		return (REAL_R);
	return (0);
}

void get_env(char **env, char *buf, int *idx)
{
	int		edx;

	edx = -1;
	(*idx)++;
	*env = malloc(BUFFER_SIZE);
	if (!*env)
		return ; // error 처리
	while (buf[(*idx)] && buf[(*idx)] != ' ' && buf[(*idx)] != '\'' && buf[(*idx)] != '\"')
	{
		(*env)[++edx] = buf[(*idx)++];
	}
	--(*idx);
	(*env)[++edx] = 0;
}

int	put_env(char **temp, char *env, int tdx)
{
	// char	temp[BUFFER_SIZE];
	char	*dirp;

	if ((dirp = m_find_env(env))) // NULL 이면 볼 필요 없음
	{
		while(*dirp)
		{
			(*temp)[++tdx] = *dirp;
			++dirp;
		}
	}
	return (tdx);
}

// void	replace_env(char *buf)
// {
// 	printf("1. string : %s\n", buf);
// 	delete_quote(buf, '\"');
// 	printf("2. string : %s\n", buf);
// 	put_env(buf);
// 	printf("3. string : %s\n", buf);
// 	delete_quote(buf, '\'');
// 	printf("4. string : %s\n", buf);
// 	while (*buf)
// 	{
// 		printf("%d ", (int)*buf);
// 		++buf;
// 	}
// 	printf("\n");
// }


// 없는 환경변수면 \n
// 있는 환경변수면 치환 (""사이에 있거나 그냥 있을 때만)


void	 replace_env()
{
	char	*temp;
	char	*env;
	int		idx;
	int		tdx;

	tdx = -1;
	idx = -1;
	temp = m_calloc(BUFFER_SIZE, 1);
	if (!temp)
		return ;  // error 처리
	while(g_read_buf[++idx])
	{
		if (g_read_buf[idx] == '\"')
		{
			while (g_read_buf[++idx] && g_read_buf[idx] != '\"')
			{
				// 아래랑 똑같음
				if (g_read_buf[idx] == '$')
				{
					get_env(&env, g_read_buf, &idx);
					tdx = put_env(&temp, env, tdx);
					free(env);
				}
				else
				{
					temp[++tdx] = g_read_buf[idx];
				}
				// -------
			}
		}
		else if(g_read_buf[idx] == '\'')
		{
			while (g_read_buf[++idx] && g_read_buf[idx] != '\'')
			{
				temp[++tdx] = g_read_buf[idx];
			}
		}
		else
		{
			// 위에랑 똑같음
			if (g_read_buf[idx] == '$')
			{
				get_env(&env, g_read_buf, &idx);
				tdx = put_env(&temp, env, tdx);
				free(env);
			}
			//  --------
			else if (check_real(g_read_buf, idx))
			{
				temp[++tdx] = check_real(g_read_buf, idx);
				if (check_real(g_read_buf, idx) == 2 || check_real(g_read_buf, idx) == 4)
					++idx;
			}
			else
				temp[++tdx] = g_read_buf[idx];
		}
	}
	m_memset(g_read_buf, 0 , BUFFER_SIZE);
	m_strlcpy(g_read_buf, temp, BUFFER_SIZE);
	free(temp);
	temp = 0;
}