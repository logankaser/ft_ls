#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include "libft.h"
#include "ft_ls.h"

int	main(void)
{
	DIR* pwd;
	t_vector files;
	struct dirent* info;

	ft_vector_init(&files);
	pwd = opendir(".");
	while ((info = readdir(pwd)))
	{
		if (info->d_name[0] == '.')
			continue;
		ft_vector_push(&files, malloc(sizeof(t_file)));
		((t_file*)files.data[files.length - 1])->info = *info;
		lstat(info->d_name, &(((t_file*)files.data[files.length - 1])->meta));
	}

	for (unsigned i = 0; i < files.length; ++i)
	{
		ft_putstr(((t_file*)files.data[i])->info.d_name);
		ft_putchar('\t');
	}
	ft_putchar('\n');
}
