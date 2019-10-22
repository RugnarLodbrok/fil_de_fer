#include "fdf.h"

t_mat projection_isometric(double fov_width, double fov_height)
{
	return ((t_mat){
			2. / fov_width, 0, 0, 0,
			0, 2. / fov_height, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1});
}

void t_cam_init(t_cam *c, t_mat projection, t_point display_res)
{
	int w;
	int h;

	w = display_res.x;
	h = display_res.y;
	t_mat_reset(&c->view);
	c->proj = projection;
	c->disp = (t_mat){
			.5 * w, 0, 0, .5 * w,
			0, .5 * h, 0, .5 * h,
			0, 0, 0, 0,
			0, 0, 0, 1};
}

void t_cam_draw(t_cam *cam, void *p, t_mesh *mesh)
{
	uint i;
	t_vec p1;
	t_vec p2;
	t_mat m;

	(void)cam;
	i = 0;
	m = mesh->m;
	m = t_mat_mul(cam->view, m);
	m = t_mat_mul(cam->proj, m);
	m = t_mat_mul(cam->disp, m);
	while (i < mesh->n_edges)
	{
		p1 = mesh->vertices[mesh->edges[i].x].v;
		p2 = mesh->vertices[mesh->edges[i].y].v;
		p1 = t_vec_transform(p1, m);
		p2 = t_vec_transform(p2, m);
		line(p, p1, p2, 255 * GREEN);
		++i;
	}
}
