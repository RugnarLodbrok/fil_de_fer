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

#include "ft_linalg.h"

typedef struct
{
	t_vec v;
	int color;
} t_vertex;

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

void line(t_scene *s, t_vec p1, t_vec p2, int color);
void t_wireframe_init(t_wireframe *f);
void t_wireframe_draw(t_wireframe *f, t_scene *s, int color);

#endif
