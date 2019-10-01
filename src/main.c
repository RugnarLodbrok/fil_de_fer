#include "libft.h"
#include "mlx.h"
//#include "mlx_int.h"
//#include "mlx_new_window.h"

int loop_hook(void *param);
int mouse_hook(int button, int x, int y, void *param);

int main(void)
{
	void *M;
	void *win;

	ft_printf("HELLO\n");
	M = mlx_init();
	win = mlx_new_window(M, 800, 600, "fdf");
	mlx_pixel_put(M, win, 100, 100, 255 * GREEN);
	mlx_string_put(M, win, 150, 150, 255 * GREEN, "HELLO MLX!");


	line(M, win, (t_point){50, 50}, (t_point){200, 100});
	line(M, win, (t_point){50, 50}, (t_point){200, 0});
	line(M, win, (t_point){50, 50}, (t_point){100, 200});
	line(M, win, (t_point){50, 50}, (t_point){0, 200});

	line(M, win, (t_point){50, 50}, (t_point){40, 30});
	line(M, win, (t_point){50, 50}, (t_point){60, 30});
	line(M, win, (t_point){50, 50}, (t_point){30, 40});
	line(M, win, (t_point){50, 50}, (t_point){30, 60});

	//	mlx_loop_hook(M, loop_hook, 0);
//	mlx_mouse_hook(win, mouse_hook, 0);
	mlx_loop(M);
}

int loop_hook(void *param)
{
	(void)param;
	ft_putendl("loop");
	return (-1);
}

int mouse_hook(int button, int x, int y, void *param)
{
	(void)param;
	(void)button;
	ft_printf("mouse: %d %d\n", x, y);
	return (0);
}
