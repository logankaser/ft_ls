/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/25 17:49:40 by lkaser            #+#    #+#             */
/*   Updated: 2018/05/25 19:31:34 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>
#include <stdint.h>

#include "ft_ls.h"

static t_compare	g_sorts[2][2] = {
	{sort_ascii, sort_ascii_r},
	{sort_time, sort_time_r}
};

static char			*absolute_path(const char *dir, const char *file)
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
	i = -1;
	while (++i < file_len)
		absolute[i + dir_len + 1] = file[i];
	absolute[i + dir_len + 1] = '\0';
	return (absolute);
}

static void			print_files(t_vector files,
	t_list **dirs, int blocks, uint8_t opts[])
{
	t_file		*file;
	unsigned	i;

	ft_qsort(files.data, files.length, g_sorts[opts['t']][opts['r']]);
	opts['l'] && ft_printf("total %u\n", blocks);
	i = 0;
	while (i < files.length)
	{
		file = files.data[i];
		ft_putendl(file->name);
		if (S_ISDIR(file->meta.st_mode))
			ft_lstpush(dirs, file->path, 0);
		++i;
	}
	ft_vector_rm(&files);
}

static void			iter_dir(const char *path, t_list **dirs, uint8_t opts[])
{
	DIR				*pwd;
	t_vector		ls;
	struct dirent	*info;
	unsigned		blocks;

	ft_vector_init(&ls);
	if (!(pwd = opendir(path)))
	{
		perror("ft_ls");
		return ;
	}
	blocks = 0;
	while ((info = readdir(pwd)))
	{
		if (info->d_name[0] == '.' && !opts['a'])
			continue;
		ft_vector_push(&ls, malloc(sizeof(t_file)));
		ft_memcpy(FILE(ls.data[ls.length - 1])->name, info->d_name, NAME_MAX);
		FILE(ls.data[ls.length - 1])->path = absolute_path(path, info->d_name);
		lstat(FILE(ls.data[ls.length - 1])->path,
			&(FILE(ls.data[ls.length - 1])->meta));
		blocks += FILE(ls.data[ls.length - 1])->meta.st_blocks;
	}
	print_files(ls, dirs, blocks, opts);
	closedir(pwd);
}

int					main(int argc, char **argv)
{
	uint8_t	options[128];
	t_list	*dir;
	char	*path;
	int		i;

	ft_bzero(options, 128);
	path = argc - 1 > 0 && argv[argc - 1][0] != '-' ? argv[argc - 1] : NULL;
	while (--argc > 0)
		if (argv[argc][(i = 0)] == '-')
			while (argv[argc][++i])
				options[(int)argv[argc][i]] = 1;
	dir = NULL;
	iter_dir(path ? path : ".", &dir, options);
	if (!options['R'])
		return (0);
	while ((path = ft_lstpop(&dir)))
	{
		ft_putstr("\033[34;1m");
		ft_putstr(path);
		ft_putendl("\033[0m");
		iter_dir(path, &dir, options);
		free(path);
		path = NULL;
	}
	return (0);
}
