/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/01 10:18:06 by lkaser            #+#    #+#             */
/*   Updated: 2018/07/06 20:13:25 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>
#include <stdint.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>

#include "ft_ls.h"

static t_compare	g_sorts[2][2] = {
	{sort_ascii, sort_ascii_r},
	{sort_time, sort_time_r}
};

static char			*absolute_path(const char *dir, const char *file,
	char **name)
{
	int		dir_len;
	int		file_len;
	int		i;
	char	*absolute;

	dir_len = ft_strlen(dir);
	file_len = ft_strlen(file);
	absolute = malloc(dir_len + file_len + 2);
	i = -1;
	while (++i < dir_len)
		absolute[i] = dir[i];
	absolute[i] = '/';
	*name = absolute + i + 1;
	i = -1;
	while (++i < file_len)
		absolute[i + dir_len + 1] = file[i];
	absolute[i + dir_len + 1] = '\0';
	return (absolute);
}

static char			*pms(unsigned mode)
{
	static char	p[11];

	ft_strcpy(p, "----------");
	MATCH(S_ISDIR(mode), p[0] = 'd');
	OR(S_ISBLK(mode), p[0] = 'b');
	OR(S_ISCHR(mode), p[0] = 'c');
	OR(S_ISFIFO(mode), p[0] = 'p');
	OR(S_ISLNK(mode), p[0] = 'l');
	OR(S_ISSOCK(mode), p[0] = 's');
	mode & S_IRUSR && (p[1] = 'r');
	mode & S_IWUSR && (p[2] = 'w');
	mode & S_IXUSR && (p[3] = 'x');
	mode & S_IRGRP && (p[4] = 'r');
	mode & S_IWGRP && (p[5] = 'w');
	mode & S_IXGRP && (p[6] = 'x');
	mode & S_IROTH && (p[7] = 'r');
	mode & S_IWOTH && (p[8] = 'w');
	mode & S_IXOTH && (p[9] = 'x');
	if (mode & S_ISUID)
		p[3] = (mode & S_IXUSR) ? 's' : 'S';
	if (mode & S_ISGID)
		p[6] = (mode & S_IXGRP) ? 's' : 'l';
	if (mode & S_ISVTX)
		p[9] = (mode & S_IXOTH) ? 't' : 'T';
	return (p);
}

static char			*file_link(t_file *file)
{
	static char link_str[1024];

	if (S_ISLNK(file->meta.st_mode))
	{
		ft_bzero(link_str, 1024);
		link_str[0] = ' ';
		link_str[1] = '-';
		link_str[2] = '>';
		link_str[3] = ' ';
		readlink(file->path, link_str + 4, 1020);
	}
	else
		link_str[0] = '\0';
	return (link_str);
}

static void			print_files(t_vector files,
	t_list **dirs, int blocks, int8_t opts[])
{
	t_file		*file;
	unsigned	i;
	char		*time;

	ft_qsort(files.data, files.length, g_sorts[opts['t']][opts['r']]);
	opts['l'] && ft_printf("total %u\n", blocks);
	i = 0;
	while (i < files.length && (file = files.data[i++]))
	{
		if (opts['l'])
		{
			time = ctime(&file->meta.st_mtime);
			ft_printf("%s %4u %s  %s %6lli %s %s%s\n", pms(file->meta.st_mode),
				file->meta.st_nlink, getpwuid(file->meta.st_uid)->pw_name,
				getgrgid(file->meta.st_gid)->gr_name, file->meta.st_size,
				(time[19] = 0) + time, file->name, file_link(file));
		}
		else
			ft_printf("%s%c", file->name, opts['1'] ? '\n' : '\t');
		if (!((opts['R'] && S_ISDIR(file->meta.st_mode))
			&& add_dir_sorted(dirs, file, g_sorts[opts['t']][opts['r']])))
			free(file->path);
	}
	ft_vector_rm(&files);
	!opts['l'] && write(1, "\n", 1);
}

void				iter_dir(const char *path, t_list **dirs, int8_t opts[])
{
	DIR				*pwd;
	t_vector		ls;
	struct dirent	*info;
	unsigned		blocks;

	ft_vector_init(&ls);
	if (!(pwd = opendir(path)))
		return (perror("ft_ls"));
	blocks = 0;
	while ((info = readdir(pwd)))
	{
		if (info->d_name[0] == '.' && !opts['a'])
			continue;
		ft_vector_push(&ls, malloc(sizeof(t_file)));
		FILE(ls.data[ls.length - 1])->path = absolute_path(path, info->d_name,
			&(FILE(ls.data[ls.length - 1])->name));
		lstat(FILE(ls.data[ls.length - 1])->path,
			&(FILE(ls.data[ls.length - 1])->meta));
		blocks += FILE(ls.data[ls.length - 1])->meta.st_blocks;
	}
	print_files(ls, dirs, blocks, opts);
	closedir(pwd);
}
