/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_checker.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 14:45:00 by theo              #+#    #+#             */
/*   Updated: 2026/05/04 12:16:01 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static int	check_tex(char *str, char *prefix, t_cube *cube)
{
	void	*img;
	char	*path;
	int		img_width;
	int		img_height;

	if (ft_strlen(str) <= 4)
		return (0);
	if (!check_identifier(str, prefix))
		return (ft_printf("Error\n -> Texture error\n"), 0);
	path = get_after_id(str, prefix);
	if (!path)
		return (0);
	if (!check_texture_file_type(path))
	{
		free (path);
		return (0);
	}
	img = mlx_xpm_file_to_image(cube->mlx, path, &img_width, &img_height);
	if (!img)
		return (free(path), 0);
	mlx_destroy_image(cube->mlx, img);
	free(path);
	return (1);
}

static int	check_color_format(char *str)
{
	int	comas_counter;
	int	index;

	index = 0;
	comas_counter = 0;
	while (str[index])
	{
		if (str[index] == ',')
			comas_counter++;
		if (!ft_isdigit(str[index])
			&& str[index] != ',' && !is_wspace(str[index]))
			return (0);
		index++;
	}
	if (comas_counter != 2)
		return (0);
	return (1);
}

static int	check_color(char *str, char *prefix, t_cube *cube)
{
	char	*tmp;
	char	**values;

	(void)cube;
	if (ft_strlen(str) <= 3)
		return (0);
	if (!check_identifier(str, prefix))
		return (ft_printf("Error\n -> Color error\n"), 0);
	tmp = get_after_id(str, prefix);
	if (!tmp)
		return (0);
	if (!check_color_format(tmp))
		return (free(tmp), 0);
	values = ft_split(tmp, ',');
	if (!values)
		return (free(tmp), 0);
	if (!values[0] || !values[1] || !values[2])
		return (free(tmp), free_tab(values), 0);
	if (ft_atoi(values[0]) > 255 || ft_atoi(values[1]) > 255
		|| ft_atoi(values[2]) > 255)
		return (free(tmp), free_tab(values), 0);
	free(tmp);
	free_tab(values);
	return (1);
}

int	check_file(t_cube *cube)
{
	cube->parser.no_tex_index = get_index_of_element("NO", cube);
	cube->parser.so_tex_index = get_index_of_element("SO", cube);
	cube->parser.we_tex_index = get_index_of_element("WE", cube);
	cube->parser.ea_tex_index = get_index_of_element("EA", cube);
	cube->parser.f_index = get_index_of_element("F", cube);
	cube->parser.c_index = get_index_of_element("C", cube);
	if (cube->parser.no_tex_index == -1 || cube->parser.so_tex_index == -1
		|| cube->parser.we_tex_index == -1 || cube->parser.ea_tex_index == -1
		|| cube->parser.f_index == -1 || cube->parser.c_index == -1)
		return (ft_printf("Error\n -> Map format error\n"), 0);
	if (!check_doublon(cube))
		return (ft_printf("Error\n -> Map format error\n"), 0);
	if (!check_tex(cube->parsed_file[cube->parser.no_tex_index], "NO", cube)
		|| !check_tex(cube->parsed_file[cube->parser.so_tex_index], "SO", cube)
		|| !check_tex(cube->parsed_file[cube->parser.we_tex_index], "WE", cube)
		|| !check_tex(cube->parsed_file[cube->parser.ea_tex_index], "EA", cube)
	)
		return (ft_printf("Error\n -> Texture format error\n"), 0);
	if (!check_color(cube->parsed_file[cube->parser.f_index], "F ", cube))
		return (ft_printf("Error\n -> Color format error\n"), 0);
	if (!check_color(cube->parsed_file[cube->parser.c_index], "C ", cube))
		return (ft_printf("Error\n -> Color format error\n"), 0);
	return (1);
}

int	check_file_type(char *map_path)
{
	int	i;

	i = ft_strlen(map_path);
	if (i <= 4)
	{
		ft_printf("Error\n -> Map format error\n");
		return (0);
	}
	if (!(map_path[i - 1] == 'b'
			&& map_path[i - 2] == 'u'
			&& map_path[i - 3] == 'c'
			&& map_path[i - 4] == '.'))
	{
		ft_printf("Error\n -> Map format error\n");
		return (0);
	}
	return (1);
}
