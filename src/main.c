#include "libft.h"
#include "mlx.h"
#include "fdf.h"
//#include "mlx_int.h"
//#include "mlx_new_window.h"
#include <stdio.h>
#include "ft_linalg.h"

int loop_hook(void *s);
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
	void **objs;
} t_scene;

int main(void)
{
	int i;
	void *M;
	void *win;
	t_scene s;
	o_segment *o;

	ft_printf("HELLO\n");
	M = mlx_init();
	win = mlx_new_window(M, 800, 600, "fdf");
	mlx_pixel_put(M, win, 100, 100, 255 * GREEN);
	mlx_string_put(M, win, 150, 150, 255 * GREEN, "wake up, Neo!");

	s.M = M;
	s.win = win;
	CHECK0RET1(s.objs = malloc(sizeof(o_segment *) * 13));
	s.objs[12] = 0;
	for (i = 0; i < 12; ++i)
	{
		s.objs[i] = malloc(sizeof(o_segment));
		o = s.objs[i];
		o->color = 255 * GREEN;
		t_mat_reset(&(o->m));
		o->m.dx = 200;
		o->m.dy = 200;
	}
	((o_segment *)s.objs[0])->p0 = (t_vec){0, 0, 0};
	((o_segment *)s.objs[0])->p1 = (t_vec){100, 0, 0};

	((o_segment *)s.objs[1])->p0 = (t_vec){0, 0, 0};
	((o_segment *)s.objs[1])->p1 = (t_vec){0, 100, 0};

	((o_segment *)s.objs[2])->p0 = (t_vec){100, 100, 0};
	((o_segment *)s.objs[2])->p1 = (t_vec){100, 0, 0};

	((o_segment *)s.objs[3])->p0 = (t_vec){100, 100, 0};
	((o_segment *)s.objs[3])->p1 = (t_vec){0, 100, 0};

	((o_segment *)s.objs[4])->p0 = (t_vec){0, 0, 100};
	((o_segment *)s.objs[4])->p1 = (t_vec){100, 0, 100};

	((o_segment *)s.objs[5])->p0 = (t_vec){0, 0, 100};
	((o_segment *)s.objs[5])->p1 = (t_vec){0, 100, 100};

	((o_segment *)s.objs[6])->p0 = (t_vec){100, 100, 100};
	((o_segment *)s.objs[6])->p1 = (t_vec){100, 0, 100};

	((o_segment *)s.objs[7])->p0 = (t_vec){100, 100, 100};
	((o_segment *)s.objs[7])->p1 = (t_vec){0, 100, 100};

	((o_segment *)s.objs[8])->p0 = (t_vec){0, 0, 0};
	((o_segment *)s.objs[8])->p1 = (t_vec){0, 0, 100};

	((o_segment *)s.objs[9])->p0 = (t_vec){0, 100, 0};
	((o_segment *)s.objs[9])->p1 = (t_vec){0, 100, 100};

	((o_segment *)s.objs[10])->p0 = (t_vec){100, 100, 0};
	((o_segment *)s.objs[10])->p1 = (t_vec){100, 100, 100};

	((o_segment *)s.objs[11])->p0 = (t_vec){100, 0, 0};
	((o_segment *)s.objs[11])->p1 = (t_vec){100, 0, 100};

	mlx_loop_hook(M, loop_hook, &s);

	mlx_loop(M);
}

int loop_hook(void *s)
{
	int i;
	o_segment *obj;
	t_mat rot;

	rot = t_mat_rot_point((t_vec){.1, 1, .3}, 0.04, (t_vec){250, 250, 50});
	for (i = 0; i < 12; ++i)
	{
		obj = ((t_scene *)s)->objs[i];
		line(((t_scene *)s)->M, ((t_scene *)s)->win,
			 t_vec_transform(obj->p0, obj->m),
			 t_vec_transform(obj->p1, obj->m), 0);
	}
	for (i = 0; i < 12; ++i)
	{
		obj = ((t_scene *)s)->objs[i];
		obj->m = t_mat_mul(&rot, &(obj->m));
		line(((t_scene *)s)->M, ((t_scene *)s)->win,
			 t_vec_transform(obj->p0, obj->m),
			 t_vec_transform(obj->p1, obj->m), obj->color);
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
