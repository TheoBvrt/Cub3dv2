/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 15:18:00 by theo              #+#    #+#             */
/*   Updated: 2026/04/18 13:46:12 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	forward(t_cube *cube)
{
	double	move;

	move = MOVESPEED * cube->rendering.delta_time;
	if (cube->rendering.map[(int)(cube->rendering.posX + cube->rendering.dir_x
		* move)][(int)(cube->rendering.posY)] == 0)
			cube->rendering.posX += cube->rendering.dir_x * move;
	if (cube->rendering.map[(int)(cube->rendering.posX)]
		[(int)(cube->rendering.posY + cube->rendering.dir_y * move)] == 0)
			cube->rendering.posY += cube->rendering.dir_y * move;
}

void	backward(t_cube *cube)
{
	double	move;

	move = (MOVESPEED * cube->rendering.delta_time) * -1;
	if (cube->rendering.map[(int)(cube->rendering.posX + cube->rendering.dir_x
		* move)][(int)(cube->rendering.posY)] == 0)
			cube->rendering.posX += cube->rendering.dir_x * move;
	if (cube->rendering.map[(int)(cube->rendering.posX)]
		[(int)(cube->rendering.posY + cube->rendering.dir_y * move)] == 0)
			cube->rendering.posY += cube->rendering.dir_y * move;
}

void	turn_left(t_cube *cube)
{
	double	old_dir_x;
	double	old_plane_x;
	double	rot;

	rot = TURNSPEED * cube->rendering.delta_time;
	old_dir_x = cube->rendering.dir_x;
	cube->rendering.dir_x = cube->rendering.dir_x * cos(rot)
		- cube->rendering.dir_y * sin(rot);
	cube->rendering.dir_y = old_dir_x * sin(rot)
		+ cube->rendering.dir_y * cos(rot);
	old_plane_x = cube->rendering.plane_x;
	cube->rendering.plane_x = cube->rendering.plane_x * cos(rot)
		- cube->rendering.plane_y * sin(rot);
	cube->rendering.plane_y = old_plane_x * sin(rot)
		+ cube->rendering.plane_y * cos(rot);
}

void	turn_right(t_cube *cube)
{
	double	old_dir_x;
	double	old_plane_x;
	double	rot;

	rot = -TURNSPEED * cube->rendering.delta_time;
	old_dir_x = cube->rendering.dir_x;
	cube->rendering.dir_x = cube->rendering.dir_x * cos(rot)
		- cube->rendering.dir_y * sin(rot);
	cube->rendering.dir_y = old_dir_x * sin(rot)
		+ cube->rendering.dir_y * cos(rot);
	old_plane_x = cube->rendering.plane_x;
	cube->rendering.plane_x = cube->rendering.plane_x * cos(rot)
		- cube->rendering.plane_y * sin(rot);
	cube->rendering.plane_y = old_plane_x * sin(rot)
		+ cube->rendering.plane_y * cos(rot);
}
