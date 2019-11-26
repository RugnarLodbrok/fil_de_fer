/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoetess <rpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 21:45:11 by rpoetess          #+#    #+#             */
/*   Updated: 2019/11/22 16:46:46 by rpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fdf.h"

void		t_controller_update_state(t_controller *c)
{
	c->v.z = 10 * (c->keyboard[KEY_W] - c->keyboard[KEY_S]);
	c->d_tilt = 1 * (c->keyboard[KEY_Q] - c->keyboard[KEY_E]);
	c->d_yaw = 1 * (c->keyboard[KEY_RIGHT] - c->keyboard[KEY_LEFT]);
	c->d_pitch = 1 * (c->keyboard[KEY_UP] - c->keyboard[KEY_DOWN]);
	c->status_prj = c->keyboard[KEY_P] - c->keyboard[KEY_I];
	c->d_zoom = c->keyboard[KEY_MINUS] - c->keyboard[KEY_PLUS];
	c->d_scroll = c->keyboard[KEY_HOME] - c->keyboard[KEY_END];
}

static int	t_controller_mouse_press(int button, int x, int y, t_controller *c)
{
	c->mouse.buttons[button] = 1;
	c->mouse.click_pos[button] = (t_point){x, y};
	return (0);
}

static int	t_controller_mouse_release(int button, int x, int y, t_controller *c)
{
	c->mouse.buttons[button] = 0;
	c->mouse.release_pos[button] = (t_point){x, y};
	return (0);
}

static int	t_controller_mouse_move(int x, int y, t_controller *c)
{
	c->mouse.pos = (t_point){x, y};
	return (0);
}

static int	t_controller_key_press(int keycode, void *p)
{
	t_controller *c;

	c = p;
	if (keycode == KEY_ESC)
		exit(0);
	c->keyboard[keycode] = 1;
	t_controller_update_state(c);
	return (0);
}

static int	t_controller_key_release(int keycode, void *p)
{
	t_controller *c;

	c = p;
	c->keyboard[keycode] = 0;
	t_controller_update_state(c);
	return (0);
}

void	bind_keys(void *win, t_controller *c)
{
	mlx_hook(win, MLX_EVENT_KEY_PRESS, 0, t_controller_key_press, c);
	mlx_hook(win, MLX_EVENT_KEY_RELEASE, 0, t_controller_key_release, c);
	mlx_hook(win, MLX_EVENT_MOUSE_PRESS, 0, t_controller_mouse_press, c);
	mlx_hook(win, MLX_EVENT_MOUSE_RELEASE, 0, t_controller_mouse_release, c);
	mlx_hook(win, MLX_EVENT_MOUSE_MOVE, 0, t_controller_mouse_move, c);
}
