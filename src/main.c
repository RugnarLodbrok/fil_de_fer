#include "libft.h"
#include "mlx.h"
#include "fdf.h"
#include <stdio.h>
#include "ft_linalg.h"
//#include "mlx_int.h"
//#include "mlx_new_window.h"

int loop_hook(void *s);
int mouse_hook(int button, int x, int y, void *param);

int main(void)
{
	void *M;
	void *win;
	t_scene s;
	t_wireframe w;

	ft_printf("HELLO\n");
	M = mlx_init();
	win = mlx_new_window(M, 800, 600, "fdf");
	mlx_pixel_put(M, win, 100, 100, 255 * GREEN);
	mlx_string_put(M, win, 150, 150, 255 * GREEN, "wake up, Neo!");

	s.M = M;
	s.win = win;
	s.objs = malloc(sizeof(t_wireframe *) * 2);
	s.objs[0] = &w;
	s.objs[1] = 0;
	t_wireframe_init(&w);
	w.m.dx = 200;
	w.m.dy = 200;

	mlx_loop_hook(M, loop_hook, &s);
	mlx_loop(M);
}

int loop_hook(void *p)
{
	int i;
	t_wireframe *obj;
	t_mat rot;
	t_scene *s;

	s = (t_scene *)p;
	rot = t_mat_rot_point((t_vec){.1, 1, .3}, 0.04, (t_vec){250, 250, 50});
	for (i = 0; s->objs[i]; ++i)
	{
		t_wireframe_draw(s->objs[i], s, 0);
	}
	for (i = 0; s->objs[i]; ++i)
	{
		obj = s->objs[i];
		obj->m = t_mat_mul(&rot, &(obj->m));
		t_wireframe_draw(s->objs[i], s, 255 * GREEN);
	}
	mlx_pixel_put(((t_scene *)s)->M, ((t_scene *)s)->win, 250, 250, 255 * RED);
	return (0);
}

int mouse_hook(int button, int x, int y, void *param)
{
	(void)param;
	(void)button;
	ft_printf("mouse: %d %d\n", x, y);
	return (0);
}
