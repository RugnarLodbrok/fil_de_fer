#include "libft.h"
#include "t_matrix.h"
#include "t_vector.h"

t_mat *t_mat_reset(t_mat *m)
{
	ft_bzero(m, sizeof(*m));
	m->x1 = 1;
	m->y2 = 1;
	m->z3 = 1;
	return m;
}

t_vec t_vec_transform(t_vec v, t_mat A)
{
	t_vec r;

	r.x = (A.x1 * v.x + A.y1 * v.y + A.z1 * v.z) + A.dx;
	r.y = (A.x2 * v.x + A.y2 * v.y + A.z2 * v.z) + A.dy;
	r.z = (A.x3 * v.x + A.y3 * v.y + A.z3 * v.z) + A.dz;
	return (r);
}

t_mat t_mat_mul(t_mat *A, t_mat *B)
{
	t_mat R;

	/*
	 * Rr = (Aa)*(Bb)
	 * R = AB
	 * r = Ab + a
	*/
	R.dx = A->dx + (A->x1 * B->dx + A->y1 * B->dy + A->z1 * B->dz) + A->dx;
	R.dy = A->dy + (A->x2 * B->dx + A->y2 * B->dy + A->z2 * B->dz) + A->dy;
	R.dz = A->dz + (A->x3 * B->dx + A->y3 * B->dy + A->z3 * B->dz) + A->dz;

	R.x1 = (A->x1 * B->x1 + A->x2 * B->y1 + A->x3 * B->z1);
	R.y1 = (A->y1 * B->x1 + A->y2 * B->y1 + A->y3 * B->z1);
	R.z1 = (A->z1 * B->x1 + A->z2 * B->y1 + A->z3 * B->z1);

	R.x2 = (A->x1 * B->x2 + A->x2 * B->y2 + A->x3 * B->z2);
	R.y2 = (A->y1 * B->x2 + A->y2 * B->y2 + A->y3 * B->z2);
	R.z2 = (A->z1 * B->x2 + A->z2 * B->y2 + A->z3 * B->z2);

	R.x3 = (A->x1 * B->x3 + A->x2 * B->y3 + A->x3 * B->z3);
	R.y3 = (A->y1 * B->x3 + A->y2 * B->y3 + A->y3 * B->z3);
	R.z3 = (A->z1 * B->x3 + A->z2 * B->y3 + A->z3 * B->z3);

	return (R);
}

t_mat *t_mat_mul_c(t_mat *m, double c)
{
	m->x1 *= c;
	m->x2 *= c;
	m->x3 *= c;
	m->dx *= c;
	m->y1 *= c;
	m->y2 *= c;
	m->y3 *= c;
	m->dy *= c;
	m->z1 *= c;
	m->z2 *= c;
	m->z3 *= c;
	m->dz *= c;
	return (m);
}

t_mat *t_mat_add(t_mat *a, t_mat *b)
{
	a->x1 += b->x1;
	a->x2 += b->x2;
	a->x3 += b->x3;
	a->dx += b->dx;
	a->y1 += b->y1;
	a->y2 += b->y2;
	a->y3 += b->y3;
	a->dy += b->dy;
	a->z1 += b->z1;
	a->z2 += b->z2;
	a->z3 += b->z3;
	a->dz += b->dz;
	return (a);
}

t_mat t_mat_rot(t_vec axis, double theta)
{
	t_mat w;
	t_mat w2;

	t_vec_normalize(&axis);
	w.x1 = 0;
	w.x2 = -axis.z;
	w.x3 = axis.y;
	w.y1 = axis.z;
	w.y2 = 0;
	w.y3 = -axis.x;
	w.z1 = -axis.y;
	w.z2 = axis.x;
	w.z3 = 0;
	w2 = t_mat_mul(&w, &w);
	t_mat_mul_c(&w, ft_sin(theta));
	t_mat_mul_c(&w2, 1 - ft_cos(theta));
	w.x1 += 1.;
	w.y2 += 1.;
	w.z3 += 1.;
	t_mat_add(&w, &w2);
	return (w);
}
