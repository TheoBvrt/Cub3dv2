#include "cube.h"

static void	parse_game_map(t_cube *cube)
{
	int	g_x;
	int	g_y;
	int	f_x;
	int	f_y;

	g_y = 0;
	f_y = 8;
	while (cube->parsed_file[f_y])
	{
		f_x = 0;
		g_x = 0;
		while (cube->parsed_file[f_y][f_x])
		{
			if (cube->parsed_file[f_y][f_x] != '\n')
			{
				if (cube->parsed_file[f_y][f_x] == ' ')
					cube->rendering.map[g_y][g_x] = -1;
				else if (ft_isdigit(cube->parsed_file[f_y][f_x]))
					cube->rendering.map[g_y][g_x]
						= cube->parsed_file[f_y][f_x] - 48;
				else
				{
					set_start_position(f_y, f_x, cube);
					cube->rendering.map[g_y][g_x] = 0;
				}
			}
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
	int	x;

	index = 0;
	cube->rendering.map = ft_calloc(cube->map_size - 7, sizeof(int *));
	if (!cube->rendering.map)
		return (0);
	while (index < cube->map_size - 8)
	{
		x = 0;
		cube->rendering.map[index]
			= ft_calloc(cube->map_length + 1, sizeof(int));
		while (x < cube->map_length + 1)
		{
			cube->rendering.map[index][x] = -1;
			x ++;
		}
		index ++;
	}
	return (1);
}

static void	print_map(t_cube *cube)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (y < cube->map_size - 8)
	{
		x = 0;
		while (x < cube->map_length)
		{
			ft_printf("%d", cube->rendering.map[y][x]);
			if (cube->rendering.map[y][x] == -1)
				ft_printf(" ");
			else
				ft_printf("  ");
			x ++;
		}
		ft_printf("\n");
		y ++;
	}
}

int	parse_map(char *map_path, t_cube *cube)
{
	int		index;
	int		fd;

	index = 0;
	fd = open(map_path, O_RDONLY);
	if (fd == -1 || fd == 0)
		return (ft_printf("Error\n"), 0);
	cube->map_size = get_file_size(map_path);
	cube->parsed_file = ft_calloc(cube->map_size + 1, sizeof(char *));
	if (!cube->parsed_file)
		return (0);
	cube->parsed_file[index] = get_next_line(fd);
	while (cube->parsed_file[index])
		cube->parsed_file[++ index] = get_next_line(fd);
	if (!check_file(cube))
		return (free_tab(cube->parsed_file), ft_printf("Error\n"), 0);
	cube->map_length = get_max_length(cube);
	if (!alloc_map_table(cube))
		return (free_tab(cube->parsed_file), ft_printf("Error\n"), 0);
	if (!check_map_format(cube))
		return (free_tab(cube->parsed_file), ft_printf("Error\n"), 0);
	parse_game_map(cube);
	if (!check_game_map(cube))
		return (free_tab(cube->parsed_file),
			free_game_map(cube), ft_printf("Error\n"), 0);
	return (close(fd), 1);
}
