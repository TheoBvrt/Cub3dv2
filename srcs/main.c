#include "cube.h"

void	my_mlx_pixel_put(t_image *image, int x, int y, int color)
{
	char	*dst;

	dst = image->addr + (y * image->line_length + x * (image->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}


double	myabs(double x)
{
	if (x >= 0)
		return (x);
	else
		return (x * -1);
}

void	draw_verline(int start_x, int start_y, int end_y, t_cube *cube, int color)
{
	int	current_x = start_x;
	int current_y = start_y;
	
	while (current_y < end_y)
	{
		my_mlx_pixel_put(cube->image, current_x, current_y, color);
		current_y ++;
	}
}

int	on_keydown(int keycode, t_cube *cube)
{
	return (1);
}

void	render(t_cube *cube)
{
	int worlMap[24][24]=
	{
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
		{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
		{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};
	
	cube->rendering.posX = 12;
	cube->rendering.posY = 17;
	cube->rendering.dirX = -1;
	cube->rendering.dirY = 0;
	cube->rendering.planeX = 0;
	cube->rendering.planeY = 0.66;

	int	x = 0;
	while (x < 1920)
	{
		double cameraX = 2 * x / (double)1920 - 1;
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
			if (worlMap[mapX][mapY] > 0) hit = 1;
		} 
		if(side == 0)
			perpWallDist = (sideDistX - deltaDistX);
		else
			perpWallDist = (sideDistY - deltaDistY);

		int lineHeight = (int)(1080 / perpWallDist);

		int drawStart = -lineHeight / 2 + 1080 / 2;
		if(drawStart < 0)drawStart = 0;
		int drawEnd = lineHeight / 2 + 1080 / 2;
		if(drawEnd >= 1080)drawEnd = 1080 - 1;

		int color;
		switch(worlMap[mapX][mapY])
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
		x ++;
	}
}

int	init(t_cube *cube, t_image *image)
{
	cube->mlx = mlx_init();
	cube->mlx_win = mlx_new_window(cube->mlx, 1920, 1080, "Cub3d");
	image->img = mlx_new_image(cube->mlx, 1920, 1080);
	image->addr = mlx_get_data_addr(image->img, &image->bits_per_pixel,
		&image->line_length, &image->endian);
	cube->image = image;

	render(cube);
	mlx_put_image_to_window(cube->mlx, cube->mlx_win, cube->image->img, 0, 0);

	mlx_loop(cube->mlx);
}

int	main(int argc, char *argv[])
{
	t_cube	cube;
	t_image	image;

	if (!init(&cube, &image))
		return (1);
	return (1);
}