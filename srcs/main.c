#include "cube.h"

void	my_mlx_pixel_put(t_image *image, int x, int y, int color)
{
	char	*dst;

	dst = image->addr + (y * image->line_length + x * (image->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	init(t_cube *cube, t_image *image)
{
	cube->mlx = mlx_init();
	cube->mlx_win = mlx_new_window(cube->mlx, 1920, 1080, "Cub3d");
	image->img = mlx_new_image(cube->mlx, 1920, 1080);
	image->addr = mlx_get_data_addr(image->img, &image->bits_per_pixel,
		&image->line_length, &image->endian);
	cube->image = image;

	my_mlx_pixel_put(cube->image, 5, 5, 0x00FF0000);
	mlx_put_image_to_window(cube->mlx, cube->mlx_win, cube->image->img, 0, 0);

	mlx_loop(cube->mlx);
}

void	render(t_cube *cube)
{
	int worlMap[10][10] =
	{
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
	};
	
	cube->rendering.posX = 22;
	cube->rendering.posY = 12;
	cube->rendering.dirX = -1;
	cube->rendering.dirY = 0;
	cube->rendering.planeX = 0;
	cube->rendering.planeY = 0.66;
	cube->rendering.time = 0;
	cube->rendering.oldTime = 0;
	
	int	x = 0;
	while (x < 1920)
	{
		double cameraX = 2 * 1080 / (double)1920 - 1;
		double rayDirX = cube->rendering.dirX + cube->rendering.planeX * cameraX;
		double rayDirY = cube->rendering.dirY + cube->rendering.planeY * cameraX;

		int	mapX = (int)cube->rendering.posX;
		int	mapY = (int)cube->rendering.posY;

		double sideDistX;
		double sideDistY;

		
		x ++;
	}
}

int	main(int argc, char *argv[])
{
	t_cube	cube;
	t_image	image;

	if (!init(&cube, &image))
		return (1);
	return (1);
}