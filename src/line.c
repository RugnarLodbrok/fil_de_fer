#include "mlx.h"
#include "libft.h"
#include "fdf.h"

int ft_sign(int a)
{
	int b;
	int c;

	b = a > 0;
	c = a < 0;
	return (b - c);
}

void line(void *M, void *win, t_point p1, t_point p2)
{
	int d;
	double err;
	double slope;
	t_point *pp1;
	t_point *pp2;

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
		d = ft_sign(pp2->y - pp1->y);
		slope = ((double)(pp2->y - pp1->y)) / (pp2->x - pp1->x) * d;
		err = 0;
		while (pp1->x <= pp2->x)
		{
			mlx_pixel_put(M, win, pp1->x, pp1->y, WHITE);
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
		d = ft_sign(pp2->x - pp1->x);
		slope = ((double)(pp2->x - pp1->x)) / (pp2->y - pp1->y) * d;
		err = 0;
		while (pp1->y <= pp2->y)
		{
			mlx_pixel_put(M, win, pp1->x, pp1->y, WHITE);
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
