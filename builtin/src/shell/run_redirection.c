#include "builtin.h"

// 확인 필요
int exist_filename(char *new_filename)
{
	struct dirent	*dir_entry;
	DIR				*dir_info;

	dir_info = opendir(".");
	if (dir_info)
	{
		while((dir_entry = readdir(dir_info)))
		{
			if (m_strncmp(dir_entry->d_name, new_filename,
				m_max(m_strlen(dir_entry->d_name), m_strlen(new_filename))))
			return (1);
		}
		closedir(dir_info);
	}
	return (0);
}

//t_bool
// 확인 필요
void		run_redirect(char *g_read_buf)
{
	char	**redi;
	// int		flag;
	int		fd;

	redi = m_split_char(g_read_buf, ' '); // redi[0] : cmd redi[2] : file_name
	if (exist_filename(redi[2])) // filename 이 존재
	{
		if (m_strncmp(redi[1], ">", 2))
		{
			// 기존 파일 모두 지우고 write
			fd = open(redi[2], O_WRONLY | O_TRUNC);
			write(fd, redi[0], m_strlen(redi[0]));
			close(fd);
		}
		else if (m_strncmp(redi[1], ">>", 2))
		{
			fd = open(redi[2], O_WRONLY | O_APPEND);
			write(fd, redi[0], m_strlen(redi[0]));
			close(fd);
		}
		else if (m_strncmp(redi[1], "<", 2))
		{

		}
		else if (m_strncmp(redi[1], "<<", 2))
		{

		}
	}
	else // filename 이 존재 x
	{
		if (m_strncmp(redi[1], ">", 2))
		{
			fd = open(redi[2], O_WRONLY | O_CREAT | O_TRUNC);
			write(fd, redi[0], m_strlen(redi[0]));
			close(fd);
		}
		else if (m_strncmp(redi[1], ">>", 2))
		{
			fd = open(redi[2], O_WRONLY | O_CREAT | O_TRUNC);
			write(fd, redi[0], m_strlen(redi[0]));
			close(fd);
		}
		else if (m_strncmp(redi[1], "<", 2))
		{

		}
		else if (m_strncmp(redi[1], "<<", 2))
		{

		}
	}
}
