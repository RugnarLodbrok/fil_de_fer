/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoetess <rpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 21:45:11 by rpoetess          #+#    #+#             */
/*   Updated: 2019/11/22 16:11:56 by rpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "fdf.h"

void	t_controller_update_state(t_controller *c)
{
	c->v.z = 10 * (c->keyboard[KEY_W] - c->keyboard[KEY_S]);
	c->d_tilt = 1 * (c->keyboard[KEY_Q] - c->keyboard[KEY_E]);
	c->d_yaw = 1 * (c->keyboard[KEY_RIGHT] - c->keyboard[KEY_LEFT]);
	c->d_pitch = 1 * (c->keyboard[KEY_UP] - c->keyboard[KEY_DOWN]);
	c->status_prj = c->keyboard[KEY_P] - c->keyboard[KEY_I];
	c->d_zoom = c->keyboard[KEY_MINUS] - c->keyboard[KEY_PLUS];
}

int		t_controller_key_press(int keycode, void *p)
{
	t_controller *c;

	c = p;
	if (keycode == KEY_ESC)
		exit(0);
	c->keyboard[keycode] = 1;
	t_controller_update_state(c);
	return (0);
}

int		t_controller_key_release(int keycode, void *p)
{
	t_controller *c;

	c = p;
	c->keyboard[keycode] = 0;
	t_controller_update_state(c);
	return (0);
}

void	mlx_bind_keys(void *win, t_controller *c)
{
	mlx_hook(win, MLX_EVEN_KEY_PRESS, 0, t_controller_key_press, c);
	mlx_hook(win, MLX_EVEN_KEY_RELEASE, 0, t_controller_key_release, c);
}
