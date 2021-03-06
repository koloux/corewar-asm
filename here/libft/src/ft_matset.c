/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpousse <lpousse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/18 14:37:49 by lpousse           #+#    #+#             */
/*   Updated: 2016/03/18 14:43:34 by lpousse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_matset(t_matrix *m, double **data)
{
	int		i;
	int		j;

	i = -1;
	while (++i < m->y)
	{
		j = -1;
		while (++j < m->x)
			(m->m)[i][j] = data[i][j];
	}
}
