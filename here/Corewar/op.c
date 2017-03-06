/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaz <zaz@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/10/04 11:43:01 by zaz               #+#    #+#             */
/*   Updated: 2017/02/06 14:44:35 by lpousse          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"

t_op	g_op_tab[17] =
{
	{"live", 1, {T_DIR}, 1, 10, "alive", 0, 0},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 2, 5, "load", 1, 0},
	{"st", 2, {T_REG, T_IND | T_REG}, 3, 5, "store", 1, 0},
	{"add", 3, {T_REG, T_REG, T_REG}, 4, 10, "addition", 1, 0},
	{"sub", 3, {T_REG, T_REG, T_REG}, 5, 10, "soustraction", 1, 0},
	{"and", 3, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 6, 6,
		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0},
	{"or", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 7, 6,
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0},
	{"xor", 3, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 8, 6,
		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0},
	{"zjmp", 1, {T_DIR}, 9, 20, "jump if zero", 0, 1},
	{"ldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 10, 25,
		"load index", 1, 1},
	{"sti", 3, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 11, 25,
		"store index", 1, 1},
	{"fork", 1, {T_DIR}, 12, 800, "fork", 0, 1},
	{"lld", 2, {T_DIR | T_IND, T_REG}, 13, 10, "long load", 1, 0},
	{"lldi", 3, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 14, 50,
		"long load index", 1, 1},
	{"lfork", 1, {T_DIR}, 15, 1000, "long fork", 0, 1},
	{"aff", 1, {T_REG}, 16, 2, "aff", 1, 0},
	{0, 0, {0}, 0, 0, 0, 0, 0}
};

/*
** Sujet simplifie et trie :
**
** live : (opcode 1) permet a un processus et a son joueur de rester vivant
** ld : (opcode 2, carry) charge la valeur du 1er param dans le registre en 2nd
**      param
** st : (opcode 3) stocke la valeur du registre en 1er param dans le 2nd param
** add : (opcode 4, carry) additionnne les valeurs des deux 1ers registres,
**       stocke le resultat dans le 3eme
** sub : (opcode 5, carry) soustrait les valeurs des deux 1ers registres,
**       stocke le resultat dans le 3eme
** and : (opcode 6, carry) applique un & bit-a-bit sur les deux 1ers params,
**       stocke le resultat dans le 3eme
** or : (opcode 7, carry) applique un | bit-a-bit sur les deux 1ers params,
**      stocke le resultat dans le 3eme
** xor : (opcode 8, carry) applique un | exclusif bit-a-bit sur les deux 1ers
**       params, stocke le resultat dans le 3eme
** zjmp : (opcode 9) fait un saut a l'adresse fournie dans le 1er param si
**        carry == 1
** ldi : (opcode 10) additionne les deux 1ers params, utilise le resultat comme
**       une adresse, charge la valeur lu a cette adresse dans le registre en
**       3eme param
** sti : (opcode 11) additionne les deux derniers params, utilise le resultat
**       comme une adresse, y stocke la valeur du registre en 1er param
** fork : (opcode 12) Cree un nouveau processus qui herite des differents etats
**        de son pere, sauf son PC qui est mis a (PC + (1er param % IDX_MOD))
** lld : (opcode 13, carry) charge la valeur du 1er param dans le registre en
**       2nd param sans % IDX_MOD
** lldi : (opcode 14, carry) additionne les deux 1ers params, utilise le
**        resultat comme une adresse sans % IDX_MOD, charge la valeur lu a
**        cette adresse dans le registre en 3eme param
** lfork : (opcode 15) Cree un nouveau processus qui herite des differents
**         etats de son pere, sauf son PC qui est mis a (PC + 1er param)
** aff : (opcode 16) interprete la valeur dans le registre en parametre % 256
**       comme un caractere ascii qu'il affiche sur la sortie standard
*/
