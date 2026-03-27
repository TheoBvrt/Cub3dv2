/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbouver <thbouver@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 21:41:21 by theo              #+#    #+#             */
/*   Updated: 2025/11/07 16:26:45 by thbouver         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# include "../libft/libft.h"
# include "../mlx/mlx.h"

# include "math.h"
# include "stdio.h"

# ifndef KEYCODE
#  define ESCAPE 65307
#  define SCROLL_UP 4
#  define SCROLL_DOWN 5
#  define LEFT_CLICK 1
#  define RIGHT_CLICK 3
#  define LEFT_ARROW 65361
#  define RIGHT_ARROW 65363
#  define UP_ARROW 65362
#  define DOWN_ARROW 65364
#  define A_KEY 97
#  define D_KEY 100
#  define W_KEY 119
#  define S_KEY 115
#  define R_KEY 114
#  define MINUS_KEY 45
#  define PLUS_KEY 61
# endif

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_image;

typedef struct s_rendering
{
	double posX;
	double posY;
	double dirX;
	double dirY;
	double planeX;
	double planeY;
	double time;
	double oldTime;
}	t_rendering;

typedef struct s_cube
{
	t_image		*image;
	t_rendering	rendering;
	void	*mlx;
	void	*mlx_win;
}	t_cube;

#endif