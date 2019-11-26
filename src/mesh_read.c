/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoetess <rpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:59:25 by rpoetess          #+#    #+#             */
/*   Updated: 2019/11/21 21:00:38 by rpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "libft.h"
#include "ft_linalg.h"
#include "get_next_line.h"
#include "fdf.h"

t_array read_2d_int_array(int fd)
{
	char *line;
	t_array rows;
	t_arrayi row;
	char **split_values;
	int i;
	int j;

	t_array_init(&rows, sizeof(t_arrayi));
	while ((i = get_next_line(fd, &line)) > 0)
	{
		split_values = ft_strsplit(line, ' ');
		t_arrayi_init(&row);
		i = -1;
		while (split_values[++i])
		{
			j = ft_atoi(split_values[i]);
			t_arrayi_push(&row, j);
		}
		ft_strsplit_clear(split_values);
		free(line);
		t_array_push(&rows, &row);
	}
	if (i < 0)
		ft_error_exit("can't read file");
	return rows;
}

t_point read_landscape_data(int **data, const char *f_name)
{
	t_point shape;
	t_array rows;
	t_arrayi row;
	int fd;
	int i;

	if ((fd = open(f_name, O_RDONLY)) <= 0)
		ft_error_exit("can't open file `%s`", f_name);
	rows = read_2d_int_array(fd);
	shape.x = -1;
	shape.y = rows.count;
	i = -1;
	while (++i < (int)rows.count)
		if (shape.x < (int)(((t_arrayi *)rows.data)[i].count))
			shape.x = ((t_arrayi *)rows.data)[i].count;
	*data = ft_memalloc(sizeof(int) * shape.x * shape.y);
	i = -1;
	while (++i < (int)rows.count)
	{
		row = ((t_arrayi *)rows.data)[i];
		ft_memcpy(*data + shape.y * i, row.data, sizeof(int) * row.count);
		t_arrayi_del(&row);
	}
	t_array_del(&rows);
	return shape;
}

static void center_mesh(t_mesh *m, t_vec size)
{
	int i;

	i = -1;
	while (++i < (*m).n_vertices)
	{
		m->vertices[i].v.x /= size.x - 1;
		m->vertices[i].v.y /= size.y - 1;
		m->vertices[i].v = t_vec_sub(m->vertices[i].v, (t_vec){.5, .5, 0});
		m->vertices[i].v.y *= size.y - 1;
		m->vertices[i].v.y /= size.x - 1;
		m->vertices[i].v.x *= 500;
		m->vertices[i].v.y *= 500;
		m->vertices[i].v.z *= 10;
	}
}

t_mesh t_mesh_landscape_from_file(const char *f_name)
{
	int *data;
	int i;
	int j;
	t_mesh m;
	t_point shape;

	j = -1;
	t_mesh_init(&m);
	shape = read_landscape_data(&data, f_name);
	while (++j < shape.y)
	{
		i = -1;
		while (++i < shape.x)
		{
			data[shape.y * i + j] = t_mesh_push_vertex(
					&m,
					(t_vertex){
							(t_vec){i, j, data[shape.y * i + j]},
							255 * GREEN}
			) - 1;
			if (i > 0)
				t_mesh_push_edge(&m, (t_point){data[shape.y * (i - 1) + j],
											   data[shape.y * i + j]});
			if (j > 0)
				t_mesh_push_edge(&m, (t_point){data[shape.y * i + j - 1],
											   data[shape.y * i + j]});
		}
	}
	center_mesh(&m, (t_vec){shape.x, shape.y, 10.});
	return (m);
}
