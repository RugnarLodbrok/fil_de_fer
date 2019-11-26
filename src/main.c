/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoetess <rpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 21:32:59 by rpoetess          #+#    #+#             */
/*   Updated: 2019/11/21 22:00:58 by rpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "libft.h"
#include "fdf.h"
#include <time.h>
#include "ft_linalg.h"

int		main(int ac, char **av)
{
	t_app	app;

	if (ac != 2)
		ft_error_exit("Usage: ./fdf [FILE]");
	t_app_init(&app, av[1]);
	print_info(&app);
	app.time = clock();
	app.frame_time = clock();
	mlx_loop_hook(app.M, loop_hook, &app);
	bind_keys(app.win, &app.controller);
	mlx_hook(app.win, MLX_EVENT_EXIT, 0, &close_hook, 0);
	mlx_loop(app.M);
	return (0);
}
