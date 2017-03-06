/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbourgin <jbourgin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 11:39:36 by jbourgin          #+#    #+#             */
/*   Updated: 2017/03/01 14:03:25 by jbourgin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void			cw_int_to_char(int nb, unsigned char *buf)
{
	int		i;
	int		offset;

	i = 0;
	offset = 24;
	while (i < 4)
	{
		buf[i] = (nb >> offset) & 0xff;
		i++;
		offset -= 8;
	}
}

short int		cw_char_to_short(unsigned char *c)
{
	short int	ret;

	ret = c[3] + c[2] * 0x100;
	return (ret);
}

int				cw_char_to_int(unsigned char *c)
{
	int		ret;
	int		i;
	int		offset;

	i = REG_SIZE;
	ret = 0;
	offset = 1;
	while (i > 0)
	{
		i--;
		ret += c[i] * offset;
		offset *= 0x100;
	}
	return (ret);
}

void			get_val_by_type(t_arena *arena, t_proc *proc,
							int num_arg, unsigned char *value)
{
	int		param;
	int		tmp;

	param = cw_char_to_int(proc->args[num_arg]);
	if (((proc->codagebyte >> ((3 - num_arg) * 2)) & 0b11) == DIR_CODE)
	{
		if (g_op_tab[proc->opcode - 1].param_coding == 1)
		{
			tmp = (int)cw_char_to_short(proc->args[num_arg]);
			cw_int_to_char(tmp, proc->args[num_arg]);
		}
		ft_memcpy(value, proc->args[num_arg], DIR_SIZE);
	}
	else if (((proc->codagebyte >> ((3 - num_arg) * 2)) & 0b11) == REG_CODE)
		ft_memcpy(value, proc->reg[param - 1], REG_SIZE);
	else if (((proc->codagebyte >> ((3 - num_arg) * 2)) & 0b11) == IND_CODE)
	{
		param = (short int)param;
		cw_memcpy_from_arena(value, arena->memory,
									proc->pc + (param % IDX_MOD), REG_SIZE);
	}
}

unsigned int	advance_proc_pc(t_arena *arena, t_proc *proc)
{
	unsigned int	adv;
	unsigned int	diff;
	unsigned int	i;

	if ((g_op_tab[proc->opcode - 1]).param_coding == 0)
		adv = mem_adr(proc->pc + 1 +
					((g_op_tab[proc->opcode - 1]).dir_size ? 2 : DIR_SIZE));
	else
		adv = mem_adr(proc->pc + get_instruct_len(g_op_tab +
										proc->opcode - 1, proc->codagebyte));
	if ((arena->verbose & 0x10) && proc->opcode && (proc->opcode != 9 ||
									(proc->opcode == 9 && proc->carry == 0)))
	{
		diff = mem_adr(adv - proc->pc);
		i = 0;
		ft_printf("ADV %d (0x%.4x -> 0x%.4x) ", diff, proc->pc,
															proc->pc + diff);
		while (i < diff)
		{
			ft_printf("%.2x ", arena->memory[mem_adr(proc->pc + i)]);
			i++;
		}
		ft_putchar('\n');
	}
	return (adv);
}
