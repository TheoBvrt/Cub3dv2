/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 14:45:00 by theo              #+#    #+#             */
/*   Updated: 2026/04/24 15:22:01 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static int	check_neighbor(int y, int x, t_cube *cube)
{
	if (y == 0 || y == cube->map_size - (cube->parser.map_index + 1)
		|| x == 0 || x == cube->map_length -1)
		return (0);
	if (cube->rendering.map[y - 1][x] == -1)
		return (0);
	if (cube->rendering.map[y + 1][x] == -1)
		return (0);
	if (cube->rendering.map[y][x - 1] == -1)
		return (0);
	if (cube->rendering.map[y][x + 1] == -1)
		return (0);
	return (1);
}

static int	check_start_position(t_cube *cube)
{
	int	counter;
	int	y;
	int	x;

	y = cube->parser.map_index;
	counter = 0;
	while (y < cube->map_size)
	{
		x = 0;
		while (x < cube->map_length)
		{
			if (is_start_position(cube, cube->parsed_file[y][x]))
				counter ++;
			x ++;
		}
		y ++;
	}
	if (counter != 1)
		return (0);
	return (1);
}

int	check_map_format(t_cube *cube)
{
	int	y;
	int	x;

	y = cube->parser.map_index;
	while (cube->parsed_file[y])
	{
		x = 0;
		if (cube->parsed_file[y][0] == '\n')
			return (ft_printf("Error\n -> Empty line in the map\n"), 0);
		while (cube->parsed_file[y][x])
		{
			if (!is_valid_map_char(cube->parsed_file[y][x]))
				return (ft_printf("Error\n -> Invalid character\n"), 0);
			x ++;
		}
		y ++;
	}
	if (!check_start_position(cube))
		return (ft_printf("Error\n -> Start position error\n"), 0);
	return (1);
}

int	check_game_map(t_cube *cube)
{
	int	y;
	int	x;

	y = 0;
	while (y < cube->map_size - cube->parser.map_index)
	{
		x = 0;
		while (x < cube->map_length)
		{
			if (cube->rendering.map[y][x] != -1
				&& cube->rendering.map[y][x] != 1)
			{
				if (!check_neighbor(y, x, cube))
					return (ft_printf("Error\n -> Map format error\n"), 0);
			}
			x ++;
		}
		y ++;
	}
	return (1);
}
