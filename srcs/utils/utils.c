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