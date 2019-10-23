#include "libft.h"
#include "ft_linalg.h"
#include "fdf.h"
#include "mlx.h"

int ft_sign(int a)
{
	int b;
	int c;

	b = a > 0;
	c = a < 0;
	return (b - c);
}

static void put_pixel(t_app *app, int x, int y, int color)
{

	if (x < 0 || y < 0 || x >= app->w || y >= app->h)
		return;
	app->framebuffer.data[y * app->framebuffer.row_len + x] = color;
}

void line(t_app *app, t_vec p1, t_vec p2, int color)
{
	int d;
	double err;
	double slope;
	t_vec *pp1;
	t_vec *pp2;

	if ((p2.x - p1.x) + (p2.y - p1.y) >= 0)
	{
		pp1 = &p1;
		pp2 = &p2;
	}
	else
	{
		pp1 = &p2;
		pp2 = &p1;
	}
	if ((pp2->y - pp1->y) - (pp2->x - pp1->x) < 0)
	{
		d = ft_sign((int)(pp2->y - pp1->y));
		slope = ((double)(pp2->y - pp1->y)) / (pp2->x - pp1->x) * d;
		err = 0;
		while (pp1->x <= pp2->x)
		{
			put_pixel(app, (int)pp1->x, (int)pp1->y, color);
			err += slope;
			if (err > 0.5)
			{
				pp1->y += d;
				err -= 1;
			}
			pp1->x++;
		}
	}
	else
	{
		d = ft_sign((int)(pp2->x - pp1->x));
		slope = ((double)(pp2->x - pp1->x)) / (pp2->y - pp1->y) * d;
		err = 0;
		while (pp1->y <= pp2->y)
		{
			put_pixel(app, (int)pp1->x, (int)pp1->y, color);
			err += slope;
			if (err > 0.5)
			{
				pp1->x += d;
				err -= 1;
			}
			pp1->y++;
		}
	}
}
