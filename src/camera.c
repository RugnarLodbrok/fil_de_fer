#include "fdf.h"

void t_cam_init(t_cam *c)
{
	t_mat_reset(&c->m);
	t_mat_reset(&c->p);
}

void t_cam_draw(t_cam *c, void *p, t_mesh *mesh, int color)
{
	uint i;
	t_vec p1;
	t_vec p2;

	(void)c;
	i = 0;
	while (i < mesh->n_edges)
	{
		p1 = mesh->vertices[mesh->edges[i].x].v;
		p2 = mesh->vertices[mesh->edges[i].y].v;
		line(p,
			 t_vec_transform(p1, mesh->m),
			 t_vec_transform(p2, mesh->m),
			 color);
		++i;
	}
}
