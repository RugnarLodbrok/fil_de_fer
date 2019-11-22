/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoetess <rpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 21:02:29 by rpoetess          #+#    #+#             */
/*   Updated: 2019/11/21 22:26:09 by rpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "libft.h"
#include "fdf.h"

static void	t_init_se(t_se *se)
{
	se->start_x = 0;
	se->start_y = 0;
	se->end_x = 200;
	se->end_y = WIN_H;
}

static void	ft_free_area(t_app *app)
{
	int		i;
	int		j;
	t_se	se;

	t_init_se(&se);
	j = se.start_y;
	while (j < se.end_y)
	{
		i = se.start_x;
		while (i < se.end_x)
		{
			mlx_pixel_put(app->M, app->win, i, j, GRAYSCALE * 64);
			i++;
		}
		j++;
	}
}

static void sidebar_draw_controls(t_app *app, int y)
{
	uint c1;
	c1 = GRAYSCALE * 192;

	mlx_string_put(app->M, app->win, 10, y += 45, 0xab4444, "controls:");
	mlx_string_put(app->M, app->win, 10, y += 20, c1, "exit:         [ESC]");
	mlx_string_put(app->M, app->win, 10, y += 20, c1, "projection:   [I/P]");
	mlx_string_put(app->M, app->win, 10, y += 20, c1, "zoom:         [+/-]");
	mlx_string_put(app->M, app->win, 10, y += 20, c1, "z-scale: [home/end]");
	mlx_string_put(app->M, app->win, 10, y += 20, c1, "look:      [arrows]");
}

void		print_info(t_app *app)
{
	int		y;
	char	*pers;
	uint	c1;

	c1 = GRAYSCALE * 192;
	ft_free_area(app);
	y = 0;
	mlx_string_put(app->M, app->win, 10, y += 15, 0xa140c7, app->map_name);
	mlx_string_put(app->M, app->win, 10, y += 25, c1, "projection:");
	if (app->cam.projection_type == PROJ_PERSPECTIVE)
		pers = "perspective";
	else
		pers = "isometic";
	mlx_string_put(app->M, app->win, 10, y += 15, c1, pers);
	sidebar_draw_controls(app, y);
}

void		ft_change_projection(t_app *app)
{
	app->controller.projection = app->controller.status_prj;
	if (app->controller.status_prj == 1)
		app->cam.projection_type = PROJ_PERSPECTIVE;
	else
		app->cam.projection_type = PROJ_ISOMETRIC;
	t_cam_init_projection(&app->cam);
	print_info(app);
}
