#ifndef BUILTIN_H
#define BUILTIN_H

#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <dirent.h>
#include <fcntl.h>
#include <termios.h>

#define SHORT 0
#define LONG 1

#define BUFFER_SIZE 100000
#define ENV_MAX 40000000

#define WHITESPACE "\t\n\v\f\r "

#define REAL_PIPE 1
#define REAL_LL 2
#define REAL_L 3
#define REAL_RR 4
#define REAL_R 5

#define ERROR 0
#define OK 1

struct termios new_term;
struct termios org_term;

pid_t	g_pid;
char	g_read_buf[BUFFER_SIZE];
// int		g_errno;
int		g_fds;

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

typedef struct	s_parsed
{
	char cmd[3][BUFFER_SIZE];
	// char opt[BUFFER_SIZE];
	// char arv[BUFFER_SIZE];
}				t_parsed;

// main.c
int				start_shell();
void			print_pwd(int type);
int				run_builtin(t_parsed parsed);
void			set_input_mode(void);
void			reset_input_mode(void);
void			printpipe(char **pipe_str);

//builtin
int 			m_echo(t_parsed parsed);
int				m_cd(t_parsed parsed);
int				m_pwd(t_parsed parsed);
int				m_exit();
int				m_env(t_parsed parsed);
int				m_export(t_parsed parsed);
int				m_unset(t_parsed parsed);


// tree.c
t_tree			*tree(void);
void			init_tree(char **env);
void			insert_tree(char *val);
void			delete_tree();
void			free_tree(t_tree **tr);
t_tree			**search_tree(char *val);

void			inorder_print(t_tree *tr, int type);
int				inorder_execve(t_tree *tr, char ***output, int index);
char*			inorder_print_node(char *val, int type);


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
int				nnnn(char *line);
char			*m_strjoin(char *s1, char *s2);
int				m_isnum(char *str);
void			*m_calloc(size_t count, size_t size);


// run_redirection.c
int				exist_filename(char *new_filename);
void			run_redirect(char *g_read_buf);

// parsing.c
t_parsed		get_cmd_echo(char *line);
t_parsed		get_cmd(char *line);


// error.c
void			print_error(t_parsed parsed, char *status);
void			print_parsed(t_parsed parsed);

// quote.c
void			replace_env();
char			*m_find_env(char *envp);
int				put_env(char **temp, char *env, int tdx);

// execve.c
int				run_execved(char *pipe_str, t_parsed parsed, int pnum, int final);

// syntax_error.c
int 			check_syntax();
int 			check_pipe();

#endif
