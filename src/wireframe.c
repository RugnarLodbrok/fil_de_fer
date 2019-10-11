#include "libft.h"
#include "ft_linalg.h"
#include "fdf.h"
#include <stdio.h>

void t_wireframe_init(t_wireframe *f)
{
	ft_bzero(f, sizeof(t_wireframe));
	t_mat_reset(&(f->m));
	f->n_vertices = 8;

	f->vertices = malloc(sizeof(t_vertex) * 8);
	f->vertices[0] = (t_vertex){(t_vec){0, 0, 0}, 255 * GREEN};
	f->vertices[1] = (t_vertex){(t_vec){100, 0, 0}, 255 * GREEN};
	f->vertices[2] = (t_vertex){(t_vec){100, 100, 0}, 255 * GREEN};
	f->vertices[3] = (t_vertex){(t_vec){0, 100, 0}, 255 * GREEN};
	f->vertices[4] = (t_vertex){(t_vec){0, 0, 100}, 255 * GREEN};
	f->vertices[5] = (t_vertex){(t_vec){100, 0, 100}, 255 * GREEN};
	f->vertices[6] = (t_vertex){(t_vec){100, 100, 100}, 255 * GREEN};
	f->vertices[7] = (t_vertex){(t_vec){0, 100, 100}, 255 * GREEN};

	f->n_edges = 12;
	f->edges = malloc(sizeof(t_point) * 12);
	f->edges[0] = (t_point){0, 1};
	f->edges[1] = (t_point){1, 2};
	f->edges[2] = (t_point){2, 3};
	f->edges[3] = (t_point){3, 0};

	f->edges[4] = (t_point){4, 5};
	f->edges[5] = (t_point){5, 6};
	f->edges[6] = (t_point){6, 7};
	f->edges[7] = (t_point){7, 4};

	f->edges[8] = (t_point){0, 4};
	f->edges[9] = (t_point){1, 5};
	f->edges[10] = (t_point){2, 6};
	f->edges[11] = (t_point){3, 7};
}

void t_wireframe_draw(t_wireframe *f, t_scene *s, int color)
{
	uint i;
	t_vec p1;
	t_vec p2;

	i = 0;
	while (i < f->n_edges)
	{
		p1 = f->vertices[f->edges[i].x].v;
		p2 = f->vertices[f->edges[i].y].v;
		line(s,
			 t_vec_transform(p1, f->m),
			 t_vec_transform(p2, f->m),
			 color);
		++i;
	}
}
