#include "ft_linalg.h"
#include "fdf.h"

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

static void t_vec_swap(t_vec *v1, t_vec *v2)
{
	t_vec tmp;

	tmp = *v1;
	*v1 = *v2;
	*v2 = tmp;
}

void line(t_app *app, t_vec p1, t_vec p2, int color)
{
	int d;
	double err;
	double slope;

	if ((p2.x - p1.x) + (p2.y - p1.y) < 0)
		t_vec_swap(&p1, &p2);
	if ((p2.y - p1.y) - (p2.x - p1.x) < 0)
	{
		d = ft_sign((int)(p2.y - p1.y));
		slope = ((double)(p2.y - p1.y)) / (p2.x - p1.x) * d;
		err = 0;
		while (p1.x <= p2.x)
		{
			put_pixel(app, (int)p1.x, (int)p1.y, color);
			err += slope;
			if (err > 0.5)
			{
				p1.y += d;
				err -= 1;
			}
			p1.x++;
		}
	}
	else
	{
		d = ft_sign((int)(p2.x - p1.x));
		slope = ((double)(p2.x - p1.x)) / (p2.y - p1.y) * d;
		err = 0;
		while (p1.y <= p2.y)
		{
			put_pixel(app, (int)p1.x, (int)p1.y, color);
			err += slope;
			if (err > 0.5)
			{
				p1.x += d;
				err -= 1;
			}
			p1.y++;
		}
	}
}
/*
void line_wu(t_app *app, t_vec p1, t_vec p2, int color)
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
	if ((p2.y - pp1->y) - (p2.x - p1.x) < 0)
	{

	}
	else
	{}
}*/