/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_matclr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpousse <lpousse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/16 15:50:57 by lpousse           #+#    #+#             */
/*   Updated: 2016/03/17 16:53:34 by lpousse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_matclr(t_matrix *m)
{
	int i;
	int j;

	i = -1;
	while (++i < m->y)
	{
		j = -1;
		while (++j < m->x)
			(m->m)[i][j] = 0;
	}
}
