#ifndef T_MATRIX_H
# define T_MATRIX_H

#include "t_vector.h"

/*
 * | x1 x2 x3 dx |
 * | y1 y2 y3 dy |
 * | z1 z2 z3 dz |
 * | 0  0  0  1  |
 */

typedef struct
{
	double x1;
	double x2;
	double x3;
	double dx;

	double y1;
	double y2;
	double y3;
	double dy;

	double z1;
	double z2;
	double z3;
	double dz;
} t_mat;

t_mat *t_mat_reset(t_mat *m);
t_vec t_vec_transform(t_vec v, t_mat A);
t_mat t_mat_mul(t_mat *A, t_mat *B);
t_mat t_mat_rot(t_vec axis, double theta);

#endif
