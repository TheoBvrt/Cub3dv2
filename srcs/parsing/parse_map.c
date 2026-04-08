#include "cube.h"

static int	parse_game_map(t_cube *cube)
{
	int	g_x;
	int	g_y;
	int	f_x;
	int	f_y;

	g_x = 0;
	g_y = 0;
	f_y = 8;
	while (cube->parsed_file[f_y])
	{
		f_x = 0;
		g_x = 0;
		while (cube->parsed_file[f_y][f_x])
		{
			f_x ++;
			g_x ++;
		}
		g_y ++;
		f_y ++;
	}

}

static int	alloc_map_table(t_cube *cube)
{
	int	index;

	index = 0;
	cube->rendering.map = ft_calloc(cube->map_size - 7, sizeof(int *));
	if (!cube->rendering.map)
		return (0);
	while (index < cube->map_size - 7)
	{
		cube->parsed_file[index] = ft_calloc(cube->max_length + 1, sizeof(int));
		index ++;
	}
	return (1);
}

int	parse_map(char *map_path, t_cube *cube)
{
	int		index;
	int		fd;

	index = 0;
	fd = open(map_path, O_RDONLY);
	if (fd == -1 || fd == 0)
		return (ft_printf("Error\nMap error"), 0);
	cube->map_size = get_file_size(map_path);
	cube->parsed_file = ft_calloc(cube->map_size + 1, sizeof(char *));
	if (!cube->parsed_file)
		return (0);
	cube->parsed_file[index] = get_next_line(fd);

	while (cube->parsed_file[index])
		cube->parsed_file[++ index] = get_next_line(fd);

	if (!check_map(cube))
		return (ft_printf("Error\n"), 0);


	// if (!alloc_map_table(cube))
	// 	return (0);



	return (close(fd), 1);
}
