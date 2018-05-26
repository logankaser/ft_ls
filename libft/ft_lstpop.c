/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstpop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 19:50:45 by lkaser            #+#    #+#             */
/*   Updated: 2018/05/25 17:34:30 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_lstpop(t_list **lst)
{
	t_list	*tmp;
	void	*content;

	content = NULL;
	if (*lst)
	{
		tmp = *lst;
		*lst = tmp->next;
		content = tmp->content;
		free(tmp);
	}
	return (content);
}
