/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 21:41:21 by theo              #+#    #+#             */
/*   Updated: 2026/04/07 18:32:44 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include <sys/time.h>
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

# ifndef SCREEN_SETTINGS
#  define WIDTH 1920
#  define HEIGHT 1080
# endif

# ifndef ORIENTATION
#  define N 0
#  define S 1
#  define W 2
#  define E 3
# endif

# ifndef GAME_SETTINGS
#  define MOVESPEED 5
#  define TURNSPEED 2
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
	int		**map;
	double	posX;
	double	posY;
	double	dirX;
	double	dirY;
	double	planeX;
	double	planeY;
	double	lastTime;
	double	deltaTime;
	char	*n_texture;
	char	*s_texture;
	char	*w_texture;
	char	*e_texture;
	char	*f_color;
	char	*c_color;
}	t_rendering;

typedef struct s_keydown
{
	int	key_w;
	int	key_s;
	int	key_a;
	int	key_d;
}	t_keydown;

typedef struct s_cube
{
	t_image		*image;
	t_rendering	rendering;
	t_keydown	keydown;
	int		orientation;
	int		map_size;
	int		map_length;
	void	*mlx;
	void	*mlx_win;
	char	**parsed_file;
}	t_cube;

void	render(t_cube *cube);
int		on_keydown(int keycode, t_cube *cube);
int		on_keyrelease(int keycode, t_cube *cube);
void	draw_verline(int start_x, int start_y, int end_y, t_cube *cube, int color);
void	my_mlx_pixel_put(t_image *image, int x, int y, int color);
void	forward(t_cube *cube);
void	backward(t_cube *cube);
void	turn_left(t_cube *cube);
void	turn_right(t_cube *cube);
int	update(t_cube *cube);
int	on_keyrelease(int keycode, t_cube *cube);
int	check_file_type(char *map_path);
int	parse_map(char *map_path, t_cube *cube);
int	get_file_size(char *map_path);
int	check_file(t_cube *cube);
int	check_game_map(t_cube *cube);
void	free_tab(char **tab);
void	free_game_map(t_cube *cube);
int	get_max_length(t_cube *cube);
void	set_start_position(int y, int x, t_cube *cube);
int	is_valid_map_char(char c);

int	check_map_format(t_cube *cube);
#endif
