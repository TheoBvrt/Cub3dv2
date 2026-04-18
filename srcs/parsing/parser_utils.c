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

int	get_max_length(t_cube *cube)
{
	int	index;
	int	res;
	int	tmp;

	index = 8;
	res = 0;
	while (cube->parsed_file[index])
	{
		tmp = ft_strlen(cube->parsed_file[index]) - 1;
		if (tmp > res)
			res = tmp;
		index ++;
	}
	return (res);
}

int	get_file_size(char *map_path)
{
	char	*line;
	int		fd;
	int		size;

	size = 0;
	fd = open(map_path, O_RDONLY);
	if (fd == -1 || fd == 0)
		return (0);
	line = get_next_line(fd);
	while (line != NULL)
	{
		free (line);
		line = get_next_line(fd);
		size++;
	}
	free (line);
	close(fd);
	return (size);
}

int	alloc_map_table(t_cube *cube)
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

int	is_start_position(t_cube *cube, char c)
{
	if (c == 'N')
		return (cube->orientation = N, 1);
	if (c == 'S')
		return (cube->orientation = S, 1);
	if (c == 'W')
		return (cube->orientation = W, 1);
	if (c == 'E')
		return (cube->orientation = E, 1);;
	return (0);
}
