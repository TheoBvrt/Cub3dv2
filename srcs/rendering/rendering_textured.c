#include "cube.h"

void	calculate_deltatime(t_cube *cube)
{
	struct timeval	tv;
	double			curtime;

	gettimeofday(&tv, NULL);
	curtime = (double)tv.tv_sec + (double)tv.tv_usec / 1e6;
	cube->rendering.deltaTime = (curtime - cube->rendering.lastTime);
	cube->rendering.lastTime = curtime;
}

void	clear_screen(t_cube *cube)
{
	mlx_destroy_image(cube->mlx, cube->image->img);
	cube->image->img = mlx_new_image(cube->mlx, WIDTH, HEIGHT);
	cube->image->addr = mlx_get_data_addr(cube->image->img,
		&cube->image->bits_per_pixel, &cube->image->line_length,
		&cube->image->endian);
}

void	image_loader(t_cube *cube)
{
	cube->textures.north = mlx_xpm_file_to_image(cube->mlx,
			"textures/basalt.xpm", &cube->textures.pw, &cube->textures.ph);
	cube->textures.south = mlx_xpm_file_to_image(cube->mlx,
			"textures/basalt.xpm",&cube->textures.pw, &cube->textures.ph);
	cube->textures.east = mlx_xpm_file_to_image(cube->mlx,
			"textures/basalt.xpm", &cube->textures.pw, &cube->textures.ph);
	cube->textures.west = mlx_xpm_file_to_image(cube->mlx,
			"textures/basalt.xpm", &cube->textures.pw, &cube->textures.ph);
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
			x ++;
		}
		y ++;
	}
}

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
		y ++;
	}
}

void	set_values(t_cube *cube, t_raycasting *ray)
{
	ray->hit = 0;
	ray->camera_x = 2 * ray->x / (double)WIDTH - 1;
	ray->ray_dir_x = cube->rendering.dirX + cube->rendering.planeX * ray->camera_x;
	ray->ray_dir_y = cube->rendering.dirY + cube->rendering.planeY * ray->camera_x;
	ray->map_x = (int)cube->rendering.posX;
	ray->map_y = (int)cube->rendering.posY;
	if (ray->ray_dir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->ray_dir_x);
	if (ray->ray_dir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->ray_dir_y);
}

void	ray_calculator(t_cube *cube, t_raycasting *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->side_dist_x - ray->delta_dist_x);
	else
		ray->perp_wall_dist = (ray->side_dist_y - ray->delta_dist_y);
	ray->line_height = (int)(HEIGHT / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + HEIGHT / 2;
	if (ray->draw_end >= HEIGHT)
		ray->draw_end = HEIGHT - 1;
	if (ray->side == 0)
		ray->wall_x = cube->rendering.posY + ray->perp_wall_dist * ray->ray_dir_y;
	else
		ray->wall_x = cube->rendering.posX
			+ ray->perp_wall_dist * ray->ray_dir_x ;
	ray->wall_x -= floor((ray->wall_x));
	ray->tex_x = (int)(ray->wall_x * (double)64);
	if (ray->side == 0 && ray->ray_dir_x > 0)
		ray->tex_x = 64 - ray->tex_x - 1;
	ray->step = 1.0 * 64 / ray->line_height;
	ray->text_pos = (ray->draw_start - HEIGHT / 2 + ray->line_height / 2)
		* ray->step;
}

void	texture_selector(t_cube *cube, t_raycasting *ray)
{
	if (cube->rendering.map[ray->map_x][ray->map_y] == 1)
	{
		if (ray->side == 0)
		{
			if (ray->ray_dir_x > 0)
				ray->tex_data = mlx_get_data_addr
					(cube->textures.north, &ray->bpp, &ray->sl, &ray->end);
			else
				ray->tex_data = mlx_get_data_addr
					(cube->textures.south, &ray->bpp, &ray->sl, &ray->end);
		}
		else
		{
			if (ray->ray_dir_y > 0)
				ray->tex_data = mlx_get_data_addr
					(cube->textures.east, &ray->bpp, &ray->sl, &ray->end);
			else
				ray->tex_data = mlx_get_data_addr
					(cube->textures.west, &ray->bpp, &ray->sl, &ray->end);
		}
	}
}

void	set_ray_dir(t_cube *cube, t_raycasting *ray)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (cube->rendering.posX - ray->map_x)
			* ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - cube->rendering.posX)
			* ray->delta_dist_x;
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (cube->rendering.posY - ray->map_y)
			* ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - cube->rendering.posY)
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
			ray->map_x += ray->step_x ;
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
	mlx_put_image_to_window(cube->mlx, cube->mlx_win, cube->image->img, 0, 0);
}
