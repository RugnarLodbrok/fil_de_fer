#include "libft.h"
#include "fdf.h"
#include "ascii.h"

void line(void *p, t_vec p1, t_vec p2, int v)
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
		d = pp2->y > pp1->y ? 1 : -1;
		slope = ((double) (pp2->y - pp1->y)) / (pp2->x - pp1->x) * d;
		err = 0;
		while (pp1->x <= pp2->x)
		{
			ascii_draw_put_pixel(p, (int) (pp1->x), (int) (pp1->y), v);
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
		d = pp2->x > pp1->x ? 1 : -1;
		slope = ((double) (pp2->x - pp1->x)) / (pp2->y - pp1->y) * d;
		err = 0;
		while (pp1->y <= pp2->y)
		{
			ascii_draw_put_pixel(p, (int) (pp1->x), (int) (pp1->y), v);
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
