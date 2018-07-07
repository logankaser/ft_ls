/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/25 17:49:46 by lkaser            #+#    #+#             */
/*   Updated: 2018/05/25 17:52:37 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_bool	sort_ascii(const void *a, const void *b)
{
	return (ft_strcmp(FILE(a)->name, FILE(b)->name) > 0);
}

t_bool	sort_ascii_r(const void *a, const void *b)
{
	return (ft_strcmp(FILE(b)->name, FILE(a)->name) > 0);
}

t_bool	sort_time(const void *a, const void *b)
{
	return (FILE(b)->meta.st_mtime > FILE(a)->meta.st_mtime);
}

t_bool	sort_time_r(const void *a, const void *b)
{
	return (FILE(a)->meta.st_mtime > FILE(b)->meta.st_mtime);
}

int		add_dir_sorted(t_list **dirs, t_file *dir,
		t_bool (*comp)(const void *, const void *))
{
	t_list *new;
	t_list *walk;

	if (!ft_strcmp(dir->name, ".") || !ft_strcmp(dir->name, "..")
		|| !(new = ft_lstnew(dir, sizeof(t_file))))
		return (0);
	if (!*dirs || comp((*dirs)->content, new->content)
		|| !comp(dir, (*dirs)->content))
	{
		new->next = *dirs;
		*dirs = new;
		return (1);
	}
	walk = *dirs;
	while (walk->next && comp(new->content, walk->next->content))
		walk = walk->next;
	new->next = walk->next;
	walk->next = new;
	return (1);
}
