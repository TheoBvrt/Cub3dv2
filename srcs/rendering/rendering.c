#include "cube.h"

void	raycasting(t_cube *cube)
{	
	int	x = 0;
	while (x < WIDTH)
	{
		double cameraX = 2 * x / (double)WIDTH - 1;
		double rayDirX = cube->rendering.dirX + cube->rendering.planeX * cameraX;
		double rayDirY = cube->rendering.dirY + cube->rendering.planeY * cameraX;

		int	mapX = (int)cube->rendering.posX;
		int	mapY = (int)cube->rendering.posY;

		double sideDistX;
		double sideDistY;

		double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
		double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
		double perpWallDist;

		int stepX;
		int stepY;

		int hit = 0;
		int side;

		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (cube->rendering.posX - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - cube->rendering.posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (cube->rendering.posY - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - cube->rendering.posY) * deltaDistY;
		}

		while (hit == 0)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			if (cube->rendering.map[mapX][mapY] > 0) hit = 1;
		} 
		if(side == 0)
			perpWallDist = (sideDistX - deltaDistX);
		else
			perpWallDist = (sideDistY - deltaDistY);

		int lineHeight = (int)(HEIGHT / perpWallDist);

		int drawStart = -lineHeight / 2 + HEIGHT / 2;
		if(drawStart < 0)drawStart = 0;
		int drawEnd = lineHeight / 2 + HEIGHT / 2;
		if(drawEnd >= HEIGHT)drawEnd = HEIGHT - 1;

		if (cube->rendering.map[mapX][mapY] != -1)
		{
			int color;
			switch(cube->rendering.map[mapX][mapY])
			{
				case 1:  color = 0xFF0000; break; // rouge
				case 2:  color = 0x00FF00; break; // vert
				case 3:  color = 0x0000FF; break; // bleu
				case 4:  color = 0xFFFFFF; break; // blanc
				default: color = 0xFFFF00; break; // jaune
			}

			if (side == 1)
				{color = color / 2;}

			draw_verline(x, drawStart, drawEnd, cube, color);
		}
		x ++;
	}


	struct timeval tv;

	gettimeofday(&tv, NULL);

	double curtime = (double)tv.tv_sec + (double)tv.tv_usec / 1e6;
	cube->rendering.deltaTime = (curtime - cube->rendering.lastTime);
	cube->rendering.lastTime = curtime;
	printf("(%f)", cube->rendering.deltaTime);
}

void	draw_celling_and_ground(t_cube *cube)
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
				my_mlx_pixel_put(cube->image, x, y, 0x03f8fc);
			else
				my_mlx_pixel_put(cube->image, x, y, 0x67fc03);
	
			x ++;
		}
		y ++;
	}
}

void	clear_screen(t_cube *cube)
{
	mlx_destroy_image(cube->mlx, cube->image->img);
	cube->image->img = mlx_new_image(cube->mlx, WIDTH, HEIGHT);
	cube->image->addr = mlx_get_data_addr(cube->image->img,
		&cube->image->bits_per_pixel, &cube->image->line_length,
		&cube->image->endian);
}

//main loop
void	render(t_cube *cube)
{
	clear_screen(cube);
	draw_celling_and_ground(cube);
	raycasting(cube);

	mlx_put_image_to_window(cube->mlx, cube->mlx_win, cube->image->img, 0, 0);
}