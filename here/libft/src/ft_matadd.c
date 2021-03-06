/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpousse <lpousse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 15:31:51 by lpousse           #+#    #+#             */
/*   Updated: 2016/03/17 16:57:12 by lpousse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_matrix	*ft_matadd(t_matrix *a, t_matrix *b)
{
	t_matrix	*result;
	int			i;
	int			j;

	if (a->x != b->x || a->y != b->y || !(result = ft_matnew(a->x, a->y)))
		return (NULL);
	i = -1;
	while (++i < result->y)
	{
		j = -1;
		while (++j < result->x)
			(result->m)[i][j] = (a->m)[i][j] + (b->m)[i][j];
	}
	return (result);
}
