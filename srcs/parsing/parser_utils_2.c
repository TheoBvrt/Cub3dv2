/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 14:45:00 by theo              #+#    #+#             */
/*   Updated: 2026/04/18 14:26:36 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	is_map_line(char *str)
{
	if (ft_strncmp(str, "NO ", 3) == 0
		|| ft_strncmp(str, "SO ", 3) == 0
		|| ft_strncmp(str, "WE ", 3) == 0
		|| ft_strncmp(str, "EA ", 3) == 0
		|| ft_strncmp(str, "F ", 2) == 0
		|| ft_strncmp(str, "C ", 2) == 0
		|| str[0] == '\n')
		return (0);
	return (1);
}

int	get_index_of_map(t_cube *cube)
{
	int	index;

	index = 0;
	while (cube->parsed_file[index])
	{
		if (is_map_line(cube->parsed_file[index]))
			return (index);
		index ++;
	}
	ft_printf("Error\n -> Map error\n");
	return (-1);
}

int	get_index_of_element(char *prefix_to_find, t_cube *cube)
{
	int	index;

	index = 0;
	while (index < cube->parser.map_index)
	{
		if (ft_strncmp(cube->parsed_file[index],
				prefix_to_find, ft_strlen(prefix_to_find)) == 0)
			return (index);
		index ++;
	}
	return (-1);
}

// void	set_map_int(t_cube *cube, int f_y, int f_x, int g_y, int g_x)
// {
// 	if (cube->parsed_file[f_y][f_x] != '\n')
// 	{
// 		if (cube->parsed_file[f_y][f_x] == ' ')
// 			cube->rendering.map[g_y][g_x] = -1;
// 		else if (ft_isdigit(cube->parsed_file[f_y][f_x]))
// 			cube->rendering.map[g_y][g_x]
// 				= cube->parsed_file[f_y][f_x] - 48;
// 		else
// 		{
// 			set_start_position(f_y, f_x, cube);
// 			cube->rendering.map[g_y][g_x] = 0;
// 		}
// 	}
// }