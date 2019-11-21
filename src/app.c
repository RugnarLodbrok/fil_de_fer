#include "fdf.h"
#include "mlx.h"

void t_framebuffer_init(t_framebuffer *fb, void *mlx, int w, int h)
{
	fb->image = mlx_new_image(mlx, WIN_W, WIN_H);
	fb->data = (uint *)mlx_get_data_addr(
			fb->image,
			&fb->bpp,
			&fb->row_len,
			&fb->endian);
	fb->bpp /= 8;
	fb->row_len /= fb->bpp;
	fb->w = w;
	fb->h = h;
}

void t_framebuffer_clear(t_framebuffer *fb)
{
	(void)fb;
	ft_bzero(fb->data, fb->row_len * WIN_H * sizeof(int));
}

void t_framebuffer_upscale(t_framebuffer *fb, int scale)
{
	int i;
	int j;

	i = fb->w;
	while(--i >= 0)
	{
		j = fb->h;
		while(--j >= 0)
		{
			fb->data[fb->row_len*j + i] = fb->data[fb->row_len*(j/scale) + i/scale];
		}
	}
}

void t_app_init(t_app *app)
{
	const double tg = ft_sin(radians(FOV / 2)) / ft_cos(radians(FOV / 2));
	const double near = 10.;
	ft_bzero(app, sizeof(t_app));
	app->w = WIN_W;
	app->h = WIN_H;
	app->M = mlx_init();
	app->win = mlx_new_window(app->M, WIN_W, WIN_H, "fdf");
	mlx_string_put(app->M, app->win, 150, 150, 255 * GREEN, "wake up, Neo!");
	t_vec_normalize(&(app->momentum));
	t_framebuffer_init(&app->framebuffer, app->M, app->w, app->h);
	app->objs = malloc(sizeof(t_mesh *) * 2);
	app->objs[0] = malloc(sizeof(t_mesh));
	app->objs[1] = 0;
	*(app->objs[0]) = t_mesh_landscape_from_file("maps/mars.fdf");
//	*(app->objs[0]) = t_mesh_landscape_from_file("test.txt");
//	*(app->objs[0]) = t_mesh_cube(50);

	t_cam_init(&app->cam,
//			   projection_isometric((double)WIN_W/10, (double)WIN_H/10),
			   projection_perspective(near, tg * near,
									  tg * near * WIN_H / WIN_W, 9999.),
			   (t_point){WIN_W, WIN_H});
}
