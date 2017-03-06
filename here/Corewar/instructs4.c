/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructs4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpousse <lpousse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 12:11:50 by lpousse           #+#    #+#             */
/*   Updated: 2017/03/01 13:59:41 by jbourgin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			i_lldi(t_arena *arena, t_proc *proc)
{
	unsigned char	val1[4];
	unsigned char	val2[4];
	int				addr;
	int				regnb;

	if (check_types(g_op_tab + 13, proc->codagebyte, proc->args))
	{
		regnb = cw_char_to_int(proc->args[2]);
		get_val_by_type(arena, proc, 0, val1);
		get_val_by_type(arena, proc, 1, val2);
		addr = cw_char_to_int(val1) + cw_char_to_int(val2);
		cw_memcpy_from_arena(proc->reg[regnb - 1], arena->memory,
									proc->pc + addr, REG_SIZE);
		proc->carry = (cw_char_to_int(proc->reg[regnb - 1]) == 0 ? 1 : 0);
		if (arena->verbose & 0x4)
		{
			ft_printf("P% 5d | lldi %d %d r%d\n       | -> ",
				proc->nb, cw_char_to_int(val1), cw_char_to_int(val2), regnb);
			ft_printf("load from %d + %d = %d (with pc %d)\n",
			cw_char_to_int(val1), cw_char_to_int(val2), addr, proc->pc + addr);
		}
	}
	else if (arena->invert == 0)
		proc->carry = 0;
}

void			i_lfork(t_arena *arena, t_proc *proc)
{
	short int	dir;

	dir = cw_char_to_short(proc->args[0]);
	new_process(arena, mem_adr(proc->pc + dir), proc);
	if (arena->verbose & 0x4)
		ft_printf("P% 5d | lfork %hd (%d)\n", proc->nb, dir, proc->pc + dir);
}

void			i_aff(t_arena *arena, t_proc *proc)
{
	int		regnb;
	char	aff;

	if (check_types(g_op_tab + 15, proc->codagebyte, proc->args))
	{
		(void)arena;
		regnb = cw_char_to_int(proc->args[0]);
		aff = (char)cw_char_to_int(proc->reg[regnb - 1]);
		ft_printf("Aff: %c\n", aff);
	}
}
