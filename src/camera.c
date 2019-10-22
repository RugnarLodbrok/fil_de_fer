#include "fdf.h"

t_mat projection_isometric(double fov_width, double fov_height)
{
	return ((t_mat){-2. / fov_width, 0, 0, 0,
					0, -2. / fov_height, 0, 0,
					0, 0, 1, 0,
					0, 0, 0, 1});
}

t_mat projection_perspective(double n, double w, double h, double f)
{
	double l = -w / 2;
	double r = w / 2;
	double b = -h / 2;
	double t = h / 2;

	return (t_mat){
			2 * n / (r - l), 0, (r + l) / (r - l), 0,
			0, 2 * n / (t - b), (t + b) / (t - b), 0,
			0, 0, -(f + n) / (f - n), -2 * f * n / (f - n),
			0, 0, -1, 0};
}

void t_cam_init(t_cam *c, t_mat projection, t_point display_res)
{
	int w;
	int h;

	w = display_res.x;
	h = display_res.y;
	t_mat_reset(&c->v2);
	c->v1 = (t_mat){1, 0, 0, 0,
					0, 0, -1, 0,
					0, 1, 0, 0,
					0, 0, 0, 1};
	c->proj = projection;
	c->disp = (t_mat){.5 * w, 0, 0, .5 * w,
					  0, -.5 * h, 0, .5 * h,
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
	m = t_mat_mul(cam->v1, m);
	m = t_mat_mul(cam->v2, m);
//	m = t_mat_mul(cam->proj, m);
//	m = t_mat_mul(cam->disp, m);
	while (i < mesh->n_edges)
	{
		p1 = mesh->vertices[mesh->edges[i].x].v;
		p2 = mesh->vertices[mesh->edges[i].y].v;

		p1 = t_vec_transform(p1, m);
		p1 = t_vec_transform4(p1, cam->proj);
		p1 = t_vec_transform(p1, cam->disp);

		p2 = t_vec_transform(p2, m);
		p2 = t_vec_transform4(p2, cam->proj);
		p2 = t_vec_transform(p2, cam->disp);
		line(p, p1, p2, 255 * GREEN);
		++i;
	}
}

void t_cam_move(t_cam *cam, t_controller *ctrl)
{
	if (ctrl->d_yaw)
	{
		cam->v1 = t_mat_mul(cam->v1, t_mat_rot(
				(t_vec){0, 0, 1},
				radians(ctrl->d_yaw)));
	}
	if (ctrl->d_pitch)
	{
		cam->v2 = t_mat_mul(cam->v2, t_mat_rot(
				(t_vec){1, 0, 0},
				radians(ctrl->d_pitch)));
	}

}
