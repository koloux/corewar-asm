/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpousse <lpousse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 15:47:54 by lpousse           #+#    #+#             */
/*   Updated: 2017/03/01 14:00:55 by jbourgin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		reset_process_instructs(t_proc *proc)
{
	int		i;

	i = 0;
	proc->opcode = 0;
	proc->codagebyte = 0;
	while (i < MAX_ARGS_NUMBER)
	{
		ft_bzero(proc->args[i], REG_SIZE);
		i++;
	}
	proc->wait = 0;
	proc->towait = 0;
}

static int	new_process_nb(void)
{
	static int	proc_nb = 0;

	proc_nb++;
	return (proc_nb);
}

void		new_process(t_arena *arena, unsigned int pc, t_proc *inherit)
{
	t_proc	*new;
	int		i;

	new = (t_proc *)malloc(sizeof(t_proc));
	if (!new)
		error(errno, NULL);
	i = -1;
	while (++i < REG_NUMBER)
		ft_bzero(new->reg[i], REG_SIZE);
	new->nb = new_process_nb();
	new->pc = pc;
	new->carry = 0;
	new->live = 0;
	if (inherit != NULL)
	{
		i = -1;
		while (++i < REG_NUMBER)
			ft_memcpy(new->reg[i], inherit->reg[i], REG_SIZE);
		new->carry = inherit->carry;
		new->live = inherit->live;
		new->lastlive = inherit->lastlive;
	}
	reset_process_instructs(new);
	new->next = arena->processes;
	arena->processes = new;
}

t_proc		*kill_process(t_arena *arena, t_proc *todel, t_proc *prev)
{
	t_proc	*next;

	next = todel->next;
	if (prev != NULL)
		prev->next = next;
	else
		arena->processes = next;
	free(todel);
	return (next);
}

void		kill_all_processes(t_arena *arena)
{
	t_proc	*tmp;

	while (arena->processes != NULL)
	{
		tmp = arena->processes->next;
		free(arena->processes);
		arena->processes = tmp;
	}
}
