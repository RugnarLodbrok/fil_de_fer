/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpoetess <rpoetess@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:54:05 by rpoetess          #+#    #+#             */
/*   Updated: 2019/11/21 20:55:17 by rpoetess         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_linalg.h"
#include "fdf.h"

int			ft_sign(int a)
{
	int b;
	int c;

	b = a > 0;
	c = a < 0;
	return (b - c);
}

static uint	blend(uint c1, uint c2, uint a)
{
	uint rb;
	uint g;

	rb = (c1 & 0xFF00FF) + ((a * (c2 & 0xFF00FF)) >> 8);
	g = (c1 & 0x00FF00) + ((a * (c2 & 0x00FF00)) >> 8);
	return (rb & 0xFF00FF) + (g & 0x00FF00);
}

uint		blend_alpha(uint c1, uint c2, uint a)
{
	uint c;
	uint res;

	c1 &= 0xFFFFFF;
	c2 &= 0xFFFFFF;
	res = 0;
	c = (c1 & 0x0000FF) * (255 - a) + (c2 & 0x0000FF) * a;
	c /= 255;
	res += c;
	c = ((c1 & 0x00FF00) >> 8) * (255 - a) + ((c2 & 0x00FF00) >> 8) * a;
	c /= 255;
	res += c << 8;
	c = ((c1 & 0xFF0000) >> 16) * (255 - a) + ((c2 & 0xFF0000) >> 16) * a;
	c /= 255;
	res += c << 16;
	return (res);
}

static void	put_pixel(t_app *app, int x, int y, uint color)
{
	unsigned char	a;
	uint			*d;

	if (x < 0 || y < 0 || x >= app->w || y >= app->h)
		return ;
	a = color >> 24;
	d = &app->framebuffer.data[y * app->framebuffer.row_len + x];
	*d = blend_alpha(*d, color, a);
}

static void	t_vec_swap(t_vec *v1, t_vec *v2)
{
	t_vec tmp;

	tmp = *v1;
	*v1 = *v2;
	*v2 = tmp;
}

void		line_(t_app *app, t_vec p1, t_vec p2, uint color)
{
	int		d;
	double	err;
	double	slope;

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

void		put_wu_pixel(t_app *app, t_wu_pixel p, double alpha, uint color)
{
	int		int_y;
	double	z1;
	double	z2;
	int		i1;
	int		i2;

	int_y = (int)p.y;
	z2 = (p.y - int_y);
	z1 = 1. - z2;
	i1 = (int)(255. * z1 * alpha + .5);
	i2 = (int)(255. * z2 * alpha + .5);
	if (p.flip)
	{
		put_pixel(app, int_y, p.x, color + i1 * ALPHA);
		put_pixel(app, int_y + 1, p.x, color + i2 * ALPHA);
	}
	else
	{
		put_pixel(app, p.x, int_y, color + i1 * ALPHA);
		put_pixel(app, p.x, int_y + 1, color + i2 * ALPHA);
	}
}

void		line(t_app *app, t_vec p1, t_vec p2, uint color)
{
	double		slope;
	t_wu_pixel	p;

	if ((p1.x < 0 || p1.y < 0 || p1.x >= app->w || p1.y >= app->h) &&
		(p2.x < 0 || p2.y < 0 || p2.x >= app->w || p2.y >= app->h))
		return ;
	if ((p.flip = ft_fabs(p2.y - p1.y) > ft_fabs(p2.x - p1.x)))
	{
		ft_swap_double(&p1.x, &p1.y);
		ft_swap_double(&p2.x, &p2.y);
	}
	if (p1.x > p2.x)
		t_vec_swap(&p1, &p2);
	slope = (p2.y - p1.y) / (p2.x - p1.x);
	p.x = (int)(p1.x + 2.5) - 2;
	p.y = p1.y - (p1.x - p.x) * slope;
	put_wu_pixel(app, p, ft_fpow(.5 - p1.x + p.x, 1), color);
	p.x++;
	p.y += slope;
	while (p.x < p2.x - .5)
	{
		put_wu_pixel(app, p, 1, color);
		p.x++;
		p.y += slope;
	}
	put_wu_pixel(app, p, ft_fpow(0.5 - p.x + p2.x, 1), color);
}
