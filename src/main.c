#include "mlx.h"
#include "libft.h"
#include "fdf.h"
#include <stdio.h>
#include <time.h>
#include "ft_linalg.h"

int		loop_hook(void *p);

int		close_hook(void *param)
{
	(void)param;
	exit(0);
}

void	print_info(t_app *app, char *name)
{
	void	*mlx;
	void	*win;
	int		y;

	y = 0;
	mlx = app->M;
	win = app->win;
	mlx_string_put(mlx, win, 10, y += 15, 0xa140c7, name);
	mlx_string_put(mlx, win, 10, y += 25, 0xFFFFFF, "projection:");
	mlx_string_put(mlx, win, 10, y += 15, 0xFFFFFF, "perspective");
//	printf("%d\n", y);
	mlx_string_put(mlx, win, 10, y += 45, 0xab4444, "FAQ:");
	mlx_string_put(mlx, win, 10, y += 25, 0xFFFFFF, "isometric:   i");
	mlx_string_put(mlx, win, 10, y += 20, 0xFFFFFF, "perspective: p");
	mlx_string_put(mlx, win, 10, y += 20, 0xFFFFFF, "x-axis:    L/R");
	mlx_string_put(mlx, win, 10, y += 20, 0xFFFFFF, "y-axis:    U/D");
	mlx_string_put(mlx, win, 10, y += 20, 0xFFFFFF, "  exit:    ESC");
}

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
			
			app->framebuffer.data[i * sizeof(uint) + j * WIN_W * sizeof(uint)] = 0;
			i++;
		}
		i = x_s;
		j++;
	}
}

void	ft_change_projection(t_app *app)
{
	char	*line;
	double	near;
	double	tg;

	tg = ft_sin(radians(FOV / 2)) / ft_cos(radians(FOV / 2));
	near = 10.;
	line = 0;
	if (app->controller.status_prj == 1 || app->controller.status_prj == -1)
		if (app->controller.status_prj != app->controller.projection)
		{
			(line) ? free(line) : 0;
			//ft_free_area(app, 10, 55, 30, 100);
			//ft_bzero(&app->framebuffer.data[10 * 4 + 55 * WIN_W * 4], 100000);
			(app->controller.status_prj == 1) ?
			(line = ft_strdup("perspective")) : (line = ft_strdup("isometric"));
			mlx_string_put(app->M, app->win, 10, 55, 0xFFFFFF, line);
			//free(app->cam);
			app->controller.projection = app->controller.status_prj;
			if (app->controller.status_prj == 1)
				t_cam_init(&app->cam, projection_perspective(near, tg * near,
					tg * near * WIN_H / WIN_W, 9999.), (t_point){WIN_W, WIN_H});
			else
				t_cam_init(&app->cam,
					projection_isometric((double)WIN_W / 5, (double)WIN_H / 5),
					(t_point){WIN_W, WIN_H});
		}
	free(line);
	//ft_putnbr(app->controller.status_prj);
}

void	update(t_app *app, double dt)
{
	int		i;
	t_mesh	*obj;

	(void)dt;
	t_framebuffer_clear(&app->framebuffer);
	ft_change_projection(app);
	//todo: https://github.com/keuhdall/images_example
	t_cam_move(&app->cam, &app->controller);
	for (i = 0; (obj = app->objs[i]); ++i)
	{
		t_cam_draw(&app->cam, app, obj);
	}
	mlx_put_image_to_window(app->M, app->win, app->framebuffer.image, 150, 0);
}

int		loop_hook(void *p)
{
	t_app *app;
	double dt;

	app = p;
	app->time = clock();
	dt = (double)(app->time - app->frame_time) / CLOCKS_PER_SEC;
	if (dt > FRAME_TIME)
	{
		app->frame_time = app->time;
		update(app, dt);
	}
	return (0);
}

int		mouse_hook(int button, int x, int y, void *param)
{
	(void)param;
	(void)button;
	ft_printf("mouse: %d %d\n", x, y);
	return (0);
}

int		main(int argc, char **argv)
{
	t_app app;

	t_app_init(&app);
	if (argc > 1)
		print_info(&app, argv[1]);
	line(&app, (t_vec){0, 0, 0}, (t_vec){50, 200, 0}, (RED * 255));
	app.time = clock();
	app.frame_time = clock();
	mlx_loop_hook(app.M, loop_hook, &app);
	mlx_bind_keys(app.win, &app.controller);
	mlx_hook(app.win, MLX_EVENT_EXIT, 0, &close_hook, 0);
	mlx_loop(app.M);
	return (0);
}
