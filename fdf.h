#ifndef FDF_H
# define FDF_H

# define WIN_W 800
# define WIN_H 600

# define MLX_EVEN_KEY_PRESS 2
# define MLX_EVEN_KEY_RELEASE 3

# define BLUE 1
# define GREEN 256
# define RED 256*256
# define WHITE (255*RED + 255*GREEN + 255*BLUE)

# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_DOWN 125
# define KEY_UP 126
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_Q 12
# define KEY_E 14

# define FRAME_RATE 60
# define FRAME_TIME 1./FRAME_RATE

# define STEP 0.05

#include <time.h>
#include "libft.h"
#include "ft_linalg.h"
//#include "ascii.h"
#include "fdf_mlx.h"


typedef struct
{
	double d_yaw;
	double d_pitch;
	double d_roll;
	t_vec v;
} t_controller;

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
	t_mat v1;
	t_mat v2;
	t_mat proj;
	t_mat disp;
} t_cam;

typedef struct
{
	void *M;
	void *win;
	void *framebuffer;
	t_mesh **objs;
	time_t time;
	time_t frame_time;
	t_controller controller;
	t_cam cam;
	t_vec momentum;
} t_app;

void t_app_init(t_app *app);
void t_cam_init(t_cam *c, t_mat projection, t_point display_res);
void t_cam_draw(t_cam *cam, void *p, t_mesh *mesh);
void t_cam_move(t_cam *cam, t_controller *ctrl);
t_mat projection_isometric(double fov_width, double fov_height);
t_mesh t_mesh_cube(int size);
void t_mesh_init(t_mesh *m);
t_mesh t_mesh_landscape_from_file(char *f_name);
int t_mesh_push_vertex(t_mesh *m, t_vertex v);
int t_mesh_push_edge(t_mesh *m, t_point e);
void mlx_bind_keys(void *win, t_controller *c);

#endif
