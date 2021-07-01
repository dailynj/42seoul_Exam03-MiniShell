#include "builtin.h"

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
	// else if (buf[idx] == '<' && buf[idx + 1] == '<')
	// 	return (REAL_LL);
	// else if (buf[idx] == '<')
	// 	return (REAL_L);
	// else if (buf[idx] == '>' && buf[idx + 1] == '>')
	// 	return (REAL_RR);
	// else if (buf[idx] == '>')
	// 	return (REAL_R);
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
	char	*dirp;


	if ((dirp = m_find_env(env)))
	{
		while(*dirp)
		{
			(*temp)[++tdx] = *dirp;
			++dirp;
		}
	}
	return (tdx);
}

void	 replace_env(char *g_read_buf)
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
		if (g_read_buf[idx] == '\\' && g_read_buf[idx + 1])
			temp[++tdx] = g_read_buf[++idx];
		else if (g_read_buf[idx] == '\"')
		{
			while (g_read_buf[++idx] && g_read_buf[idx] != '\"')
			{
				// 아래랑 똑같음
				if (g_read_buf[idx] == '\\' && g_read_buf[idx + 1] && g_read_buf[idx + 1] == '\\')
				{
					temp[++tdx] = g_read_buf[++idx];
				}
				else if (g_read_buf[idx] == '\\' && g_read_buf[idx + 1])
				{
					temp[++tdx] = g_read_buf[idx];
					temp[++tdx] = g_read_buf[++idx];
				}
				else if (g_read_buf[idx] == '$')
				{
					get_env(&env, g_read_buf, &idx);
					tdx = put_env(&temp, env, tdx);
					free(env);
				}
				else
				{
					temp[++tdx] = g_read_buf[idx];
				}
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
				if (g_read_buf[idx + 1] == '?')
				{
					char *tmp;

					tmp = g_question;
					while(*tmp)
					{
						temp[++tdx] = *tmp;
						++tmp;
					}
					++idx;
				}
				else
				{
					get_env(&env, g_read_buf, &idx);
					tdx = put_env(&temp, env, tdx);
					free(env);
				}
			}
			//  --------
			else if (check_real(g_read_buf, idx))
			{
				temp[++tdx] = check_real(g_read_buf, idx);
				// if (check_real(g_read_buf, idx) == 2 || check_real(g_read_buf, idx) == 4)
				// 	++idx;
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
