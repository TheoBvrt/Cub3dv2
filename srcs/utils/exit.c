/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiribar <xiribar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/17 15:18:00 by theo              #+#    #+#             */
/*   Updated: 2026/04/17 15:18:00 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cube.h"

int	exit_cub3d(t_cube *cube)
{
	mlx_destroy_image(cube->mlx, cube->image->img);
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
