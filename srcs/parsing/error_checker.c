#include "cube.h"

static int	check_texture(char *prefix, char *str, int length, t_cube *cube)
{
	void	*img;
	char	**tab;
	int		img_width;
	int		img_height;

	if (ft_strncmp(str, prefix, length) == 0)
	{
		tab = ft_split(str, ' ');
	}
	return (0);
}

int	first_check_map(t_cube *cube)
{
	if(ft_strncmp(cube->parsed_file[0], "NO ./", 5) != 0
		|| ft_strncmp(cube->parsed_file[1], "SO ./", 5) != 0
		|| ft_strncmp(cube->parsed_file[2], "WE ./", 5) != 0
		|| ft_strncmp(cube->parsed_file[3], "EA ./", 5) != 0
		|| ft_strncmp(cube->parsed_file[5], "F ", 2) != 0
		|| ft_strncmp(cube->parsed_file[6], "C ", 2) != 0
		|| cube->parsed_file[4][0] != '\n'
		|| cube->parsed_file[7][0] != '\n'
	)
		return (0);
	return (1);
}

int	check_map_file(char *map_path)
{
	int	i;

	i = ft_strlen(map_path);
	if (i <= 4)
	{
		ft_printf("Map format error !\n");
		return (0);
	}
	if (!(map_path[i - 1] == 'b'
		&& map_path[i - 2] == 'u'
		&& map_path[i - 3] == 'c'
		&& map_path[i - 4] == '.'))
	{
		ft_printf("Map format error !\n");
		return (0);
	}
	return (1);
}