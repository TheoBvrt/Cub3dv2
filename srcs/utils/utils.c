#include "cube.h"

void	free_tab(char **tab)
{
	int	index;

	index = 0;
	while (tab[index])
		free(tab[index ++]);
	free (tab);
}

void	free_game_map(t_cube *cube)
{
	int	index;

	index = 0;
	while (index < cube->map_size - 8)
		free(cube->rendering.map[index ++]);
	free(cube->rendering.map);
}

void	set_start_position(int y, int x, t_cube *cube)
{
	cube->rendering.posY = x + 0.5;
	cube->rendering.posX = y - 7;
	if (cube->parsed_file[y][x] == 'N')
		cube->orientation = N;
	if (cube->parsed_file[y][x] == 'S')
		cube->orientation = S;
	if (cube->parsed_file[y][x] == 'W')
		cube->orientation = W;
	if (cube->parsed_file[y][x] == 'E')
		cube->orientation = E;
}

int	is_valid_map_char(char c)
{
	if (c == '\n' || c == ' ' || c == '1' || c == '0' || c == 'N' || c == 'S'
		|| c == 'W' || c == 'E')
		return (1);
	return (0);
}

double	myabs(double x)
{
	if (x >= 0)
		return (x);
	else
		return (x * -1);
}