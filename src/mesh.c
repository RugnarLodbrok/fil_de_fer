#include "libft.h"
#include "get_next_line.h"
#include "ft_linalg.h"
#include "fdf.h"

t_mesh t_mesh_cube(int size)
{
	t_mesh m;
	int i;

	t_mesh_init(&m);
	m.n_vertices = 8;
	m.vertices = malloc(sizeof(t_vertex) * 8);
	m.vertices[0] = (t_vertex){(t_vec){-1, -1, -1}, 255 * GREEN};
	m.vertices[1] = (t_vertex){(t_vec){1, -1, -1}, 255 * GREEN};
	m.vertices[2] = (t_vertex){(t_vec){1, 1, -1}, 255 * GREEN};
	m.vertices[3] = (t_vertex){(t_vec){-1, 1, -1}, 255 * GREEN};
	m.vertices[4] = (t_vertex){(t_vec){-1, -1, 1}, 255 * GREEN};
	m.vertices[5] = (t_vertex){(t_vec){1, -1, 1}, 255 * GREEN};
	m.vertices[6] = (t_vertex){(t_vec){1, 1, 1}, 255 * GREEN};
	m.vertices[7] = (t_vertex){(t_vec){-1, 1, 1}, 255 * GREEN};

	m.n_edges = 12;
	m.edges = malloc(sizeof(t_point) * 12);
	m.edges[0] = (t_point){0, 1};
	m.edges[1] = (t_point){1, 2};
	m.edges[2] = (t_point){2, 3};
	m.edges[3] = (t_point){3, 0};

	m.edges[4] = (t_point){4, 5};
	m.edges[5] = (t_point){5, 6};
	m.edges[6] = (t_point){6, 7};
	m.edges[7] = (t_point){7, 4};

	m.edges[8] = (t_point){0, 4};
	m.edges[9] = (t_point){1, 5};
	m.edges[10] = (t_point){2, 6};
	m.edges[11] = (t_point){3, 7};

	for (i = 0; i < m.n_vertices; ++i)
		t_vec_scale(&m.vertices[i].v, size);

	return (m);
}

void t_mesh_init(t_mesh *m)
{
	ft_bzero(m, sizeof(t_mesh));
	t_array_init(&m->arr_veritces, sizeof(t_vertex));
	t_array_init(&m->arr_edges, sizeof(t_point));
	m->edges = m->arr_edges.data;
	m->vertices = m->arr_veritces.data;
	t_mat_reset(&m->m);
}

int t_mesh_push_vertex(t_mesh *m, t_vertex v)
{
	t_array_push(&m->arr_veritces, &v);
	m->vertices = m->arr_veritces.data;
	m->n_vertices = m->arr_veritces.count;
	return (m->n_vertices);
}

int t_mesh_push_edge(t_mesh *m, t_point e)
{
	t_array_push(&m->arr_edges, &e);
	m->edges = m->arr_edges.data;
	m->n_edges = m->arr_edges.count;
	return (m->n_edges);
}
