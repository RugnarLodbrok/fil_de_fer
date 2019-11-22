/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoetess <rpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 21:29:33 by rpoetess          #+#    #+#             */
/*   Updated: 2019/11/22 16:11:56 by rpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "math.h"

void	t_cam_init_projection(t_cam *c)
{
	double tg;
	double near;
	double ze;

	ze = exp(c->zoom / 100);
	tg = ft_sin(radians(FOV / 2)) / ft_cos(radians(FOV / 2)) * ze;
	near = 10.;
	if (c->projection_type == PROJ_PERSPECTIVE)
		c->proj = projection_perspective(near, tg * near,
							tg * near * WIN_H / WIN_W,
							9999.);
	else
		c->proj = projection_isometric((double)WIN_W * ze,
							(double)WIN_H * ze);
}

void	t_cam_init(t_cam *c, t_point display_res)
{
	int w;
	int h;

	w = display_res.x;
	h = display_res.y;
	t_mat_reset(&c->v3);
	t_mat_translate(&c->v3, (t_vec){0, 0, -400});
	c->v1 = (t_mat){1, 0, 0, 0,
					0, 0, -1, 0,
					0, 1, 0, 0,
					0, 0, 0, 1};
	t_mat_reset(&c->v2);
	c->disp = (t_mat){.5 * w, 0, 0, .5 * w,
					0, .5 * h, 0, .5 * h,
					0, 0, 0, 0,
					0, 0, 0, 1};
	c->zoom = 0;
	c->projection_type = PROJ_PERSPECTIVE;
	t_cam_init_projection(c);
}

void	t_cam_draw(t_cam *cam, void *p, t_mesh *mesh)
{
	uint	i;
	t_vec	p1;
	t_vec	p2;
	t_mat	m;

	i = 0;
	m = mesh->m;
	m = t_mat_mul(cam->v1, m);
	m = t_mat_mul(cam->v2, m);
	m = t_mat_mul(cam->v3, m);
	m = t_mat_mul(cam->proj, m);
	while (i < mesh->n_edges)
	{
		p1 = mesh->vertices[mesh->edges[i].x].v;
		p2 = mesh->vertices[mesh->edges[i].y].v;
		++i;
		p1 = t_vec_transform4(p1, m);
		if (p1.z < -1. || p1.z > 1.)
			continue;
		p2 = t_vec_transform4(p2, m);
		if (p2.z < -1. || p2.z > 1.)
			continue;
		p1 = t_vec_transform(p1, cam->disp);
		p2 = t_vec_transform(p2, cam->disp);
		line(p, p1, p2, (uint)(255 * GREEN));
	}
}

void	t_cam_move(t_cam *cam, t_controller *ctrl)
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
	if (ctrl->v.x || ctrl->v.z)
	{
		t_mat_translate(&cam->v3, ctrl->v);
	}
	if (ctrl->d_zoom)
	{
		cam->zoom += ctrl->d_zoom;
		t_cam_init_projection(cam);
	}
}
