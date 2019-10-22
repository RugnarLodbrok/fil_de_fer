#include "mlx.h"
#include "fdf.h"

int t_controller_key_press(int keycode, void *p)
{
	t_controller *c;

	c = p;
	if (keycode == KEY_W)
		c->v.z = -1;
	else if (keycode == KEY_S)
		c->v.z = 1;
	else if (keycode == KEY_A)
		c->v.x = -1;
	else if (keycode == KEY_D)
		c->v.x = 1;
	else if (keycode == KEY_Q)
		c->d_roll = 1;
	else if (keycode == KEY_E)
		c->d_roll = -1;
	else if (keycode == KEY_LEFT)
		c->d_yaw = -1;
	else if (keycode == KEY_RIGHT)
		c->d_yaw = 1;
	else if (keycode == KEY_UP)
		c->d_pitch = -1;
	else if (keycode == KEY_DOWN)
		c->d_pitch = 1;
	return 0;
}

int t_controller_key_release(int keycode, void *p)
{
	t_controller *c;

	c = p;
	if (keycode == KEY_W || keycode == KEY_S)
		c->v.z = 0;
	else if (keycode == KEY_A || keycode == KEY_D)
		c->v.x = 0;
	else if (keycode == KEY_Q || keycode == KEY_E)
		c->d_roll = 0;
	else if (keycode == KEY_LEFT || keycode == KEY_RIGHT)
		c->d_yaw = 0;
	else if (keycode == KEY_UP || keycode == KEY_DOWN)
		c->d_pitch = 0;
	return 0;
}

void mlx_bind_keys(void *win, t_controller *c)
{
	mlx_hook(win, MLX_EVEN_KEY_PRESS, 0, t_controller_key_press, c);
//	mlx_hook(win, MLX_EVEN_KEY_RELEASE, 0, t_controller_key_release, c);
}
