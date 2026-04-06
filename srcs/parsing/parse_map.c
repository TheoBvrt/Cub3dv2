#include "cube.h"

int	parse_map(char *map_path, t_cube *cube)
{
	int		index;
	int		fd;

	index = 0;
	fd = open(map_path, O_RDONLY);
	if (fd == -1 || fd == 0)
	{
		ft_printf("Error\nMap error");
		return (0);
	}
	cube->map_size = get_file_size(map_path);
	cube->parsed_file = ft_calloc(cube->map_size + 1, sizeof(char *));
	if (!cube->parsed_file)
		return (0);
	cube->parsed_file[index] = get_next_line(fd);
	while (cube->parsed_file[index])
	{
		index ++;
		cube->parsed_file[index] = get_next_line(fd);
		ft_printf("%s", cube->parsed_file[index]);
	}
	close(fd);
	return (1);
}