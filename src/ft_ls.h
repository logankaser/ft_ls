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

typedef struct		s_file
{
	char			name[NAME_MAX + 1];
	char			*path;
	struct stat		meta;
}					t_file;

t_bool				sort_ascii(const void *a, const void *b);
t_bool				sort_ascii_r(const void *a, const void *b);
t_bool				sort_time(const void *a, const void *b);
t_bool				sort_time_r(const void *a, const void *b);
t_list				*add_dir(t_list **dirs, void *dir_path,
					t_bool (*comp)(const void *, const void *));

#endif
