#include "fdf.h"

void t_cam_init(t_cam *c)
{
	t_mat_reset(&c->m);
	t_mat_reset(&c->p);
}
