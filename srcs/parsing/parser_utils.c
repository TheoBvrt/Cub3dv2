/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 14:45:00 by theo              #+#    #+#             */
/*   Updated: 2026/04/17 14:45:00 by theo             ###   ########.fr       */
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
