/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpousse <lpousse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 15:43:39 by lpousse           #+#    #+#             */
/*   Updated: 2017/03/01 13:29:04 by jbourgin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

void		error(int error, char *str)
{
	if (error >= 0)
		perror("error");
	else if (error == ERR_NBUSED)
		ft_putendl_fd("error: two champions can't have the same number", 2);
	else if (error == ERR_NOCHAMP)
		ft_putendl_fd("error: no champion", 2);
	else if (error == ERR_HEADER)
		ft_dprintf(2, "error: file %s has an invalid header\n", str);
	else if (error == ERR_SRCFILE)
		ft_dprintf(2, "error: can't read source file %s\n", str);
	else if (error == ERR_MUCHCHAMP)
		ft_putendl_fd("error: too many champions", 2);
	else if (error == ERR_CHAMPSIZE)
		ft_dprintf(2, "error: file %s has too large a code (> %d)\n", str,
						CHAMP_MAX_SIZE);
	else if (error == ERR_PROGSIZE)
		ft_dprintf(2, "error: file %s has a code %s", str,
						"size that differ from what its header says\n");
	exit(EXIT_FAILURE);
}

static void	introduce_champs(t_arena *arena)
{
	t_champ			champ;
	unsigned int	i;

	i = 0;
	ft_putendl("Introducing contestants...");
	while (i < arena->nb_champions)
	{
		champ = arena->champions[i];
		ft_printf("* Player %d, weighing %u bytes, \"%s\" (\"%s\") !\n",
					champ.nb, champ.program_len, champ.name, champ.comment);
		i++;
	}
}

static void	declare_winner(t_arena *arena)
{
	unsigned int	i;

	i = 0;
	while (i < arena->nb_champions
			&& (arena->champions[i]).nb != arena->lastlive)
		i++;
	ft_printf("Contestant %d, \"%s\", has won !\n", (arena->champions[i]).nb,
				(arena->champions[i]).name);
}

int			main(int ac, char **av)
{
	t_arena		arena;
	int			end;

	init_arena(&arena);
	parsing(ac, av, &arena);
	load_champions(&arena);
	introduce_champs(&arena);
	end = 0;
	if (arena.dump == 0)
	{
		dump_memory(arena.memory, MEM_SIZE);
		end = 2;
	}
	while (end < 1)
		end = cycle(&arena);
	kill_all_processes(&arena);
	if (end == 1)
		declare_winner(&arena);
	return (0);
}
