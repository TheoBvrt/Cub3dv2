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

void	clean_all(t_cube *cube)
{
	int	index;

	index = 0;
	while (index < cube->map_size)
		free(cube->parsed_file[index ++]);
	free(cube->parsed_file);
	mlx_destroy_display(cube->mlx);
	free(cube->mlx);
}

void	clean_mlx(t_cube *cube)
{
	mlx_destroy_display(cube->mlx);
	free(cube->mlx);
}

int	main(int argc, char *argv[])
{
	t_cube	cube;
	t_image	image;

	if (argc != 2)
	{
		ft_printf("Error : ./cub3d <map.cub>");
		return (0);
	}
	if (!check_file_type(argv[1]))
		return (0);

	cube.mlx = mlx_init();
	if (!parse_map(argv[1], &cube))
	 	return (clean_mlx(&cube), 0);

	if (!init(&cube, &image))
		return (1);
	clean_all(&cube);
	return (1);
}
