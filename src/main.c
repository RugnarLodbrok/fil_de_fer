#include "mlx.h"
#include "libft.h"
#include "fdf.h"
#include <time.h>
#include "ft_linalg.h"

int loop_hook(void *p);

int close_hook(void *param)
{
	(void)param;
	exit(0);
}

void ft_free_area(t_app *app, int x_s, int y_s, int x_e, int y_e)
{
	int i;
	int j;

	i = x_s;
	j = y_s;
	while (j < y_e)
	{
		while (i < x_e)
		{
			mlx_pixel_put(app->M, app->win, i, j, GRAYSCALE*64);
			i++;
		}
		i = x_s;
		j++;
	}
}

void print_info(t_app *app)
{
	void *mlx;
	void *win;
	int y;
	char *pers;
	uint c1;

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
//	printf("%d\n", y);
	mlx_string_put(mlx, win, 10, y += 45, 0xab4444, "controls:");
	mlx_string_put(mlx, win, 10, y += 20, c1, "  exit:    ESC");
	mlx_string_put(mlx, win, 10, y += 25, c1, "isometric:   [I]");
	mlx_string_put(mlx, win, 10, y += 20, c1, "perspective: [P]");
	mlx_string_put(mlx, win, 10, y += 20, c1, "");
	mlx_string_put(mlx, win, 10, y += 20, c1, "      look:");
	mlx_string_put(mlx, win, 10, y += 20, c1, "      [up]");
	mlx_string_put(mlx, win, 10, y += 20, c1, "[left]    [right]");
	mlx_string_put(mlx, win, 10, y += 20, c1, "     [down]");
}


void ft_change_projection(t_app *app)
{
	char *line;

	if (app->controller.status_prj == 1)
		line = "perspective";
	else
		line = "isometric";
	mlx_string_put(app->M, app->win, 10, 55, 0xFFFFFF, line);
	app->controller.projection = app->controller.status_prj;
	if (app->controller.status_prj == 1)
		app->cam.projection_type = PROJ_PERSPECTIVE;
	else
		app->cam.projection_type = PROJ_ISOMETRIC;
	t_cam_init_projection(&app->cam);
	print_info(app);
}

void update_debug(t_app *app, double dt)
{
	int i;
	static double a = 0;
	double dx;
	double dy;

	a += 0.0002;
	(void)dt;
	t_framebuffer_clear(&app->framebuffer);
	line(app,
		 (t_vec){1., 1., 0},
		 (t_vec){3., 1, 0}, WHITE);
	for (i = 0; i < 360; i += 5)
	{
		dx = 34. * ft_cos(a + radians(1. * i));
		dy = 34. * ft_sin(a + radians(1. * i));
		line(app,
			 (t_vec){50., 50., 0},
			 (t_vec){50. + dx, 50. + dy, 0}, WHITE);
		line(app,
			 (t_vec){50. + dx, 50. + dy, 0},
			 (t_vec){50. + 1.4 * dx, 50. + 1.4 * dy, 0}, WHITE);
	}
	t_framebuffer_upscale(&app->framebuffer, 8);
	mlx_put_image_to_window(app->M, app->win, app->framebuffer.image, 0, 0);
}

void update(t_app *app, double dt)
{
	int i;
	t_mesh *obj;

	(void)dt;
	t_framebuffer_clear(&app->framebuffer);
	if (app->controller.status_prj &&
		app->controller.status_prj != app->controller.projection)
		ft_change_projection(app);
//	t_zoom(app);
	//todo: https://github.com/keuhdall/images_example
	t_cam_move(&app->cam, &app->controller);
	for (i = 0; (obj = app->objs[i]); ++i)
	{
		t_cam_draw(&app->cam, app, obj);
	}
	mlx_put_image_to_window(app->M, app->win, app->framebuffer.image, 200, 0);
}

int loop_hook(void *p)
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

int mouse_hook(int button, int x, int y, void *param)
{
	(void)param;
	(void)button;
	ft_printf("mouse: %d %d\n", x, y);
	return (0);
}

int main(int argc, char **argv)
{
	t_app app;

	t_app_init(&app);
	print_info(&app);
	line(&app, (t_vec){0, 0, 0}, (t_vec){50, 200, 0}, (RED * 255));
	app.time = clock();
	app.frame_time = clock();
	mlx_loop_hook(app.M, loop_hook, &app);
	mlx_bind_keys(app.win, &app.controller);
	mlx_hook(app.win, MLX_EVENT_EXIT, 0, &close_hook, 0);
	mlx_loop(app.M);
	return (0);
}
