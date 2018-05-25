#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>

#include "ft_ls.h"

static t_compare g_sorts[2][2] = {
	{sort_ascii, sort_ascii_r},
	{sort_time, sort_time_r}
};

void	iterate_directory(const char *path, t_list **dirs, int opts[])
{
	DIR				*pwd;
	t_vector		files;
	struct dirent	*info;
	unsigned		i;
	char			*tmp;
	t_file*			file;

	tmp = ft_strjoin(path, "/");
	ft_vector_init(&files);
	if (!(pwd = opendir(path)))
	{
		perror("ft_ls");
		return;
	}
	errno = 0;
	while ((info = readdir(pwd)))
	{
		if (info->d_name[0] == '.' && !opts['a'])
			continue;
		file = malloc(sizeof(t_file));
		ft_memcpy(file->name, info->d_name, NAME_MAX);
		lstat(ft_strjoin(tmp, info->d_name), &(file->meta));
		ft_vector_push(&files, file);
	}
	ft_qsort(files.data, files.length, g_sorts[opts['t']][opts['r']]);
	i = 0;
	while (i < files.length)
	{
		file = files.data[i];
		ft_putendl(file->name);
		if (S_ISDIR(file->meta.st_mode))
			ft_lstpush(dirs, ft_strjoin(tmp, file->name), 0);
		++i;
	}
	free(tmp);
	ft_vector_rm(&files);
	closedir(pwd);
}

int	main(int argc, char** argv)
{
	t_list	*dir;
	char	*path;
	int		options[127] = {0};
	int		i;

	path = argc - 1 > 0 && argv[argc - 1][0] != '-' ? argv[argc - 1] : NULL;
	while (--argc > 0)
		if (argv[argc][(i = 0)] == '-')
			while (argv[argc][++i])
				options[(int)argv[argc][i]] = 1;
	dir = NULL;
	iterate_directory(path ? path : ".", &dir, options);
	if (!options['R'])
		return 0;
	while ((path = ft_lstpop(&dir)))
	{
		ft_putstr("\033[34;1m");
		ft_putstr(path);
		ft_putendl("\033[0m");
		iterate_directory(path, &dir, options);
		free(path);
		path = NULL;
	}
	return (0);
}
