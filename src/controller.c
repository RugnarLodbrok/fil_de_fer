#include "mlx.h"
#include "fdf.h"

void t_controller_update_state(t_controller *c)
{
	c->v.z = -10 * (c->keyboard[KEY_W] - c->keyboard[KEY_S]);
	c->d_tilt = 1 * (c->keyboard[KEY_Q] - c->keyboard[KEY_E]);
	c->d_yaw = 1 * (c->keyboard[KEY_RIGHT] - c->keyboard[KEY_LEFT]);
	c->d_pitch = -1 * (c->keyboard[KEY_UP] - c->keyboard[KEY_DOWN]);
}

int t_controller_key_press(int keycode, void *p)
{
	t_controller *c;

	c = p;
	if (keycode == KEY_ESC)
		exit(0);
	c->keyboard[keycode] = 1;
	t_controller_update_state(c);
	return 0;
}

int t_controller_key_release(int keycode, void *p)
{
	t_controller *c;

	c = p;
	c->keyboard[keycode] = 0;
	t_controller_update_state(c);
	return 0;
}

void mlx_bind_keys(void *win, t_controller *c)
{
	mlx_hook(win, MLX_EVEN_KEY_PRESS, 0, t_controller_key_press, c);
	mlx_hook(win, MLX_EVEN_KEY_RELEASE, 0, t_controller_key_release, c);
}
