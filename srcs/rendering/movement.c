/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiribar <xiribar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 15:18:00 by theo              #+#    #+#             */
/*   Updated: 2026/04/17 15:18:00 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	forward(t_cube *cube)
{
	cube->rendering.posX += cube->rendering.dir_x
		* (MOVESPEED * cube->rendering.delta_time);
	cube->rendering.posY += cube->rendering.dir_y
		* (MOVESPEED * cube->rendering.delta_time);
}

void	backward(t_cube *cube)
{
	cube->rendering.posX -= cube->rendering.dir_x
		* (MOVESPEED * cube->rendering.delta_time);
	cube->rendering.posY -= cube->rendering.dir_y
		* (MOVESPEED * cube->rendering.delta_time);
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
