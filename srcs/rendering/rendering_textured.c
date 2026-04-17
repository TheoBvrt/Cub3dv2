/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_textured.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 15:02:00 by theo              #+#    #+#             */
/*   Updated: 2026/04/17 15:02:00 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	image_loader(t_cube *cube)
{
	cube->textures.north = mlx_xpm_file_to_image(cube->mlx,
			"textures/basalt.xpm", &cube->textures.pw, &cube->textures.ph);
	cube->textures.south = mlx_xpm_file_to_image(cube->mlx,
			"textures/basalt.xpm", &cube->textures.pw, &cube->textures.ph);
	cube->textures.east = mlx_xpm_file_to_image(cube->mlx,
			"textures/basalt.xpm", &cube->textures.pw, &cube->textures.ph);
	cube->textures.west = mlx_xpm_file_to_image(cube->mlx,
			"textures/basalt.xpm", &cube->textures.pw, &cube->textures.ph);
}

void	texture_selector(t_cube *cube, t_raycasting *ray)
{
	if (cube->rendering.map[ray->map_x][ray->map_y] == 1)
	{
		if (ray->side == 0)
		{
			if (ray->ray_dir_x > 0)
				ray->tex_data = mlx_get_data_addr(cube->textures.north,
						&ray->bpp, &ray->sl, &ray->end);
			else
				ray->tex_data = mlx_get_data_addr(cube->textures.south,
						&ray->bpp, &ray->sl, &ray->end);
		}
		else
		{
			if (ray->ray_dir_y > 0)
				ray->tex_data = mlx_get_data_addr(cube->textures.east,
						&ray->bpp, &ray->sl, &ray->end);
			else
				ray->tex_data = mlx_get_data_addr(cube->textures.west,
						&ray->bpp, &ray->sl, &ray->end);
		}
	}
}

void	set_ray_dir(t_cube *cube, t_raycasting *ray)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (cube->rendering.pos_x - ray->map_x)
			* ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - cube->rendering.pos_x)
			* ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (cube->rendering.pos_y - ray->map_y)
			* ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - cube->rendering.pos_y)
			* ray->delta_dist_y;
	}
}

void	init_ray(t_cube *cube, t_raycasting *ray)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (cube->rendering.map[ray->map_x][ray->map_y] == 1)
			ray->hit = 1;
	}
}

void	raycasting(t_cube *cube, t_raycasting *ray)
{
	unsigned int	buffer[HEIGHT][WIDTH];

	ft_memset(buffer, 0, sizeof(buffer));
	ray->x = 0;
	while (ray->x < WIDTH)
	{
		set_values(cube, ray);
		set_ray_dir(cube, ray);
		init_ray(cube, ray);
		ray_calculator(cube, ray);
		texture_selector(cube, ray);
		buffer_fill(ray, buffer);
		ray->x++;
	}
	calculate_deltatime(cube);
	set_buffer(cube, buffer);
	mlx_put_image_to_window(cube->mlx, cube->mlx_win,
		cube->image->img, 0, 0);
}
