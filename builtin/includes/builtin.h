/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najlee <najlee@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 12:01:52 by najlee            #+#    #+#             */
/*   Updated: 2021/07/02 12:01:53 by najlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include <signal.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <string.h>
# include <dirent.h>
# include <fcntl.h>
# include <termios.h>
# include <errno.h>

# define SHORT 0
# define LONG 1

# define BUFFER_SIZE 100000
# define ENV_MAX 40000000

# define WHITESPACE "\t\n\v\f\r "

# define REAL_PIPE 1

# define FALSE 0
# define TRUE 1

// extern int errno;

pid_t	g_pid;
// int		pp[2];


typedef int		t_bool;


typedef struct	s_term
{
	struct termios new_term;
	struct termios org_term;
}				t_term;

typedef enum	e_type
{
	normal = 0,
	export,
	environ
}				t_type;

typedef struct	s_tree
{
	char			val[ENV_MAX];
	int				size;
	struct s_tree	*left;
	struct s_tree	*right;
}				t_tree;

typedef struct	s_list
{
	char			val[BUFFER_SIZE];
	int				db;
	struct s_list	*left;
	struct s_list	*right;
}				t_list;

typedef struct		s_dummy
{
	struct s_list	*head;
	struct s_list	*tail;
}					t_dummy;

typedef struct	s_parsed
{
	char	cmd[3][BUFFER_SIZE];
}				t_parsed;

t_dummy env_list;

// main.c
void			sigint_handler(int err);
void			sigquit_handler(int err);
int				start_shell(t_term *term, t_dummy *history);
void			print_pwd(int type);
int				run_builtin(t_parsed parsed, t_dummy *std_out);
void			printpipe(char **pipe_str);
void			noncanonical_input(char *g_read_buf, t_term *term, t_dummy *history);


//builtin
int				m_echo(t_parsed parsed, t_dummy *std_out);
int				m_cd(t_parsed parsed);
int				m_pwd(t_parsed parsed, t_dummy *std_out);
int				m_exit(t_parsed parsed);
int				m_env(t_parsed parsed, t_dummy *std_out);
int				m_export(t_parsed parsed, t_dummy *std_out);
int				m_unset(t_parsed parsed);

// tree.c
t_tree			*tree(void);
void			init_tree(char **env);
void			insert_tree(char *val);
void			delete_tree(char *val);
void			free_tree();
t_tree			**search_tree(char *val);

void			inorder_print(t_tree *tr, int type, int out_fds);
int				inorder_execve(t_tree *tr, char ***output, int index);
char			*inorder_print_node(char *val, int type, int out_fds);

// lib.c
int				m_strncmp(char *s1, char *s2, size_t n);
void			*m_memset(void *dest, int value, size_t size);
char			*m_strcpy(char *dest, char *src);
int				m_strcmp(char *s1, char *s2);
int				m_strlen(char *str);
int				find_equal(char *str);

// lib2.c
char			**m_split_char(char *s, char c);
char			*m_substr(char *s, unsigned int start, size_t len);
char			**m_free_split(char **s);
size_t			m_check_size(char *s, char delim);
size_t			m_strlcpy(char *dst, char *src, size_t dstsize);
int				m_strchr(char *s, int c);

// lib3.c
char			*m_strdup(char *src);
int				m_max(int n1, int n2);
int				m_arrsize(char **arr);
int				nnnn(char *line, int idx, int flag, int ret);
char			*m_strjoin(char *s1, char *s2);
int				m_isnum(char *str);
void			*m_calloc(size_t count, size_t size);
char			*m_itoa(int n);
long long		m_atoi(char *str);


// run_redirection.c
char			*first_word(char *line);
void			fill_list(char *line, char ch, t_dummy *std);
int				redi_stdin(t_list *node);
int				redi_stdout(t_list *node);
char			*core_cmd(char *line);
char 			*join_parsed(t_parsed parsed);

// parsing.c
t_parsed		get_cmd_echo(char *line);
t_parsed		get_cmd(char *line);

// error.c
void			print_error(t_parsed parsed, char *status);
int				return_message(char *file, char *message, int ret);

void			print_parsed(t_parsed parsed);

// quote.c
void	 		replace_env(char *g_read_buf, int before_errno);
char			*m_find_env(char *envp);
int				put_env(char **temp, char *env, int tdx);

// execve.c
int				run_execved(char *pipe_str, t_parsed parsed,
				int in_fds, int out_fds, t_dummy *std_in, t_dummy *std_out);

// syntax_error.c
int 			check_syntax(char *g_read_buf);
int 			check_pipe(char *g_read_buf);
int				check_redi(char *g_read_buf);

// term.c
void			init_term(t_term *term);
void			reset_input_mode(t_term *term);
void			set_input_mode(t_term *term);

// signal.c
void			sigint_handler(int err);
// void			sigquit_handler(void);

// list.c
t_list			*new_list(char *val, int db);
int				init_list(t_dummy *dummy);
int				add_list(t_list *tail, char *val, int db);
void			prt_list(t_list *head);
t_bool			history_up(int i, int hdx, t_dummy *history, char **g_read_buf);
t_bool			history_down(int i, int hdx, t_dummy *history, char **g_read_buf);
void			delete_val(int hdx, t_dummy *history);
void			write_val(int hdx, t_dummy *history, int ch);
int				add_list_sort(t_dummy *dummy, char *val);
void			print_list(t_dummy *dummy);
void			free_list(t_dummy **dummy);
char			**make_envp(t_dummy *dummy);
char			*m_find_env_list(t_dummy *dummy, char *val);
int				delete_list(t_dummy *dummy, char *val);
int				search_list(t_dummy *dummy, char *val);

#endif
