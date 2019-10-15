#ifndef FDF_H
# define FDF_H

# define BLUE 1
# define GREEN 256
# define RED 256*256
# define WHITE (255*RED + 255*GREEN + 255*BLUE)

# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_DOWN 125
# define KEY_UP 126
# define STEP 0.05

#include "ft_linalg.h"
//#include "ascii.h"
#include "fdf_mlx.h"


typedef struct
{
	t_vec v;
	int color;
} t_vertex;

typedef struct
{
	t_vertex *vertices;
	int n_vertices;
	t_point *edges;
	int n_edges;
	t_mat m;
} t_mesh;

typedef struct
{
	size_t n_vertices;
	t_vertex *vertices;
	size_t n_edges;
	t_point *edges;
	t_mat m;
} t_wireframe;

typedef struct
{
	void *M;
	void *win;
	void **objs;
	t_vec momentum;
} t_scene;

t_mesh t_mesh_cube(int size);
void t_mesh_draw(t_mesh *m, void *p, int color);

#endif
