#include "fdf.h"
#include "mlx.h"

void t_app_init(t_app *app)
{
	ft_bzero(app, sizeof(t_app));

	app->M = mlx_init();
	app->win = mlx_new_window(app->M, WIN_W, WIN_H, "fdf");
	mlx_string_put(app->M, app->win, 150, 150, 255 * GREEN, "wake up, Neo!");
	app->momentum = (t_vec){.1, 1, .3};
	t_vec_normalize(&(app->momentum));
	app->momentum = t_vec_mul(app->momentum, 0.2);
	app->framebuffer = mlx_new_image(app->M, WIN_W, WIN_H);
/*	app->objs = malloc(sizeof(t_mesh *) * 2);
	app->objs[0] = malloc(sizeof(t_mesh *));
	app->objs[1] = 0;
	*(app->objs[0]) = t_mesh_landscape_from_file("test.txt");
//	*(app->objs[0]) = t_mesh_cube(50);
 */
	t_cam_init(&app->cam,
			   projection_isometric((double)WIN_W / 2, (double)WIN_H / 2),
			   (t_point){WIN_W, WIN_H});
}
