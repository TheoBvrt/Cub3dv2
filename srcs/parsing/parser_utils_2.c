/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 14:45:00 by theo              #+#    #+#             */
/*   Updated: 2026/04/24 16:23:53 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	check_identifier(char *str, char *identifier)
{
	int	index;

	index = 0;
	while (str[index] && str[index] != '\n' && str[index] != identifier[0])
	{
		if (!is_wspace(str[index]))
			return (-1);
		index ++;
	}
	if (ft_strncmp(str + index, identifier, ft_strlen(identifier)) == 0)
		return (1);
	return (0);
}

int	is_map_line(char *str)
{
	if (check_identifier(str, "NO") == 1
		|| check_identifier(str, "SO") == 1
		|| check_identifier(str, "WE") == 1
		|| check_identifier(str, "EA") == 1
		|| check_identifier(str, "F") == 1
		|| check_identifier(str, "C") == 1
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
		if (check_identifier(cube->parsed_file[index],
				prefix_to_find) == 1)
			return (index);
		index ++;
	}
	return (-1);
}

char	*get_after_id(char *str, char *id)
{
	char	*res;
	int		index;
	int		max;

	index = 0;
	max = ft_strlen(str) - 2;
	while (max != 0 && is_wspace(str[max]))
		max --;
	while (str[index] && str[index] != '\n' && str[index] != id[0])
		index ++;
	index += ft_strlen(id);
	while (is_wspace(str[index]))
		index ++;
	res = ft_substr(str, index, max - index + 1);
	return (res);
}
