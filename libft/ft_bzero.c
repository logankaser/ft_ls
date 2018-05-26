/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 11:32:35 by lkaser            #+#    #+#             */
/*   Updated: 2018/05/25 19:18:31 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "libft.h"

void	ft_bzero(void *m, size_t size)
{
	unsigned bit;

	bit = 0;
	if (!(size % 8))
	{
		size /= 8;
		while (bit < size)
			((uint64_t*)m)[bit++] = 0;
	}
	else if (!(size % 4))
	{
		size /= 4;
		while (bit < size)
			((uint32_t*)m)[bit++] = 0;
	}
	else
		while (bit < size)
			((uint8_t*)m)[bit++] = 0;
}
