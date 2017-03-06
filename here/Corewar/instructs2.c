/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructs2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpousse <lpousse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 12:07:26 by lpousse           #+#    #+#             */
/*   Updated: 2017/03/01 14:01:07 by jbourgin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			i_and(t_arena *arena, t_proc *proc)
{
	unsigned char	value1[REG_SIZE];
	unsigned char	value2[REG_SIZE];
	unsigned char	and[REG_SIZE];
	int				reg3;
	int				i;

	if (check_types(g_op_tab + 5, proc->codagebyte, proc->args))
	{
		reg3 = cw_char_to_int(proc->args[2]);
		get_val_by_type(arena, proc, 0, value1);
		get_val_by_type(arena, proc, 1, value2);
		i = -1;
		while (++i < REG_SIZE)
			and[i] = value1[i] & value2[i];
		ft_memcpy(proc->reg[reg3 - 1], and, REG_SIZE);
		proc->carry = (cw_char_to_int(proc->reg[reg3 - 1]) == 0 ? 1 : 0);
		if (arena->verbose & 0x4)
			ft_printf("P% 5d | and %d %d r%d\n", proc->nb,
						cw_char_to_int(value1), cw_char_to_int(value2), reg3);
	}
	else if (arena->invert == 0)
		proc->carry = 0;
}

void			i_or(t_arena *arena, t_proc *proc)
{
	unsigned char	value1[REG_SIZE];
	unsigned char	value2[REG_SIZE];
	unsigned char	or[REG_SIZE];
	int				reg3;
	int				i;

	if (check_types(g_op_tab + 6, proc->codagebyte, proc->args))
	{
		reg3 = cw_char_to_int(proc->args[2]);
		get_val_by_type(arena, proc, 0, value1);
		get_val_by_type(arena, proc, 1, value2);
		i = -1;
		while (++i < REG_SIZE)
			or[i] = value1[i] | value2[i];
		ft_memcpy(proc->reg[reg3 - 1], or, REG_SIZE);
		proc->carry = (cw_char_to_int(proc->reg[reg3 - 1]) == 0 ? 1 : 0);
		if (arena->verbose & 0x4)
			ft_printf("P% 5d | or %d %d r%d\n", proc->nb,
						cw_char_to_int(value1), cw_char_to_int(value2), reg3);
	}
	else if (arena->invert == 0)
		proc->carry = 0;
}

void			i_xor(t_arena *arena, t_proc *proc)
{
	unsigned char	value1[REG_SIZE];
	unsigned char	value2[REG_SIZE];
	unsigned char	xor[REG_SIZE];
	int				reg3;
	int				i;

	if (check_types(g_op_tab + 7, proc->codagebyte, proc->args))
	{
		reg3 = cw_char_to_int(proc->args[2]);
		get_val_by_type(arena, proc, 0, value1);
		get_val_by_type(arena, proc, 1, value2);
		i = -1;
		while (++i < REG_SIZE)
			xor[i] = value1[i] ^ value2[i];
		ft_memcpy(proc->reg[reg3 - 1], xor, REG_SIZE);
		proc->carry = (cw_char_to_int(proc->reg[reg3 - 1]) == 0 ? 1 : 0);
		if (arena->verbose & 0x4)
			ft_printf("P% 5d | xor %d %d r%d\n", proc->nb,
						cw_char_to_int(value1), cw_char_to_int(value2), reg3);
	}
	else if (arena->invert == 0)
		proc->carry = 0;
}

void			i_zjmp(t_arena *arena, t_proc *proc)
{
	short int	jump;

	jump = cw_char_to_short(proc->args[0]);
	if (proc->carry == 1)
		proc->pc = mem_adr(proc->pc + (jump % IDX_MOD) - 3);
	if (arena->verbose & 0x4)
	{
		ft_printf("P% 5d | zjmp %hd ", proc->nb, jump);
		proc->carry == 1 ? ft_putendl("OK") : ft_putendl("FAILED");
	}
}

void			i_ldi(t_arena *arena, t_proc *proc)
{
	unsigned char	val1[4];
	unsigned char	val2[4];
	int				addr;
	int				regnb;

	if (check_types(g_op_tab + 9, proc->codagebyte, proc->args))
	{
		regnb = cw_char_to_int(proc->args[2]);
		get_val_by_type(arena, proc, 0, val1);
		get_val_by_type(arena, proc, 1, val2);
		addr = cw_char_to_int(val1) + cw_char_to_int(val2);
		cw_memcpy_from_arena(proc->reg[regnb - 1], arena->memory,
									proc->pc + (addr % IDX_MOD), REG_SIZE);
		if (arena->verbose & 0x4)
		{
			ft_printf("P% 5d | ldi %d %d r%d\n       | -> ",
				proc->nb, cw_char_to_int(val1), cw_char_to_int(val2), regnb);
			ft_printf("load from %d + %d = %d (with pc and mod %d)\n",
							cw_char_to_int(val1), cw_char_to_int(val2), addr,
												proc->pc + (addr % IDX_MOD));
		}
	}
}
