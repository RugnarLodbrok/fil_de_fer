#ifndef T_VECTOR_H
# define T_VECTOR_H

typedef struct
{
	double x;
	double y;
	double z;
} t_vec;

t_vec *t_vec_normalize(t_vec *v);

#endif
