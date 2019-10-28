/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cr_vis.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vrichese <vrichese@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/12 13:55:06 by vrichese          #+#    #+#             */
/*   Updated: 2019/10/28 16:42:00 by vrichese         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CR_VIS_H
# define CR_VIS_H

# include <math.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "libft.h"
# include <ncurses.h>
# include <locale.h>
# include <time.h>
# include "cwGameObject.h"

/*
** ---------------------------
** Visual defines
*/

# define V_W 260
# define V_H 68
# define V_BSYM "\xe2\x96\x88"
# define V_BHALF "\xe2\x96\x93"
# define V_BQUARTER "\xe2\x96\x91"
# define V_SEP 200

/*
** ---------------------------
*/

/*
** ---------------------------
** Visual typedefs
*/

typedef struct			s_vis
{
	int					flow;
	int					step;
	int					exit;
	int					tick;
	int					fpsdiv;
	unsigned char		*field;
	long int			time;

}						t_vis;

enum						e_vis_act
{
	V_INIT,								// initialise the matp
	V_CONTROL,							// update time and check key input
	V_UPDATE,							// update the map (left section)
	V_CLEANUP							// clean allocated memory and get rid of the visuals
};

/*
** ---------------------------
*/

/*
** ---------------------------
** Visual declarations
*/

int							cr_vis_main					(corewar_t *cr, int act);
int							cr_vis_cleanup				(corewar_t *cr);
int							cr_vis_printattr			(int y, int x, char *str, int colour, int reverse);
int							cr_vis_initvis				(corewar_t *cr);
int							cr_vis_initcolour			(void);
int							cr_vis_initterm				(void);
void						cr_vis_putx					(int num, int i, int colour, int rev, corewar_t *cr);
int							cr_vis_drawborder			(void);
int							cr_vis_printmap				(unsigned char *f, int f_len, corewar_t *cr);
int							cr_vis_timer				(corewar_t *cr);
int							cr_vis_keys					(corewar_t *cr);
int							cr_vis_updatemap			(corewar_t *cr);
int							cr_vis_printinfo			(corewar_t *cr);

/*
** ---------------------------
*/

#endif