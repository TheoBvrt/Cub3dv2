/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 14:45:00 by theo              #+#    #+#             */
/*   Updated: 2026/04/18 13:23:07 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	buffer_fill(t_raycasting *ray, unsigned int b[1080][1920])
{
	int	y;
	int	tex_y;

	y = ray->draw_start;
	while (y <= ray->draw_end)
	{
		tex_y = (int)ray->text_pos & (64 - 1);
		ray->text_pos += ray->step;
		ray->color = *(int *)(ray->tex_data
				+ (tex_y * ray->sl + ray->tex_x * (ray->bpp / 8)));
		b[y][ray->x] = ray->color;
		y++;
	}
}

void	ray_calculator(t_cube *cube, t_raycasting *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = ray->side_dist_x - ray->delta_dist_x;
	else
		ray->perp_wall_dist = ray->side_dist_y - ray->delta_dist_y;
	ray->line_height = (int)(HEIGHT / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + HEIGHT / 2;
	if (ray->draw_end >= HEIGHT)
		ray->draw_end = HEIGHT - 1;
	if (ray->side == 0)
		ray->wall_x = cube->rendering.posY
			+ ray->perp_wall_dist * ray->ray_dir_y;
	else
		ray->wall_x = cube->rendering.posX
			+ ray->perp_wall_dist * ray->ray_dir_x;
	ray->wall_x -= floor(ray->wall_x);
	ray->tex_x = (int)(ray->wall_x * (double)64);
	if (ray->side == 0 && ray->ray_dir_x > 0)
		ray->tex_x = 64 - ray->tex_x - 1;
	ray->step = 1.0 * 64 / ray->line_height;
	ray->text_pos = (ray->draw_start - HEIGHT / 2 + ray->line_height / 2)
		* ray->step;
}

void	draw_ground_sky(t_cube *cube, unsigned int buffer[1080][1920])
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (y < HEIGHT / 2)
				buffer[y][x] = cube->rendering.c_color;
			else
				buffer[y][x] = cube->rendering.f_color;
			x ++;
		}
		y ++;
	}
}
