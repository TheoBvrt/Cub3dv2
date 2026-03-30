#include "cube.h"

void	forward(t_cube *cube)
{
	cube->rendering.posX += cube->rendering.dirX * (MOVESPEED * cube->rendering.deltaTime);
	cube->rendering.posY += cube->rendering.dirY * (MOVESPEED * cube->rendering.deltaTime);
}

void	backward(t_cube *cube)
{
	cube->rendering.posX -= cube->rendering.dirX * (MOVESPEED * cube->rendering.deltaTime);
	cube->rendering.posY -= cube->rendering.dirY *( MOVESPEED * cube->rendering.deltaTime);
}

void	turn_left(t_cube *cube)
{
	double oldDirX;
	double	oldPlaneX;
	double	rot;

	rot = TURNSPEED * cube->rendering.deltaTime;

	oldDirX = cube->rendering.dirX;
	cube->rendering.dirX = cube->rendering.dirX * cos(rot) - cube->rendering.dirY * sin (rot);
	cube->rendering.dirY = oldDirX * sin(rot) + cube->rendering.dirY * cos (rot);
	oldPlaneX = cube->rendering.planeX;
	cube->rendering.planeX = cube->rendering.planeX * cos (rot) - cube->rendering.planeY * sin (rot);
	cube->rendering.planeY = oldPlaneX * sin (rot) + cube->rendering.planeY * cos (rot);
}

void	turn_right(t_cube *cube)
{
	double	oldDirX;
	double	oldPlaneX;
	double	rot;

	rot = -TURNSPEED * cube->rendering.deltaTime;

	oldDirX = cube->rendering.dirX;
	cube->rendering.dirX = cube->rendering.dirX * cos(rot) - cube->rendering.dirY * sin(rot);
	cube->rendering.dirY = oldDirX * sin(rot) + cube->rendering.dirY * cos(rot);

	oldPlaneX = cube->rendering.planeX;
	cube->rendering.planeX = cube->rendering.planeX * cos(rot) - cube->rendering.planeY * sin(rot);
	cube->rendering.planeY = oldPlaneX * sin(rot) + cube->rendering.planeY * cos(rot);
}