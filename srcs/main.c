#include "cube.h"

double	myabs(double x)
{
	if (x >= 0)
		return (x);
	else
		return (x * -1);
}

int	init(t_cube *cube, t_image *image)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	cube->rendering.lastTime = (double)tv.tv_sec + (double)tv.tv_usec / 1e6;

	cube->rendering.posX = 12;
	cube->rendering.posY = 17;
	cube->rendering.dirX = -1;
	cube->rendering.dirY = 0;
	cube->rendering.planeX = 0;
	cube->rendering.planeY = 0.66;
	cube->keydown.key_a = 0;
	cube->keydown.key_s = 0;
	cube->keydown.key_d = 0;
	cube->keydown.key_w = 0;
	cube->mlx = mlx_init();
	cube->mlx_win = mlx_new_window(cube->mlx, WIDTH, HEIGHT, "Cub3d");
	image->img = mlx_new_image(cube->mlx, WIDTH, HEIGHT);
	image->addr = mlx_get_data_addr(image->img, &image->bits_per_pixel,
		&image->line_length, &image->endian);
	cube->image = image;

	render(cube);
	mlx_hook(cube->mlx_win, 2, (1L << 0), on_keydown, cube);
	mlx_hook(cube->mlx_win, 3, (1L << 1), on_keyrelease, cube);
	mlx_loop_hook(cube->mlx, update, cube);
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