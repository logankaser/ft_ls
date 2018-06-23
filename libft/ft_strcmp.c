/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/20 09:35:25 by lkaser            #+#    #+#             */
/*   Updated: 2017/09/20 09:43:58 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *a, const char *b)
{
	while (*a || *b)
	{
		if (*a != *b)
			return (*(unsigned char *)a - *(unsigned char *)b);
		++a;
		++b;
	}
	return (0);
}
