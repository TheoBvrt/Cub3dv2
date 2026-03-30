#include "cube.h"

int	update(t_cube *cube)
{
	if (cube->keydown.key_w == 1)
		forward(cube);
	if (cube->keydown.key_s == 1)
		backward(cube);
	if (cube->keydown.key_a == 1)
		turn_left(cube);
	if (cube->keydown.key_d == 1)
		turn_right(cube);
	render(cube);
}

int	on_keydown(int keycode, t_cube *cube)
{
	if (keycode == W_KEY)
		cube->keydown.key_w = 1;
	if (keycode == S_KEY)
		cube->keydown.key_s = 1;
	if (keycode == A_KEY)
		cube->keydown.key_a = 1;
	if (keycode == D_KEY)
		cube->keydown.key_d = 1;
	return (1);
}

int	on_keyrelease(int keycode, t_cube *cube)
{
	if (keycode == W_KEY)
		cube->keydown.key_w = 0;
	if (keycode == S_KEY)
		cube->keydown.key_s = 0;
	if (keycode == A_KEY)
		cube->keydown.key_a = 0;
	if (keycode == D_KEY)
		cube->keydown.key_d = 0;
	return (1);
}