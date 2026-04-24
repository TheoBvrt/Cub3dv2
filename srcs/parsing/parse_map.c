/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 14:45:00 by theo              #+#    #+#             */
/*   Updated: 2026/04/24 16:39:28 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static int	get_map_color(t_cube *cube, int line, int *dest)
{
	char	*tmp;
	char	**rgb;

	if (line == cube->parser.f_index)
		tmp = get_after_id(cube->parsed_file[line], "F");
	else
		tmp = get_after_id(cube->parsed_file[line], "C");
	if (!tmp)
		return (0);
	rgb = ft_split(tmp, ',');
	if (!rgb)
		return (0);
	free (tmp);
	*dest = (ft_atoi(rgb[0]) << 16) | (atoi(rgb[1]) << 8) | atoi(rgb[2]);
	free_tab(rgb);
	return (1);
}

static int	get_textures(t_cube *cube)
{
	cube->path_texture_north
		= get_after_id(cube->parsed_file[cube->parser.no_tex_index], "NO");
	if (!cube->path_texture_north)
		return (0);
	cube->path_texture_south
		= get_after_id(cube->parsed_file[cube->parser.so_tex_index], "SO");
	if (!cube->path_texture_south)
		return (0);
	cube->path_texture_west
		= get_after_id(cube->parsed_file[cube->parser.we_tex_index], "WE");
	if (!cube->path_texture_west)
		return (0);
	cube->path_texture_east
		= get_after_id(cube->parsed_file[cube->parser.ea_tex_index], "EA");
	if (!cube->path_texture_east)
		return (0);
	return (1);
}

static void	parse_game_map(t_cube *cube)
{
	cube->parser.g_y = 0;
	cube->parser.f_y = cube->parser.map_index;
	while (cube->parsed_file[cube->parser.f_y])
	{
		cube->parser.f_x = 0;
		cube->parser.g_x = 0;
		while (cube->parsed_file[cube->parser.f_y][cube->parser.f_x])
		{
			parse_game_map_extend(cube);
			cube->parser.f_x ++;
			cube->parser.g_x ++;
		}
		cube->parser.g_y ++;
		cube->parser.f_y ++;
	}
}

int	get_file_lines(char *map_path, t_cube *cube)
{
	int	index;
	int	fd;

	index = 0;
	fd = open(map_path, O_RDONLY);
	if (fd == -1 || fd == 0)
		return (ft_printf("Error\n"), 0);
	cube->map_size = get_file_size(map_path);
	cube->parsed_file = ft_calloc(cube->map_size + 1, sizeof(char *));
	if (!cube->parsed_file)
		return (close(fd));
	if (!cube->parsed_file)
		return (0);
	cube->parsed_file[index] = get_next_line(fd);
	while (cube->parsed_file[index])
		cube->parsed_file[++index] = get_next_line(fd);
	close(fd);
	return (1);
}

int	parse_map(char *map_path, t_cube *cube)
{
	if (!get_file_lines(map_path, cube))
		return (0);
	cube->parser.map_index = get_index_of_map(cube);
	if (cube->parser.map_index == -1)
		return (free_tab(cube->parsed_file), 0);
	if (!check_file(cube))
		return (free_tab(cube->parsed_file), 0);
	cube->map_length = get_max_length(cube);
	if (!check_map_format(cube))
		return (free_tab(cube->parsed_file), 0);
	if (!alloc_map_table(cube))
		return (free_tab(cube->parsed_file), 0);
	parse_game_map(cube);
	get_map_color(cube, cube->parser.f_index, &cube->rendering.f_color);
	get_map_color(cube, cube->parser.c_index, &cube->rendering.c_color);
	if (!check_game_map(cube) || !get_textures(cube))
		return (free_tab(cube->parsed_file),
			free_game_map(cube), 0);
	return (1);
}
