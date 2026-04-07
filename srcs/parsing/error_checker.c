#include "cube.h"

static int	check_texture(char *str, char *prefix, t_cube *cube)
{
	void	*img;
	char	*path;
	int		img_width;
	int		img_height;

	if (ft_strlen(str) <= 4)
		return (0);
	if (ft_strncmp(str, prefix, 3) == 0)
	{
		path = ft_substr(str, 3, ft_strlen(str) - 4);
		if (!path)
			return (0);
		img = mlx_xpm_file_to_image(cube->mlx, path, &img_width, &img_height);
		if (!img)
			return (free (path), 0);
		mlx_destroy_image(cube->mlx, img);
		free (path);
	}
	return (1);
}

static int	check_color_format(char *str)
{
	int	comas_counter;
	int	index;

	index = 0;
	comas_counter;
	while (str[index])
	{
		if (str[index] == ',')
			comas_counter ++;
		if (!ft_isdigit(str[index]) && str[index] != ',')
			return (0);
		index ++;
	}
	if (comas_counter != 3)
		return (0);
	return (1);
}

static int	check_color(char *str, char *prefix, t_cube *cube)
{
	int		color[3];
	char	*tmp;
	char	**extracted_values;

	if (ft_strlen(str) <= 4)
		return (0);
	if (ft_strncmp(str, prefix, 3) == 0)
	{
		tmp = ft_substr(str, 3, ft_strlen(str) - 4);
		if (!tmp)
			return (0);
		if (!check_color_format(tmp))
			return(free(tmp), 0);
	}
	return (1);
}

int	check_map(t_cube *cube)
{
	if (cube->map_size <= 8)
		return (0);
	if (ft_strlen(cube->parsed_file[4]) != 1 && cube->parsed_file[4][0] != '\n')
		return (0);
	if (ft_strlen(cube->parsed_file[7]) != 1 && cube->parsed_file[7][0] != '\n')
		return (0);
	if (!check_texture(cube->parsed_file[0], "NO ", cube)
		|| !check_texture(cube->parsed_file[1], "SO ", cube)
		|| !check_texture(cube->parsed_file[2], "WE ", cube)
		|| !check_texture(cube->parsed_file[3], "EA ", cube))
		return (0);
	return (1);
}

int	check_file_type(char *map_path)
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
