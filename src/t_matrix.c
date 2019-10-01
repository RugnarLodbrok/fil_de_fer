#include "t_matrix.h"
#include "t_vector.h"

t_vec t_vec_transform(t_vec v, t_mat A)
{
	t_vec r;

	r.x = (A.x1 * v.x + A.y1 * v.y + A.z1 * v.z) + A.dx;
	r.y = (A.x2 * v.x + A.y2 * v.y + A.z2 * v.z) + A.dy;
	r.z = (A.x3 * v.x + A.y3 * v.y + A.z3 * v.z) + A.dz;
	return (r);
}

t_mat t_mat_mul(t_mat A, t_mat B)
{
	t_mat R;

	//Rr = (Aa)*(Bb)
	//R = AB
	//r = Ab + a
	R.dx = A.dx + (A.x1 * B.dx + A.y1 * B.dy + A.z1 * B.dz) + A.dx;
	R.dy = A.dy + (A.x2 * B.dx + A.y2 * B.dy + A.z2 * B.dz) + A.dy;
	R.dz = A.dz + (A.x3 * B.dx + A.y3 * B.dy + A.z3 * B.dz) + A.dz;

	R.x1 = (A.x1 * B.x1 + A.x2 * B.y1 + A.x3 * B.z1);
	R.y1 = (A.y1 * B.x1 + A.y2 * B.y1 + A.y3 * B.z1);
	R.z1 = (A.z1 * B.x1 + A.z2 * B.y1 + A.z3 * B.z1);

	R.x2 = (A.x1 * B.x2 + A.x2 * B.y2 + A.x3 * B.z2);
	R.y2 = (A.y1 * B.x2 + A.y2 * B.y2 + A.y3 * B.z2);
	R.z2 = (A.z1 * B.x2 + A.z2 * B.y2 + A.z3 * B.z2);

	R.x3 = (A.x1 * B.x3 + A.x2 * B.y3 + A.x3 * B.z3);
	R.y3 = (A.y1 * B.x3 + A.y2 * B.y3 + A.y3 * B.z3);
	R.z3 = (A.z1 * B.x3 + A.z2 * B.y3 + A.z3 * B.z3);

	return (R);
}
