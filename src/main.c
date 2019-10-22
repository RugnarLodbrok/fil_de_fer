#include "mlx.h"
#include "libft.h"
#include "fdf.h"
#include <stdio.h>
#include "ft_linalg.h"

int loop_hook(void *p);
int mouse_hook(int button, int x, int y, void *param);
int key_hook(int keycode, void *p);

int main(void)
{
	void *M;
	void *win;
	t_app app;
	t_mesh m;

	M = mlx_init();
	win = mlx_new_window(M, WIN_W, WIN_H, "fdf");
	mlx_string_put(M, win, 150, 150, 255 * GREEN, "wake up, Neo!");

	ft_bzero(&app, sizeof(app));
	app.momentum = (t_vec){.1, 1, .3};
	t_vec_normalize(&(app.momentum));
	app.momentum = t_vec_mul(app.momentum, 0.2);
	app.M = M;
	app.win = win;
	app.objs = malloc(sizeof(t_mesh *) * 2);
	app.objs[0] = &m;
	app.objs[1] = 0;
	m = t_mesh_landscape_from_file("../test.txt");
	t_cam_init(&app.cam,
			   projection_isometric((double)WIN_W / 2, (double)WIN_H / 2),
			   (t_point){WIN_W, WIN_H});

	mlx_loop_hook(M, loop_hook, &app);
	mlx_key_hook(win, key_hook, &app);
	mlx_loop(M);
}

int loop_hook(void *p)
{
	int i;
	t_mesh *obj;
	t_mat rot;
	t_app *s;

	s = (t_app *)p;
	if (!t_vec_len(s->momentum))
		return (0);
	obj = s->objs[0];
	rot = t_mat_rotation(s->momentum, t_vec_len(s->momentum), (t_vec){obj->m.data[0][3], obj->m.data[1][3], 0});
	t_vec_decay(&(s->momentum), 0.003);
	for (i = 0; (obj = s->objs[i]); ++i)
	{
		t_cam_draw(&s->cam, p, obj, 0);
	}
	for (i = 0; (obj = s->objs[i]); ++i)
	{
		obj->m = t_mat_mul(rot, obj->m);
		t_cam_draw(&s->cam, p, obj, 255 * GREEN);
	}
	mlx_pixel_put(((t_app *)s)->M, ((t_app *)s)->win, 200, 200, 255 * RED);
	return (0);
}

int mouse_hook(int button, int x, int y, void *param)
{
	(void)param;
	(void)button;
	ft_printf("mouse: %d %d\n", x, y);
	return (0);
}

int key_hook(int keycode, void *p)
{
	t_app *s;

	s = (t_app *)p;
	if (keycode == KEY_LEFT)
	{
		s->momentum = t_vec_add(s->momentum, (t_vec){0, STEP, 0});
	}
	else if (keycode == KEY_RIGHT)
	{
		s->momentum = t_vec_add(s->momentum, (t_vec){0, -STEP, 0});
	}
	else if (keycode == KEY_UP)
	{
		s->momentum = t_vec_add(s->momentum, (t_vec){-STEP, 0, 0});
	}
	else if (keycode == KEY_DOWN)
	{
		s->momentum = t_vec_add(s->momentum, (t_vec){STEP, 0, 0});
	}
	return (0);
}
