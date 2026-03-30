#include "cube.h"

void	my_mlx_pixel_put(t_image *image, int x, int y, int color)
{
	char	*dst;

	dst = image->addr + (y * image->line_length + x * (image->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	draw_verline(int start_x, int start_y, int end_y, t_cube *cube, int color)
{
	int	current_x = start_x;
	int current_y = start_y;
	
	while (current_y < end_y)
	{
		my_mlx_pixel_put(cube->image, current_x, current_y, color);
		current_y ++;
	}
}