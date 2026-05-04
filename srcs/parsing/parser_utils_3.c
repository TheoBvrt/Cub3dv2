/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 14:45:00 by theo              #+#    #+#             */
/*   Updated: 2026/05/04 12:17:16 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	parse_game_map_extend(t_cube *cube)
{
	if (cube->parsed_file[cube->parser.f_y][cube->parser.f_x] != '\n')
	{
		if (cube->parsed_file[cube->parser.f_y][cube->parser.f_x] == ' ')
			cube->rendering.map[cube->parser.g_y][cube->parser.g_x] = -1;
		else if (ft_isdigit(cube->parsed_file[cube->parser.f_y]
				[cube->parser.f_x]))
			cube->rendering.map[cube->parser.g_y][cube->parser.g_x]
				= cube->parsed_file[cube->parser.f_y][cube->parser.f_x] - 48;
		else
		{
			set_start_position(cube->parser.f_y, cube->parser.f_x, cube);
			cube->rendering.map[cube->parser.g_y][cube->parser.g_x] = 0;
		}
	}
}

int	check_doublon(t_cube *cube)
{
	int	index;

	index = 0;
	while (cube->parsed_file[index])
	{
		if ((check_identifier(cube->parsed_file[index], "NO") == 1
				&& index != cube->parser.no_tex_index)
			|| (check_identifier(cube->parsed_file[index], "SO") == 1
				&& index != cube->parser.so_tex_index)
			|| (check_identifier(cube->parsed_file[index], "WE") == 1
				&& index != cube->parser.we_tex_index)
			|| (check_identifier(cube->parsed_file[index], "EA") == 1
				&& index != cube->parser.ea_tex_index)
			|| (check_identifier(cube->parsed_file[index], "F") == 1
				&& index != cube->parser.f_index)
			|| (check_identifier(cube->parsed_file[index], "C") == 1
				&& index != cube->parser.c_index))
			return (0);
		index ++;
	}
	return (1);
}

int	check_texture_file_type(char *texture)
{
	int	index;

	index = ft_strlen(texture) - 1;
	if (texture[index] != 'm'
		&& texture[index - 1] != 'p'
		&& texture[index - 2] != 'x'
		&& texture[index - 3] != '.'
	)
		return (0);
	return (1);
}
