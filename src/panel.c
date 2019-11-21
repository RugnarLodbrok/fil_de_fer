/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoetess <rpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 21:02:29 by rpoetess          #+#    #+#             */
/*   Updated: 2019/11/21 21:28:17 by rpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "libft.h"
#include "fdf.h"

void	ft_free_area(t_app *app, int x_s, int y_s, int x_e, int y_e)
{
	int	i;
	int	j;

	i = x_s;
	j = y_s;
	while (j < y_e)
	{
		while (i < x_e)
		{
			mlx_pixel_put(app->M, app->win, i, j, GRAYSCALE * 64);
			i++;
		}
		i = x_s;
		j++;
	}
}

void	print_info(t_app *app)
{
	void	*mlx;
	void	*win;
	int		y;
	char	*pers;
	uint	c1;

	c1 = GRAYSCALE * 192;
	ft_free_area(app, 0, 0, 200, WIN_H);
	y = 0;
	mlx = app->M;
	win = app->win;
	mlx_string_put(mlx, win, 10, y += 15, 0xa140c7, app->map_name);
	mlx_string_put(mlx, win, 10, y += 25, c1, "projection:");
	if (app->cam.projection_type == PROJ_PERSPECTIVE)
		pers = "perspective";
	else
		pers = "isometic";
	mlx_string_put(mlx, win, 10, y += 15, c1, pers);
	mlx_string_put(mlx, win, 10, y += 45, 0xab4444, "controls:");
	mlx_string_put(mlx, win, 10, y += 20, c1, "  exit:     [ESC]");
	mlx_string_put(mlx, win, 10, y += 20, c1, "isometric:   [I]");
	mlx_string_put(mlx, win, 10, y += 20, c1, "perspective: [P]");
	mlx_string_put(mlx, win, 10, y += 20, c1, "");
	mlx_string_put(mlx, win, 10, y += 20, c1, "      look:");
	mlx_string_put(mlx, win, 10, y += 20, c1, "      [up]");
	mlx_string_put(mlx, win, 10, y += 35, c1, "[left]    [right]");
	mlx_string_put(mlx, win, 10, y += 35, c1, "     [down]");
}

void	ft_change_projection(t_app *app)
{
	app->controller.projection = app->controller.status_prj;
	if (app->controller.status_prj == 1)
		app->cam.projection_type = PROJ_PERSPECTIVE;
	else
		app->cam.projection_type = PROJ_ISOMETRIC;
	t_cam_init_projection(&app->cam);
	print_info(app);
}
