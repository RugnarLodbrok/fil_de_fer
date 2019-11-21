/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoetess <rpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 21:05:41 by rpoetess          #+#    #+#             */
/*   Updated: 2019/11/21 21:11:04 by rpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_linalg.h"
#include "fdf.h"

void	t_mesh_cube1(t_mesh *m)
{
	t_mesh_push_edge(m, (t_point){0, 1});
	t_mesh_push_edge(m, (t_point){1, 2});
	t_mesh_push_edge(m, (t_point){2, 3});
	t_mesh_push_edge(m, (t_point){3, 0});
	t_mesh_push_edge(m, (t_point){4, 5});
	t_mesh_push_edge(m, (t_point){5, 6});
	t_mesh_push_edge(m, (t_point){6, 7});
	t_mesh_push_edge(m, (t_point){7, 4});
	t_mesh_push_edge(m, (t_point){0, 4});
	t_mesh_push_edge(m, (t_point){1, 5});
	t_mesh_push_edge(m, (t_point){2, 6});
	t_mesh_push_edge(m, (t_point){3, 7});
}

t_mesh	t_mesh_cube(int size)
{
	t_mesh	m;
	int		i;

	i = -1;
	t_mesh_init(&m);
	t_mesh_push_vertex(&m, (t_vertex){(t_vec){-1, -1, -1}, 255 * GREEN});
	t_mesh_push_vertex(&m, (t_vertex){(t_vec){1, -1, -1}, 255 * GREEN});
	t_mesh_push_vertex(&m, (t_vertex){(t_vec){1, 1, -1}, 255 * GREEN});
	t_mesh_push_vertex(&m, (t_vertex){(t_vec){-1, 1, -1}, 255 * GREEN});
	t_mesh_push_vertex(&m, (t_vertex){(t_vec){-1, -1, 1}, 255 * GREEN});
	t_mesh_push_vertex(&m, (t_vertex){(t_vec){1, -1, 1}, 255 * GREEN});
	t_mesh_push_vertex(&m, (t_vertex){(t_vec){1, 1, 1}, 255 * GREEN});
	t_mesh_push_vertex(&m, (t_vertex){(t_vec){-1, 1, 1}, 255 * GREEN});

	t_mesh_push_edge(&m, (t_point){0, 1});
	t_mesh_push_edge(&m, (t_point){1, 2});
	t_mesh_push_edge(&m, (t_point){2, 3});
	t_mesh_push_edge(&m, (t_point){3, 0});

	t_mesh_push_edge(&m, (t_point){4, 5});
	t_mesh_push_edge(&m, (t_point){5, 6});
	t_mesh_push_edge(&m, (t_point){6, 7});
	t_mesh_push_edge(&m, (t_point){7, 4});

	t_mesh_push_edge(&m, (t_point){0, 4});
	t_mesh_push_edge(&m, (t_point){1, 5});
	t_mesh_push_edge(&m, (t_point){2, 6});
	t_mesh_push_edge(&m, (t_point){3, 7});

	for (i = 0; i < m.n_vertices; ++i)
		t_vec_scale(&m.vertices[i].v, size);
	return (m);
}

void	t_mesh_init(t_mesh *m)
{
	ft_bzero(m, sizeof(t_mesh));
	t_array_init(&m->arr_veritces, sizeof(t_vertex));
	t_array_init(&m->arr_edges, sizeof(t_point));
	m->edges = m->arr_edges.data;
	m->vertices = m->arr_veritces.data;
	t_mat_reset(&m->m);
}

int		t_mesh_push_vertex(t_mesh *m, t_vertex v)
{
	t_array_push(&m->arr_veritces, &v);
	m->vertices = m->arr_veritces.data;
	m->n_vertices = m->arr_veritces.count;
	return (m->n_vertices);
}

int		t_mesh_push_edge(t_mesh *m, t_point e)
{
	t_array_push(&m->arr_edges, &e);
	m->edges = m->arr_edges.data;
	m->n_edges = m->arr_edges.count;
	return (m->n_edges);
}
