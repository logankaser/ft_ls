#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include "libft.h"
#include "ft_ls.h"

void	iterate_directory(const char *path, t_list **directories)
{
	DIR* pwd;
	t_vector files;
	struct dirent* info;
	unsigned i;

	ft_vector_init(&files);
	pwd = opendir(path);
	while ((info = readdir(pwd)))
	{
		if (info->d_name[0] == '.')
			continue;
		ft_vector_push(&files, malloc(sizeof(t_file)));
		((t_file*)files.data[files.length - 1])->info = *info;
		lstat(info->d_name, &(((t_file*)files.data[files.length - 1])->meta));
	}
	i = 0;
	while (i < files.length)
		ft_putendl(((t_file*)files.data[i++])->info.d_name);
	(void)directories;
}

int	main(void)
{
	t_list **directories;

	directories = NULL;
	iterate_directory(".", directories);
	return (0);
}
