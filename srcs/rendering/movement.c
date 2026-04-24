/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 15:18:00 by theo              #+#    #+#             */
/*   Updated: 2026/04/24 16:26:17 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	forward(t_cube *cube)
{
	double	move;

	move = MOVESPEED * cube->rendering.delta_time;
	if (cube->rendering.map[(int)(cube->rendering.pos_x + cube->rendering.dir_x
			* move)][(int)(cube->rendering.pos_y)] == 0)
		cube->rendering.pos_x += cube->rendering.dir_x * move;
	if (cube->rendering.map[(int)(cube->rendering.pos_x)]
		[(int)(cube->rendering.pos_y + cube->rendering.dir_y * move)] == 0)
		cube->rendering.pos_y += cube->rendering.dir_y * move;
}

void	backward(t_cube *cube)
{
	double	move;

	move = (MOVESPEED * cube->rendering.delta_time) * -1;
	if (cube->rendering.map[(int)(cube->rendering.pos_x + cube->rendering.dir_x
			* move)][(int)(cube->rendering.pos_y)] == 0)
		cube->rendering.pos_x += cube->rendering.dir_x * move;
	if (cube->rendering.map[(int)(cube->rendering.pos_x)]
		[(int)(cube->rendering.pos_y + cube->rendering.dir_y * move)] == 0)
		cube->rendering.pos_y += cube->rendering.dir_y * move;
}

void	right(t_cube *cube)
{
	double	move;

	move = MOVESPEED * cube->rendering.delta_time;
	if (cube->rendering.map[(int)(cube->rendering.pos_x + cube->rendering.dir_y
			* move)][(int)(cube->rendering.pos_y)] == 0)
		cube->rendering.pos_x += cube->rendering.dir_y * move;
	if (cube->rendering.map[(int)(cube->rendering.pos_x)]
		[(int)(cube->rendering.pos_y
		+ (cube->rendering.dir_x * -1) * move)] == 0)
		cube->rendering.pos_y += (cube->rendering.dir_x * -1) * move;
}

void	left(t_cube *cube)
{
	double	move;

	move = MOVESPEED * cube->rendering.delta_time;
	if (cube->rendering.map[(int)(cube->rendering.pos_x
			+ (cube->rendering.dir_y * -1)
			* move)][(int)(cube->rendering.pos_y)] == 0)
		cube->rendering.pos_x += (cube->rendering.dir_y * -1) * move;
	if (cube->rendering.map[(int)(cube->rendering.pos_x)]
		[(int)(cube->rendering.pos_y + cube->rendering.dir_x * move)] == 0)
		cube->rendering.pos_y += cube->rendering.dir_x * move;
}
