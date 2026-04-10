#include "cube.h"

int	exit_cub3d(t_cube *cube)
{
	mlx_destroy_image(cube->mlx, cube->image->img);
	mlx_destroy_window(cube->mlx, cube->mlx_win);
	mlx_destroy_display(cube->mlx);
	free(cube->mlx);
	free_tab(cube->parsed_file);
	free_game_map(cube);
	exit (0);
}

void	clean_mlx(t_cube *cube)
{
	mlx_destroy_display(cube->mlx);
	free(cube->mlx);
}