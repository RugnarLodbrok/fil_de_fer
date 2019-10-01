#include "libft.h"
#include "mlx.h"
#include "fdf.h"
//#include "mlx_int.h"
//#include "mlx_new_window.h"
#include <stdio.h>
#include <t_vector.h>
#include <t_matrix.h>

int loop_hook(void *param);
int mouse_hook(int button, int x, int y, void *param);

typedef struct
{
	t_vec p0;
	t_vec p1;
	t_mat m;
	int color;
} o_segment;

typedef struct
{
	void *M;
	void *win;
	void *obj;
} t_scene;

int main(void)
{
	void *M;
	void *win;
	t_scene s;
	o_segment o;

	ft_printf("HELLO\n");
	M = mlx_init();
	win = mlx_new_window(M, 800, 600, "fdf");
	mlx_pixel_put(M, win, 100, 100, 255 * GREEN);
	mlx_string_put(M, win, 150, 150, 255 * GREEN, "HELLO MLX!");

	s.M = M;
	s.win = win;
	s.obj = &o;
	o.color = 255 * GREEN;
	o.p0 = (t_vec){0, 0, 0};
	o.p1 = (t_vec){100, 100, 0};
	t_mat_reset(&(o.m));

	mlx_loop_hook(M, loop_hook, &s);
//	mlx_mouse_hook(win, mouse_hook, 0);


	mlx_loop(M);
}

int loop_hook(void *s)
{
	o_segment *obj;
	t_vec v1;
	t_vec v2;
	t_point p1;
	t_point p2;
	t_mat rot;

	obj = ((t_scene *)s)->obj;
	rot = t_mat_rot((t_vec){0, 0, 1}, 0.001);
	obj->m = t_mat_mul(&rot, &(obj->m));
	v1 = t_vec_transform(obj->p0, obj->m);
	v2 = t_vec_transform(obj->p1, obj->m);
	p1.x = (int)v1.x;
	p1.y = (int)v1.y;
	p2.x = (int)v2.x;
	p2.y = (int)v2.y;
	line(((t_scene *)s)->M, ((t_scene *)s)->win, p1, p2);
	return (0);
}

int mouse_hook(int button, int x, int y, void *param)
{
	(void)param;
	(void)button;
	ft_printf("mouse: %d %d\n", x, y);
	return (0);
}
