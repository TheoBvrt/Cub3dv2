/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 15:18:00 by theo              #+#    #+#             */
/*   Updated: 2026/04/24 16:37:33 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	set_default_param(t_cube *cube)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	cube->rendering.last_time = (double)tv.tv_sec + (double)tv.tv_usec / 1e6;
	cube->rendering.dir_x = -1;
	cube->rendering.dir_y = 0;
	cube->rendering.plane_x = 0;
	cube->rendering.plane_y = 0.66;
	cube->keydown.key_a = 0;
	cube->keydown.key_s = 0;
	cube->keydown.key_d = 0;
	cube->keydown.key_w = 0;
	cube->keydown.key_right = 0;
	cube->keydown.key_left = 0;
	cube->parser.g_x = 0;
	cube->parser.g_y = 0;
	cube->parser.f_x = 0;
	cube->parser.f_y = 0;
}

int	init(t_cube *cube, t_image *image)
{
	set_default_param(cube);
	cube->mlx_win = mlx_new_window(cube->mlx, WIDTH, HEIGHT, "Cub3d");
	image->img = mlx_new_image(cube->mlx, WIDTH, HEIGHT);
	image->addr = mlx_get_data_addr(image->img, &image->bits_per_pixel,
			&image->line_length, &image->endian);
	cube->image = image;
	image_loader(cube);
	rotation_to(cube, cube->orientation);
	mlx_hook(cube->mlx_win, 2, (1L << 0), on_keydown, cube);
	mlx_hook(cube->mlx_win, 3, (1L << 1), on_keyrelease, cube);
	mlx_hook(cube->mlx_win, 17, 0L, on_cross_click, cube);
	mlx_loop_hook(cube->mlx, update, cube);
	mlx_loop(cube->mlx);
	return (1);
}
