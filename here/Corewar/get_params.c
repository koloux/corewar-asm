/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_params.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpousse <lpousse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/26 15:46:40 by lpousse           #+#    #+#             */
/*   Updated: 2017/03/01 13:59:06 by jbourgin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int			get_instruct_len(t_op *op, unsigned char codagebyte)
{
	unsigned int	i;
	unsigned char	type;
	int				len;

	i = 0;
	len = 2;
	while (i < op->nbarg)
	{
		type = (codagebyte >> ((3 - i) * 2)) & 0b11;
		if (type == REG_CODE)
			len++;
		else if (type == DIR_CODE)
			len += op->dir_size == 0 ? DIR_SIZE : IND_SIZE;
		else if (type == IND_CODE)
			len += IND_SIZE;
		i++;
	}
	return (len);
}

int			check_types(t_op *op, unsigned char codagebyte,
							unsigned char (*args)[REG_SIZE])
{
	unsigned int	i;
	unsigned char	type;
	unsigned char	verif;
	int				regnb;

	i = 0;
	while (i < op->nbarg)
	{
		verif = 0;
		type = (codagebyte >> ((3 - i) * 2)) & 0b11;
		if (type == REG_CODE)
		{
			regnb = cw_char_to_int(args[i]);
			if (regnb > 0 && regnb <= REG_NUMBER)
				verif = op->args_type[i] & T_REG;
		}
		else if (type == DIR_CODE)
			verif = op->args_type[i] & T_DIR;
		else if (type == IND_CODE)
			verif = op->args_type[i] & T_IND;
		if (!verif)
			return (0);
		i++;
	}
	return (1);
}

int			get_one_param(t_arena *arena, t_proc *proc, int i, int offset)
{
	int		size;
	int		type;

	size = 0;
	if ((g_op_tab[proc->opcode - 1]).param_coding == 0)
		type = DIR_CODE;
	else
		type = (proc->codagebyte >> ((3 - i) * 2)) & 0b11;
	if (type == REG_CODE)
		size = 1;
	else if (type == DIR_CODE)
		size = (g_op_tab[proc->opcode - 1]).dir_size == 0 ?
					DIR_SIZE : IND_SIZE;
	else if (type == IND_CODE)
		size = IND_SIZE;
	cw_memcpy_from_arena(proc->args[i] + REG_SIZE - size, arena->memory,
					proc->pc + offset, size);
	return (size);
}
