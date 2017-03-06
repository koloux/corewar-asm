/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpousse <lpousse@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 15:43:20 by lpousse           #+#    #+#             */
/*   Updated: 2017/03/01 13:56:18 by jbourgin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include <fcntl.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include "op.h"
# include "libft.h"

# define ERR_NBUSED -1
# define ERR_NOCHAMP -2
# define ERR_HEADER -3
# define ERR_SRCFILE -4
# define ERR_MUCHCHAMP -5
# define ERR_CHAMPSIZE -6
# define ERR_PROGSIZE -7

# define DUMP_BPL 32

typedef struct	s_proc
{
	unsigned char	reg[REG_NUMBER][REG_SIZE];
	unsigned int	pc;
	unsigned char	carry;
	unsigned int	live;
	unsigned int	lastlive;
	unsigned int	nb;

	unsigned char	opcode;
	unsigned char	codagebyte;
	unsigned char	args[MAX_ARGS_NUMBER][REG_SIZE];
	unsigned int	wait;
	unsigned int	towait;

	struct s_proc	*next;
}				t_proc;

typedef struct	s_champ
{
	char			name[PROG_NAME_LENGTH + 1];
	char			comment[COMMENT_LENGTH + 1];
	int				nb;
	unsigned int	program_len;
	unsigned char	program[CHAMP_MAX_SIZE + 1];
}				t_champ;

typedef struct	s_arena
{
	unsigned char	memory[MEM_SIZE];
	unsigned int	nb_cycles;
	int				dump;
	unsigned int	cycletodie;
	unsigned int	lastcheck;
	unsigned int	nb_lives;
	unsigned int	checksnodelta;
	int				lastlive;
	t_champ			champions[MAX_PLAYERS];
	unsigned int	nb_champions;
	t_proc			*processes;
	int				verbose;
	int				invert;
}				t_arena;

extern t_op		g_op_tab[17];

typedef void	(*t_instruct)(t_arena *, t_proc *);

void			parsing(int ac, char **av, t_arena *arena);
void			error(int error, char *str);
void			dump_memory(unsigned char *memory, unsigned int mem_size);

void			init_arena(t_arena *arena);
void			load_champions(t_arena *arena);

int				cycle(t_arena *arena);
int				get_one_param(t_arena *arena, t_proc *proc, int i, int offset);
int				check_types(t_op *op, unsigned char codagebyte,
								unsigned char (*args)[REG_SIZE]);
int				get_instruct_len(t_op *op, unsigned char codagebyte);
int				cw_char_to_int(unsigned char *c);
short int		cw_char_to_short(unsigned char *c);
void			cw_int_to_char(int nb, unsigned char *buf);
unsigned int	advance_proc_pc(t_arena *arena, t_proc *proc);

void			i_live(t_arena *arena, t_proc *proc);
void			i_ld(t_arena *arena, t_proc *proc);
void			i_st(t_arena *arena, t_proc *proc);
void			i_add(t_arena *arena, t_proc *proc);
void			i_sub(t_arena *arena, t_proc *proc);
void			i_and(t_arena *arena, t_proc *proc);
void			i_or(t_arena *arena, t_proc *proc);
void			i_xor(t_arena *arena, t_proc *proc);
void			i_zjmp(t_arena *arena, t_proc *proc);
void			i_ldi(t_arena *arena, t_proc *proc);
void			i_sti(t_arena *arena, t_proc *proc);
void			i_fork(t_arena *arena, t_proc *proc);
void			i_lld(t_arena *arena, t_proc *proc);
void			i_lldi(t_arena *arena, t_proc *proc);
void			i_lfork(t_arena *arena, t_proc *proc);
void			i_aff(t_arena *arena, t_proc *proc);

/*
** //!\\ a chaque fois que vous voulez utiliser un index dans la memoire de la
** VM, passez-le dans cette fonction, elle s'occupe de la circularité de la
** mémoire
*/
int				mem_adr(int pos);
unsigned char	*cw_memcpy_from_arena(unsigned char *dst, unsigned char *arena,
							int a_start, int n);
unsigned char	*cw_memcpy_to_arena(unsigned char *arena, unsigned char *src,
							int a_start, int n);
void			get_val_by_type(t_arena *arena, t_proc *proc,
							int num_arg, unsigned char *value);

void			new_process(t_arena *arena, unsigned int pc, t_proc *inherit);
void			reset_process_instructs(t_proc *proc);
t_proc			*kill_process(t_arena *arena, t_proc *todel, t_proc *prev);
void			kill_all_processes(t_arena *arena);

#endif
