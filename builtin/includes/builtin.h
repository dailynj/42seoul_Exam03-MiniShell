#ifndef BUILTIN_H
#define BUILTIN_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>

#define SHORT 0
#define LONG 1
#define BUFFER_SIZE 100
#define ENV_MAX 4000000

typedef enum e_type
{
	normal = 0,
	export,
	environ
}			t_type;

typedef struct s_tree
{
	char			val[ENV_MAX];
	int				size;
	struct s_tree	*left;
	struct s_tree	*right;
}			t_tree;


int echo(char **option, char *value);
int cd(char **option, char *value);
int pwd();
int m_exit();
int m_env();
int m_export();
int m_unset(char *val);

// lib.c
int		m_strncmp(char *s1, char *s2, size_t n);
void	*m_memset(void *dest, int value, size_t size);
char	*m_strcpy(char *dest, const char *src);
int		m_strcmp(char *s1, char *s2);
int		m_strlen(char *str);
int		find_equal(char *str);

// tree.c
t_tree	*tree(void);
void init_tree(char **env);
void insert_tree(char *val);
void delete_tree();
void free_tree(t_tree **tr);
void inorder(int type, t_tree *tr);
t_tree **search_tree(char *val);
int m_max(int n1, int n2);

#endif
