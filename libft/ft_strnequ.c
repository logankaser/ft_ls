/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 18:21:19 by lkaser            #+#    #+#             */
/*   Updated: 2017/09/22 11:52:18 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strnequ(char const *a, char const *b, size_t n)
{
	unsigned i;

	i = 0;
	if (a && b)
		while ((*a || *b) && i++ < n)
			if (*a++ != *b++)
				return (0);
	return (1);
}
