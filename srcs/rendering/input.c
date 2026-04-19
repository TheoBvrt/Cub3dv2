/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiribar <xiribar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 15:10:00 by theo              #+#    #+#             */
/*   Updated: 2026/04/17 15:10:00 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	update(t_cube *cube)
{
	if (cube->keydown.key_w == 1)
		forward(cube);
	if (cube->keydown.key_s == 1)
		backward(cube);
	if (cube->keydown.key_a == 1)
		left(cube);
	if (cube->keydown.key_d == 1)
		right(cube);
	if (cube->keydown.key_right == 1)
		turn_right(cube);
	if (cube->keydown.key_left == 1)
		turn_left(cube);
	raycasting(cube, &cube->ray);
	return (0);
}

int	on_keydown(int keycode, t_cube *cube)
{
	if (keycode == W_KEY)
		cube->keydown.key_w = 1;
	if (keycode == S_KEY)
		cube->keydown.key_s = 1;
	if (keycode == A_KEY)
		cube->keydown.key_a = 1;
	if (keycode == D_KEY)
		cube->keydown.key_d = 1;
	if (keycode == RIGHT_ARROW)
		cube->keydown.key_right = 1;
	if (keycode == LEFT_ARROW)
		cube->keydown.key_left = 1;
	if (keycode == ESCAPE)
		exit_cub3d(cube);
	return (1);
}

int	on_keyrelease(int keycode, t_cube *cube)
{
	if (keycode == W_KEY)
		cube->keydown.key_w = 0;
	if (keycode == S_KEY)
		cube->keydown.key_s = 0;
	if (keycode == A_KEY)
		cube->keydown.key_a = 0;
	if (keycode == D_KEY)
		cube->keydown.key_d = 0;
	if (keycode == RIGHT_ARROW)
		cube->keydown.key_right = 0;
	if (keycode == LEFT_ARROW)
		cube->keydown.key_left = 0;
	return (1);
}

int	on_cross_click(t_cube *cube)
{
	exit_cub3d(cube);
	return (1);
}
