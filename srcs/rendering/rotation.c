/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 15:18:00 by theo              #+#    #+#             */
/*   Updated: 2026/04/24 16:28:07 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

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

void	rotation_to(t_cube *cube, int orientation)
{
	double	rotation_angle;
	double	old_dir_x;
	double	old_plane_x;

	if (orientation == E)
		rotation_angle = -3.14159265358979323846 / 2;
	if (orientation == W)
		rotation_angle = 3.14159265358979323846 / 2;
	if (orientation == S)
		rotation_angle = 3.14159265358979323846;
	if (orientation == N)
		return ;
	old_dir_x = cube->rendering.dir_x;
	cube->rendering.dir_x = cube->rendering.dir_x
		* cos(rotation_angle) - cube->rendering.dir_y * sin(rotation_angle);
	cube->rendering.dir_y = old_dir_x
		* sin(rotation_angle) + cube->rendering.dir_y * cos(rotation_angle);
	old_plane_x = cube->rendering.plane_x;
	cube->rendering.plane_x = cube->rendering.plane_x
		* cos(rotation_angle) - cube->rendering.plane_y * sin(rotation_angle);
	cube->rendering.plane_y = old_plane_x
		* sin(rotation_angle) + cube->rendering.plane_y * cos(rotation_angle);
}
