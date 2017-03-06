/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   battle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpousse <lpousse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 14:42:39 by lpousse           #+#    #+#             */
/*   Updated: 2017/03/01 13:57:07 by jbourgin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static void	check_processes(t_arena *arena, t_proc *processes)
{
	t_proc	*prev;

	prev = NULL;
	while (processes != NULL)
	{
		if (processes->live > 0)
		{
			processes->live = 0;
			prev = processes;
			processes = processes->next;
		}
		else
		{
			if (arena->verbose & 0x8)
				ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n",
					processes->nb, (arena->nb_cycles - processes->lastlive),
															arena->cycletodie);
			processes = kill_process(arena, processes, prev);
		}
	}
}

static int	end_cycle(t_arena *arena)
{
	if (arena->lastcheck + arena->cycletodie == arena->nb_cycles)
	{
		check_processes(arena, arena->processes);
		if (arena->processes == NULL)
			return (1);
		if (arena->nb_lives >= NBR_LIVE ||
			arena->checksnodelta >= MAX_CHECKS - 1)
		{
			if (CYCLE_DELTA >= arena->cycletodie)
				return (1);
			arena->cycletodie -= CYCLE_DELTA;
			if (arena->verbose & 0x2)
				ft_printf("Cycle to die is now %d\n", arena->cycletodie);
			arena->checksnodelta = 0;
		}
		else
			(arena->checksnodelta)++;
		arena->lastcheck = arena->nb_cycles;
		arena->nb_lives = 0;
	}
	return (0);
}

static void	get_instruct(t_arena *arena, t_proc *process)
{
	int				offset;
	unsigned int	i;

	offset = 1;
	if ((g_op_tab[process->opcode - 1]).param_coding == 1)
	{
		offset++;
		process->codagebyte = (arena->memory[mem_adr(process->pc + 1)]);
		i = 0;
		while (i < (g_op_tab[process->opcode - 1]).nbarg)
		{
			offset += get_one_param(arena, process, i, offset);
			i++;
		}
	}
	else
		get_one_param(arena, process, 0, offset);
}

static void	exec_process(t_arena *arena, t_proc *proc, t_instruct *instructs)
{
	if (proc->wait == 0)
	{
		if (arena->memory[mem_adr(proc->pc)] > 0
			&& arena->memory[mem_adr(proc->pc)] < 17)
		{
			proc->opcode = arena->memory[mem_adr(proc->pc)];
			proc->towait = (g_op_tab[proc->opcode - 1]).nbcycles;
			(proc->wait)++;
		}
		else
			proc->pc = mem_adr(proc->pc + 1);
	}
	else
		(proc->wait)++;
	if (proc->towait > 0 && proc->wait >= proc->towait)
	{
		get_instruct(arena, proc);
		instructs[proc->opcode - 1](arena, proc);
		proc->pc = advance_proc_pc(arena, proc);
		reset_process_instructs(proc);
	}
}

int			cycle(t_arena *arena)
{
	static t_instruct	instructs[17] = {&i_live, &i_ld, &i_st, &i_add, &i_sub,
										&i_and, &i_or, &i_xor, &i_zjmp, &i_ldi,
										&i_sti, &i_fork, &i_lld, &i_lldi,
										&i_lfork, &i_aff, NULL};
	t_proc				*process;

	(arena->nb_cycles)++;
	if (arena->verbose & 0x2)
		ft_printf("It is now cycle %d\n", arena->nb_cycles);
	process = arena->processes;
	while (process != NULL)
	{
		exec_process(arena, process, instructs);
		process = process->next;
	}
	if (arena->dump > 0 && arena->nb_cycles == (unsigned int)arena->dump)
	{
		dump_memory(arena->memory, MEM_SIZE);
		return (2);
	}
	if (end_cycle(arena) > 0)
		return (1);
	return (0);
}
