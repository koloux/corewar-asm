/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpousse <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 19:50:22 by lpousse           #+#    #+#             */
/*   Updated: 2016/02/04 19:23:14 by lpousse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	if (n < 0)
		ft_putchar_fd('-', fd);
	if (n > 0)
		n = -n;
	if (n <= -10)
	{
		ft_putnbr_fd(-(n / 10), fd);
		ft_putnbr_fd((10 - (n % 10)) % 10, fd);
	}
	else
		ft_putchar_fd(-n + '0', fd);
}
