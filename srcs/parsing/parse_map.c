#include "cube.h"

static void	assign_string_pointers(char **parsed_map, t_cube *cube)
{

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
	if (!first_check_map(cube))
	{
		ft_printf("Error\n");
		return (0);
	}
	return (close(fd), 1);
}