#include "cube.h"

static int	check_neighbor(int y, int x, t_cube *cube)
{
	if (y == 0 || y == cube->map_size - 9 || x == 0 || x == cube->map_length -1)
		return (0);
	if (cube->rendering.map[y - 1][x] == -1)
		return (0);
	if (cube->rendering.map[y + 1][x] == -1)
		return (0);
	if (cube->rendering.map[y][x - 1] == -1)
		return (0);
	if (cube->rendering.map[y][x + 1] == -1)
		return (0);
	return (1);
}

int	check_game_map(t_cube *cube)
{
	int	y;
	int	x;

	y = 0;
	while (y < cube->map_size - 8)
	{
		x = 0;
		while (x < cube->map_length)
		{
			if (cube->rendering.map[y][x] != -1
				&& cube->rendering.map[y][x] != 1)
			{
				if (!check_neighbor(y, x, cube))
					return (0);
			}
			x ++;
		}
		y ++;
	}
	return (1);
}