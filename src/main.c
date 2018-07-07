/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 20:12:36 by lkaser            #+#    #+#             */
/*   Updated: 2018/07/06 20:12:41 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int	parse_args(int8_t opts[], int argc, char **argv)
{
	int	i;
	int	j;

	ft_memset(opts, -1, 256);
	opts['R'] = 0;
	opts['a'] = 0;
	opts['l'] = 0;
	opts['r'] = 0;
	opts['t'] = 0;
	opts['1'] = 0;
	j = 0;
	while (++j < argc && argv[j][(i = 0)] == '-')
		while (argv[j][++i])
			if (ANY2(opts[(uint8_t)argv[j][i]], 0, 1))
				opts[(uint8_t)argv[j][i]] = 1;
			else
			{
				printf(USAGE, argv[j][i]);
				exit(1);
			}
	return (j);
}

int			main(int argc, char **argv)
{
	int8_t		opts[256];
	t_list		*dirs;
	t_file		*dir;
	int			i;

	dirs = NULL;
	i = parse_args(opts, argc, argv);
	if (i >= argc)
		iter_dir(".", &dirs, opts);
	while (i < argc)
	{
		ft_printf("%s: \n", argv[i]);
		iter_dir(argv[i], &dirs, opts);
		write(1, "\n", 1);
		++i;
	}
	while ((dir = ft_lstpop(&dirs)))
	{
		ft_printf("\n%s:\n", dir->path);
		iter_dir(dir->path, &dirs, opts);
		free(dir->path);
		free(dir);
	}
	return (0);
}
