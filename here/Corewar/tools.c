/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpousse <lpousse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/18 18:03:34 by lpousse           #+#    #+#             */
/*   Updated: 2017/03/01 13:54:01 by jbourgin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			dump_memory(unsigned char *memory, unsigned int mem_size)
{
	unsigned char	buf[DUMP_BPL * 3 + 1];
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	ft_bzero(buf, DUMP_BPL * 3 + 1);
	while (i < mem_size)
	{
		buf[j] = memory[i] / 16 + (memory[i] / 16 < 10 ? '0' : 'a' - 10);
		buf[j + 1] = memory[i] % 16 + (memory[i] % 16 < 10 ? '0' : 'a' - 10);
		buf[j + 2] = ' ';
		i++;
		j += 3;
		if (i % DUMP_BPL == 0 || i == mem_size)
		{
			ft_printf("0x%.4x : %s\n", i >= DUMP_BPL ? i - DUMP_BPL : 0, buf);
			j = 0;
		}
	}
}

int				mem_adr(int pos)
{
	while (pos >= MEM_SIZE)
		pos -= MEM_SIZE;
	while (pos < 0)
		pos += MEM_SIZE;
	return (pos);
}

unsigned char	*cw_memcpy_from_arena(unsigned char *dst, unsigned char *arena,
							int a_start, int n)
{
	int		i;

	i = 0;
	while (i < n)
	{
		dst[i] = arena[mem_adr(a_start + i)];
		i++;
	}
	return (dst);
}

unsigned char	*cw_memcpy_to_arena(unsigned char *arena, unsigned char *src,
							int a_start, int n)
{
	int		i;

	i = 0;
	while (i < n)
	{
		arena[mem_adr(a_start + i)] = src[i];
		i++;
	}
	return (arena + mem_adr(a_start));
}
