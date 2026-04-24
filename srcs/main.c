/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 15:25:00 by theo              #+#    #+#             */
/*   Updated: 2026/04/24 16:28:29 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	main(int argc, char *argv[])
{
	t_cube	cube;
	t_image	image;

	if (argc != 2)
	{
		ft_printf("Error : ./cub3d <map.cub>");
		return (1);
	}
	if (!check_file_type(argv[1]))
		return (1);
	cube.mlx = mlx_init();
	if (!parse_map(argv[1], &cube))
		return (clean_mlx(&cube), 1);
	if (!init(&cube, &image))
		return (1);
	exit(0);
}
