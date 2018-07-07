/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/25 17:49:34 by lkaser            #+#    #+#             */
/*   Updated: 2018/05/25 17:51:50 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <sys/stat.h>
# include <limits.h>
# include <dirent.h>
# include "libft.h"

# define FILE(x) ((t_file*)x)

# define USAGE "ft_ls: illegal option -%c, usage: ft_ls [-Ralrt1] [file ...]\n"

typedef struct		s_file
{
	char			*path;
	char			*name;
	struct stat		meta;
}					t_file;

t_bool				sort_ascii(const void *a, const void *b);
t_bool				sort_ascii_r(const void *a, const void *b);
t_bool				sort_time(const void *a, const void *b);
t_bool				sort_time_r(const void *a, const void *b);
int					add_dir_sorted(t_list **dirs, t_file *dir,
					t_bool (*comp)(const void *, const void *));
void				iter_dir(const char *path, t_list **dirs, int8_t opts[]);

#endif
