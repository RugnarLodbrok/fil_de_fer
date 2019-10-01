#include "t_vector.h"
#include "libft.h"

t_vec t_vector_add(t_vec a, t_vec b)
{
	a.x += b.x;
	a.y += b.y;
	a.z += b.z;
	return (a);
}

t_vec *t_vec_normalize(t_vec *v)
{
	double len;

	len = ft_sqrt((v->x) * (v->x) + (v->y) * (v->y) + (v->z) * (v->z));
	v->x /= len;
	v->y /= len;
	v->z /= len;
	return (v);
}

double t_vector_dot(t_vec a, t_vec b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec t_vector_mul(t_vec a, t_vec b)
{
	t_vec r;

	r.x = a.y * b.z - a.z * b.y;
	r.x = a.z * b.x - a.x * b.z;
	r.x = a.x * b.y - a.y * b.x;
	return (r);
}

