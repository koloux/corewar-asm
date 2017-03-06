/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpousse <lpousse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 15:00:51 by lpousse           #+#    #+#             */
/*   Updated: 2017/03/01 13:31:43 by jbourgin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		init_arena(t_arena *arena)
{
	t_champ	champ;
	int		i;

	ft_bzero(arena->memory, MEM_SIZE);
	arena->nb_cycles = 0;
	arena->dump = -1;
	arena->cycletodie = CYCLE_TO_DIE;
	arena->lastcheck = 0;
	arena->nb_lives = 0;
	arena->checksnodelta = 0;
	arena->verbose = 1;
	arena->invert = 0;
	arena->nb_champions = 0;
	i = 0;
	while (i < MAX_PLAYERS)
	{
		champ = arena->champions[i];
		ft_bzero(champ.name, PROG_NAME_LENGTH + 1);
		ft_bzero(champ.comment, COMMENT_LENGTH + 1);
		champ.nb = 0;
		champ.program_len = 0;
		ft_bzero(champ.program, CHAMP_MAX_SIZE + 1);
		i++;
	}
	arena->processes = NULL;
}

static void	init_reg1(t_proc *proc, int nb, t_arena *arena)
{
	if (arena->invert == 1)
		nb = -nb;
	if (REG_SIZE >= 4)
		proc->reg[0][REG_SIZE - 4] = nb >> 24;
	if (REG_SIZE >= 3)
		proc->reg[0][REG_SIZE - 3] = (nb >> 16) & 0xff;
	if (REG_SIZE >= 2)
		proc->reg[0][REG_SIZE - 2] = (nb >> 8) & 0xff;
	if (REG_SIZE >= 1)
		proc->reg[0][REG_SIZE - 1] = nb & 0xff;
}

static void	init_processes(t_arena *arena, unsigned int *pcs)
{
	unsigned int	i;
	unsigned int	j;
	int				min;
	int				champ;

	i = 0;
	min = 0;
	while (i < arena->nb_champions)
	{
		j = 0;
		champ = -1;
		while (j < arena->nb_champions)
		{
			if (((arena->champions[j]).nb > min || i == 0) && (champ < 0
				|| (arena->champions[j]).nb < (arena->champions[champ]).nb))
				champ = j;
			j++;
		}
		new_process(arena, pcs[champ], NULL);
		init_reg1(arena->processes, (arena->champions[champ]).nb, arena);
		min = (arena->champions[champ]).nb;
		if (i == 0)
			arena->lastlive = min;
		i++;
	}
}

void		load_champions(t_arena *arena)
{
	t_champ			*champ;
	unsigned int	pcs[MAX_PLAYERS];
	unsigned int	part;
	unsigned int	i;

	i = 0;
	part = MEM_SIZE / arena->nb_champions;
	while (i < arena->nb_champions)
	{
		champ = &(arena->champions[i]);
		ft_memcpy(arena->memory + i * part, champ->program, champ->program_len);
		pcs[i] = i * part;
		i++;
	}
	init_processes(arena, pcs);
}
