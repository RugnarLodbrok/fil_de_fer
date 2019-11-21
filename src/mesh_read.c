#include <fcntl.h>
#include "libft.h"
#include "ft_linalg.h"
#include "get_next_line.h"
#include "fdf.h"
#include <stdio.h>

static void	error_exit(char *msg)
{
	if (!msg)
		msg = "error";
	ft_putendl(msg);
	exit(1);
}

#define SIZE 1024

t_vec		read_landscape_data(int buff[SIZE][SIZE], const char *f_name)
{
	t_point	r;
	int		status;
	char	*line;
	int		fd;
	char	**split_values;

	ft_bzero(&r, sizeof(r));
	if ((fd = open(f_name, O_RDONLY)) <= 0)
		error_exit("can't open file");
	while ((status = get_next_line(fd, &line)) > 0)
	{
		split_values = ft_strsplit(line, ' ');
		for (r.x = 0; split_values[r.x]; r.x++)
		{
			buff[r.x][r.y] = ft_atoi(split_values[r.x]);
			free(split_values[r.x]);
		}
		free(split_values);
		free(line);
		r.y++;
	}
	if (status < 0)
		error_exit("can't read file");
	return (t_vec){r.x, r.y, 10};
}

t_mesh		t_mesh_landscape_from_file(const char *f_name)
{
	int		d[SIZE][SIZE];
	t_vec	size;
	int		j;
	int		i;
	t_mesh	m;

	t_mesh_init(&m);
	size = read_landscape_data(d, f_name);
	for (j = 0; j < size.y; ++j)
		for (i = 0; i < size.x; ++i)
		{
			d[i][j] = t_mesh_push_vertex(&m, (t_vertex){(t_vec){i, j, d[i][j]}, 255 * GREEN}) - 1;
			if (i > 0)
				t_mesh_push_edge(&m, (t_point){d[i - 1][j], d[i][j]});
			if (j > 0)
				t_mesh_push_edge(&m, (t_point){d[i][j - 1], d[i][j]});
		}
	for (i = 0; i < m.n_vertices; ++i)
	{
		m.vertices[i].v.x /= size.x - 1;
		m.vertices[i].v.y /= size.y - 1;
		m.vertices[i].v = t_vec_sub(m.vertices[i].v, (t_vec){.5, .5});
		m.vertices[i].v.y *= size.y - 1;
		m.vertices[i].v.y /= size.x - 1;
		m.vertices[i].v.x *= 500;
		m.vertices[i].v.y *= 500;
		m.vertices[i].v.z *= 10;
	}
	return (m);
}
