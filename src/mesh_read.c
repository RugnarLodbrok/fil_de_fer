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

t_vec		read_landscape_data(int buff[SIZE][SIZE], const char *f_name)
{
	t_point	r;
	int		status;
	char	*line;
	int		fd;
	char	**split_values;

	ft_bzero(&r, sizeof(r));
	if ((fd = open(f_name, O_RDONLY)) <= 0)
		ft_error_exit("can't open file");
	while ((status = get_next_line(fd, &line)) > 0)
	{
		split_values = ft_strsplit(line, ' ');
		r.x = -1;
		while (split_values[++r.x])
		{
			buff[r.x][r.y] = ft_atoi(split_values[r.x]);
			free(split_values[r.x]);
		}
		free(split_values);
		free(line);
		r.y++;
	}
	if (status < 0)
		ft_error_exit("can't read file");
	return (t_vec){r.x, r.y, 10};
}

static void	center_mesh(t_mesh *m, t_vec size)
{
	int i;

	i = -1;
	while (++i < (*m).n_vertices)
	{
		m->vertices[i].v.x /= size.x - 1;
		m->vertices[i].v.y /= size.y - 1;
		m->vertices[i].v = t_vec_sub(m->vertices[i].v, (t_vec){.5, .5});
		m->vertices[i].v.y *= size.y - 1;
		m->vertices[i].v.y /= size.x - 1;
		m->vertices[i].v.x *= 500;
		m->vertices[i].v.y *= 500;
		m->vertices[i].v.z *= 10;
	}
}

t_mesh		t_mesh_landscape_from_file(const char *f_name)
{
	int		d[SIZE][SIZE];
	t_vec	size;
	int		j;
	int		i;
	t_mesh	m;

	j = -1;
	t_mesh_init(&m);
	size = read_landscape_data(d, f_name);
	while (++j < size.y)
	{
		i = -1;
		while (++i < size.x)
		{
			d[i][j] = t_mesh_push_vertex(&m,
			(t_vertex){(t_vec){i, j, d[i][j]}, 255 * GREEN}) - 1;
			if (i > 0)
				t_mesh_push_edge(&m, (t_point){d[i - 1][j], d[i][j]});
			if (j > 0)
				t_mesh_push_edge(&m, (t_point){d[i][j - 1], d[i][j]});
		}
	}
	center_mesh(&m, size);
	return (m);
}
