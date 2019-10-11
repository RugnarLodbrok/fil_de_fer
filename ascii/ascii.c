#include <stdio.h>
#include "libft.h"
#include "ascii.h"

void ascii_draw_new(t_screen_buff *s, int w, int h)
{
	int i;
	s->w = w;
	s->h = h;
	s->data = malloc(sizeof(int *) * s->w);
	for (i = 0; i < s->w; ++i)
	{
		s->data[i] = malloc(sizeof(int) * s->h);
		ft_bzero(s->data[i], sizeof(int) * s->h);
	}
}

void ascii_draw_flush(t_screen_buff *s)
{
	int i;
	int j;
	int k;
	char buff[s->h * 3];

	printf("\033[%d;%dH", 0, 0);
	for (i = 0; i < s->w - 1; i += 2)
	{
		for (j = 0, k = 0; j < s->h; j++)
		{
			if (s->data[i][j])
			{
				if (s->data[i + 1][j])
					ft_memcpy(buff + k, PIX_11, 3);
				else
					ft_memcpy(buff + k, PIX_10, 3);
			}
			else
			{
				if (s->data[i + 1][j])
					ft_memcpy(buff + k, PIX_01, 3);
				else
				{
					ft_memcpy(buff + k, PIX_00, 1);
					k -= 2;
				}
			}
			k += 3;
		}
		buff[k + 1] = 0;
		printf("%s|\n", buff);
	}
}

void ascii_draw_put_pixel(t_screen_buff *s, int x, int y, int v)
{
	int i;
	const char *pix = "\033[%d;%dH%s\n";

	if (s->data[x][y] == v)
		return;
	s->data[x][y] = v;
	i = x / 2;
	if (s->data[2 * i][y])
	{
		if (s->data[2 * i + 1][y])
			printf(pix, i, y, PIX_11);
		else
			printf(pix, i, y, PIX_10);
	}
	else
	{
		if (s->data[2 * i + 1][y])
			printf(pix, i, y, PIX_01);
		else
			printf(pix, i, y, PIX_00);
	}
}
