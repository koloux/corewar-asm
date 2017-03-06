/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpousse <lpousse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 17:55:54 by lpousse           #+#    #+#             */
/*   Updated: 2017/03/01 13:52:59 by jbourgin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static int	is_nb_used(t_arena *arena, int nb)
{
	unsigned int	i;

	i = 0;
	while (i < arena->nb_champions)
	{
		if (nb == (arena->champions[i]).nb)
			return (-1);
		i++;
	}
	return (0);
}

static int	get_champion_nb(t_arena *arena, int ac, char **av, int *i)
{
	int		champnb;

	if (*i + 1 < ac && ft_strcmp(av[*i], "-n") == 0)
	{
		champnb = ft_atoi(av[*i + 1]);
		(*i) += 2;
		if (is_nb_used(arena, champnb) < 0)
			error(ERR_NBUSED, NULL);
	}
	else
	{
		champnb = 1;
		while (is_nb_used(arena, champnb) < 0)
			champnb++;
	}
	return (champnb);
}

static int	get_header(t_champ *champ, int fd, char *filename)
{
	unsigned char	buf[4];

	if (read(fd, buf, 4) < 0)
		error(errno, NULL);
	if ((buf[0] << 24) + (buf[1] << 16) + (buf[2] << 8)
		+ buf[3] != COREWAR_EXEC_MAGIC)
		return (-1);
	if (read(fd, champ->name, PROG_NAME_LENGTH + 1) < 0)
		error(errno, NULL);
	lseek(fd, 4 - ((PROG_NAME_LENGTH + 1) % 4), SEEK_CUR);
	if (read(fd, buf, 4) < 0)
		error(errno, NULL);
	champ->program_len = (buf[0] << 24) + (buf[1] << 16)
								+ (buf[2] << 8) + buf[3];
	if (champ->program_len > CHAMP_MAX_SIZE)
		error(ERR_CHAMPSIZE, filename);
	if (read(fd, champ->comment, COMMENT_LENGTH + 1) < 0)
		error(errno, NULL);
	lseek(fd, 4 - ((COMMENT_LENGTH + 1) % 4), SEEK_CUR);
	return (0);
}

static void	get_champion(t_arena *arena, char *filename, int champnb)
{
	t_champ	*champ;
	char	buf[1];
	int		fd;
	int		ret;

	if (arena->nb_champions >= MAX_PLAYERS)
		error(ERR_MUCHCHAMP, NULL);
	champ = &(arena->champions[arena->nb_champions]);
	champ->nb = champnb;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error(ERR_SRCFILE, filename);
	if (get_header(champ, fd, filename) < 0)
		error(ERR_HEADER, filename);
	if ((ret = read(fd, champ->program, champ->program_len)) < 0)
		error(errno, NULL);
	if (read(fd, buf, 1) != 0 || (unsigned int)ret != champ->program_len)
		error(ERR_PROGSIZE, filename);
	close(fd);
	(arena->nb_champions)++;
}

void		parsing(int ac, char **av, t_arena *arena)
{
	int		i;
	int		champnb;

	i = 0;
	while (++i < ac)
	{
		if (i + 1 < ac && ft_strcmp(av[i], "-dump") == 0)
			arena->dump = ft_atoi(av[++i]);
		else if (i + 1 < ac && ft_strcmp(av[i], "-v") == 0)
			arena->verbose = ft_atoi(av[++i]);
		else if (ft_strcmp(av[i], "-i") == 0)
			arena->invert = 1;
		else
		{
			champnb = get_champion_nb(arena, ac, av, &i);
			if (i < ac)
				get_champion(arena, av[i], champnb);
		}
	}
	if (arena->nb_champions == 0)
		error(ERR_NOCHAMP, NULL);
}
