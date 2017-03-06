/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructs3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpousse <lpousse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 12:11:04 by lpousse           #+#    #+#             */
/*   Updated: 2017/03/01 13:59:56 by jbourgin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			i_sti(t_arena *arena, t_proc *proc)
{
	unsigned char	val2[4];
	unsigned char	val3[4];
	int				addr;
	int				reg1;

	if (check_types(g_op_tab + 10, proc->codagebyte, proc->args))
	{
		reg1 = cw_char_to_int(proc->args[0]);
		get_val_by_type(arena, proc, 1, val2);
		get_val_by_type(arena, proc, 2, val3);
		addr = cw_char_to_int(val2) + cw_char_to_int(val3);
		cw_memcpy_to_arena(arena->memory, proc->reg[reg1 - 1],
								proc->pc + (addr % IDX_MOD), REG_SIZE);
		if (arena->verbose & 0x4)
		{
			ft_printf("P% 5d | sti r%d %d %d\n       | -> ",
				proc->nb, reg1, cw_char_to_int(val2), cw_char_to_int(val3));
			ft_printf("store to %d + %d = %d (with pc and mod %d)\n",
							cw_char_to_int(val2), cw_char_to_int(val3), addr,
												proc->pc + (addr % IDX_MOD));
		}
	}
}

void			i_fork(t_arena *arena, t_proc *proc)
{
	short int	dir;

	dir = cw_char_to_short(proc->args[0]);
	new_process(arena, mem_adr(proc->pc + dir % IDX_MOD), proc);
	if (arena->verbose & 0x4)
		ft_printf("P% 5d | fork %hd (%d)\n", proc->nb, dir, proc->pc +
																dir % IDX_MOD);
}

void			i_lld(t_arena *arena, t_proc *proc)
{
	int		param1;
	int		regnb;

	if (check_types(g_op_tab + 12, proc->codagebyte, proc->args))
	{
		param1 = cw_char_to_int(proc->args[0]);
		regnb = cw_char_to_int(proc->args[1]);
		if (proc->codagebyte >> 6 == DIR_CODE)
			ft_memcpy(proc->reg[regnb - 1], proc->args[0], REG_SIZE);
		else
		{
			param1 = (short int)param1;
			cw_memcpy_from_arena(proc->reg[regnb - 1] + 2, arena->memory,
									proc->pc + param1, IND_SIZE);
			cw_int_to_char(cw_char_to_short(proc->reg[regnb - 1]),
														proc->reg[regnb - 1]);
		}
		proc->carry = (param1 == 0 ? 1 : 0);
		if (arena->verbose & 0x4)
			ft_printf("P% 5d | lld %d r%d\n", proc->nb,
								cw_char_to_int(proc->reg[regnb - 1]), regnb);
	}
	else if (arena->invert == 0)
		proc->carry = 0;
}
