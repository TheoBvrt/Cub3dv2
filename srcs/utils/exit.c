/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 15:18:00 by theo              #+#    #+#             */
/*   Updated: 2026/04/18 14:05:12 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	exit_cub3d(t_cube *cube)
{
	free(cube->path_texture_north);
	free(cube->path_texture_south);
	free(cube->path_texture_west);
	free(cube->path_texture_east);
	mlx_destroy_image(cube->mlx, cube->image->img);
	mlx_destroy_image(cube->mlx, cube->textures.north);
	mlx_destroy_image(cube->mlx, cube->textures.south);
	mlx_destroy_image(cube->mlx, cube->textures.west);
	mlx_destroy_image(cube->mlx, cube->textures.east);
	mlx_destroy_window(cube->mlx, cube->mlx_win);
	mlx_destroy_display(cube->mlx);
	free(cube->mlx);
	free_tab(cube->parsed_file);
	free_game_map(cube);
	exit (0);
}

void	clean_mlx(t_cube *cube)
{
	mlx_destroy_display(cube->mlx);
	free(cube->mlx);
}
