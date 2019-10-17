#ifndef FDF_H
# define FDF_H

# define WIN_W 800
# define WIN_H 600

# define BLUE 1
# define GREEN 256
# define RED 256*256
# define WHITE (255*RED + 255*GREEN + 255*BLUE)

# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_DOWN 125
# define KEY_UP 126
# define STEP 0.05

#include "libft.h"
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
	t_mat m;
	t_mat p;
} t_cam;

typedef struct
{
	void *M;
	void *win;
	void **objs;
	t_cam cam;
	t_vec momentum;
} t_app;

void	t_mesh_init(t_mesh *m);
t_mesh	t_mesh_cube(int size);
void	t_mesh_draw(t_mesh *m, void *p, int color);
t_mesh	t_mesh_landscape_from_file(char *f_name);
int		t_mesh_push_vertex(t_mesh *m, t_vertex v);
int		t_mesh_push_edge(t_mesh *m, t_point e);

#endif
