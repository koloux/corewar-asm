/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructs1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpousse <lpousse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/23 12:06:05 by lpousse           #+#    #+#             */
/*   Updated: 2017/03/01 13:49:27 by jbourgin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

/*
** In order to compare with the initial VM, keep this sentence :
** ft_printf("Player %d (%s) is said to be alive\n", param,
** (arena->champions[i]).name);
*/

void			i_live(t_arena *arena, t_proc *proc)
{
	unsigned int	i;
	int				param;

	i = 0;
	(proc->live)++;
	proc->lastlive = arena->nb_cycles;
	(arena->nb_lives)++;
	param = cw_char_to_int(proc->args[0]);
	if (arena->verbose & 0x4)
		ft_printf("P% 5d | live %d\n", proc->nb, param);
	if (arena->invert == 1)
		param = -param;
	while (i < arena->nb_champions && (arena->champions[i]).nb != param)
		i++;
	if (i < arena->nb_champions)
	{
		arena->lastlive = param;
		if (arena->verbose & 0x1)
			ft_printf("Un processus dit que le joueur %d(\"%s\") est en vie\n",
											param, (arena->champions[i]).name);
	}
}

void			i_ld(t_arena *arena, t_proc *proc)
{
	int		param1;
	int		regnb;

	if (check_types(g_op_tab + 1, proc->codagebyte, proc->args))
	{
		param1 = cw_char_to_int(proc->args[0]);
		regnb = cw_char_to_int(proc->args[1]);
		if (proc->codagebyte >> 6 == DIR_CODE)
			ft_memcpy(proc->reg[regnb - 1], proc->args[0], REG_SIZE);
		else
		{
			param1 = (short int)param1;
			cw_memcpy_from_arena(proc->reg[regnb - 1], arena->memory,
									proc->pc + (param1 % IDX_MOD), DIR_SIZE);
		}
		proc->carry = (param1 == 0 ? 1 : 0);
		if (arena->verbose & 0x4)
			ft_printf("P% 5d | ld %d r%d\n", proc->nb,
								cw_char_to_int(proc->reg[regnb - 1]), regnb);
	}
	else if (arena->invert == 0)
		proc->carry = 0;
}

void			i_st(t_arena *arena, t_proc *proc)
{
	int		regnb;
	int		param2;

	if (check_types(g_op_tab + 2, proc->codagebyte, proc->args))
	{
		regnb = cw_char_to_int(proc->args[0]);
		param2 = cw_char_to_int(proc->args[1]);
		if ((proc->codagebyte >> 4 & 0b11) == REG_CODE)
			ft_memcpy(proc->reg[param2 - 1], proc->reg[regnb - 1], REG_SIZE);
		else
		{
			param2 = (short int)param2;
			cw_memcpy_to_arena(arena->memory, proc->reg[regnb - 1],
								proc->pc + (param2 % IDX_MOD), REG_SIZE);
		}
		if (arena->verbose & 0x4)
			ft_printf("P% 5d | st r%d %d\n", proc->nb, regnb, param2);
	}
}

void			i_add(t_arena *arena, t_proc *proc)
{
	int		reg1;
	int		reg2;
	int		reg3;
	int		add;

	if (check_types(g_op_tab + 3, proc->codagebyte, proc->args))
	{
		reg1 = cw_char_to_int(proc->args[0]);
		reg2 = cw_char_to_int(proc->args[1]);
		reg3 = cw_char_to_int(proc->args[2]);
		add = cw_char_to_int(proc->reg[reg1 - 1]) +
				cw_char_to_int(proc->reg[reg2 - 1]);
		cw_int_to_char(add, proc->reg[reg3 - 1]);
		proc->carry = (cw_char_to_int(proc->reg[reg3 - 1]) == 0 ? 1 : 0);
		if (arena->verbose & 0x4)
			ft_printf("P% 5d | add r%d r%d r%d\n", proc->nb, reg1, reg2, reg3);
	}
	else if (arena->invert == 0)
		proc->carry = 0;
}

void			i_sub(t_arena *arena, t_proc *proc)
{
	int		reg1;
	int		reg2;
	int		reg3;
	int		sub;

	if (check_types(g_op_tab + 4, proc->codagebyte, proc->args))
	{
		reg1 = cw_char_to_int(proc->args[0]);
		reg2 = cw_char_to_int(proc->args[1]);
		reg3 = cw_char_to_int(proc->args[2]);
		sub = cw_char_to_int(proc->reg[reg1 - 1]) -
				cw_char_to_int(proc->reg[reg2 - 1]);
		cw_int_to_char(sub, proc->reg[reg3 - 1]);
		proc->carry = (cw_char_to_int(proc->reg[reg3 - 1]) == 0 ? 1 : 0);
		if (arena->verbose & 0x4)
			ft_printf("P% 5d | sub r%d r%d r%d\n", proc->nb, reg1, reg2, reg3);
	}
	else if (arena->invert == 0)
		proc->carry = 0;
}
