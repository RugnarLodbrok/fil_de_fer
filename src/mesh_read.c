#include <fcntl.h>
#include "libft.h"
#include "get_next_line.h"
#include "fdf.h"
#include <stdio.h>

static void error_exit(char *msg)
{
	if (!msg)
		msg = "error";
	ft_putendl(msg);
	exit(1);
}

t_point read_landscape_data(int buff[128][128], char *f_name)
{
	t_point r;
	int status;
	char *line;
	int fd;
	char **split_values;

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
	return (r);
}


t_mesh t_mesh_landscape_from_file(char *f_name)
{
	int d[128][128];
	t_point size;
	int j;
	int i;
	t_mesh m;

	t_mesh_init(&m);
	size = read_landscape_data(d, f_name);
	for (j = 0; j < size.y; ++j)
		for (i = 0; i < size.x; ++i)
		{
			d[i][j] = t_mesh_push_vertex(&m, (t_vertex){(t_vec){i * 10, j * 10, d[i][j]}, 255 * GREEN}) - 1;
			if (i > 0)
				t_mesh_push_edge(&m, (t_point){d[i - 1][j], d[i][j]});
			if (j > 0)
				t_mesh_push_edge(&m, (t_point){d[i][j - 1], d[i][j]});
		}
/*	for (j = 0; j < size.y; ++j)
	{
		for (i = 0; i < size.x; ++i)
		{
			printf("%d\t", d[i][j]);
		}
		printf("\n");
	}*/
	return (m);
}
