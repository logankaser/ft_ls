/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quickSort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/25 19:48:59 by lkaser            #+#    #+#             */
/*   Updated: 2018/04/26 11:09:14 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

#define COMPARE(a, b) ((struct s_player*)a)->score > ((struct s_player*)b)->score

static int partition(void *array[], int lo , int hi)
{
	void *pivot;
	int i;
	int j;
	void *tmp;

	pivot = array[lo + (hi - lo) / 2];
	i = lo - 1;
	j = hi + 1;
	while (1)
	{
		++i;
		while (COMPARE(pivot, array[i]))
			++i;
		--j;
		while (COMPARE(array[j], pivot))
			--j;
		if (i >= j)
			return j;
		tmp = array[i];
		array[i] = array[j];
		array[j] = tmp;
	}
}

static void sort(void *array[], int lo, int hi)
{
	if (lo < hi)
	{
		int p = partition(array, lo, hi);
		sort(array, lo, p);
		sort(array, p + 1, hi);
	}
}

void quickSort(struct s_player** players)
{
	int len = 0;
	while (players[len])
		++len;
	--len;
	sort((void**)players, 0, len);
}
