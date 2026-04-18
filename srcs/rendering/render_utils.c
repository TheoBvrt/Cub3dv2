/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 15:10:00 by theo              #+#    #+#             */
/*   Updated: 2026/04/18 14:13:56 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	my_mlx_pixel_put(t_image *image, int x, int y, int color)
{
	char	*dst;

	dst = image->addr + (y * image->line_length
			+ x * (image->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_verline(t_verline line, t_cube *cube)
{
	int	current_x;
	int	current_y;

	current_x = line.start_x;
	current_y = line.start_y;
	while (current_y < line.end_y)
	{
		my_mlx_pixel_put(cube->image, current_x, current_y, line.color);
		current_y++;
	}
}

void	calculate_deltatime(t_cube *cube)
{
	struct timeval	tv;
	double			curtime;

	gettimeofday(&tv, NULL);
	curtime = (double)tv.tv_sec + (double)tv.tv_usec / 1e6;
	cube->rendering.delta_time = curtime - cube->rendering.last_time;
	cube->rendering.last_time = curtime;
}

void	set_buffer(t_cube *cube, unsigned int buffer[1080][1920])
{
	int	y;
	int	x;
	int	pos;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			pos = (y * cube->image->line_length)
				+ (x * (cube->image->bits_per_pixel / 8));
			*(unsigned int *)(cube->image->addr + pos) = buffer[y][x];
			x++;
		}
		y++;
	}
}

void	set_values(t_cube *cube, t_raycasting *ray)
{
	ray->hit = 0;
	ray->camera_x = 2 * ray->x / (double)WIDTH - 1;
	ray->ray_dir_x = cube->rendering.dir_x
		+ cube->rendering.plane_x * ray->camera_x;
	ray->ray_dir_y = cube->rendering.dir_y
		+ cube->rendering.plane_y * ray->camera_x;
	ray->map_x = (int)cube->rendering.pos_x;
	ray->map_y = (int)cube->rendering.pos_y;
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
}
