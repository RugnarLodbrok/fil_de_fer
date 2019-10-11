#include "libft.h"
#include "fdf.h"
#include <stdio.h>
#include "unistd_compat.h"
#include "ascii.h"

void update(double dt, t_screen_buff *s)
{
	static int x = 1;
	static int y = 1;
	ascii_draw_put_pixel(s, x, y, 0);
	x++;
	y++;
	if (x >= s->w || y >= s->h)
	{
		x = 0;
		y = 0;
	}
	ascii_draw_put_pixel(s, x, y, 1);
}

int main(void)
{
	t_screen_buff s;
	printf("\033[H\033[J");
	ascii_draw_new(&s, 100, 100);
	ascii_draw_flush(&s);
	while (1)
	{
		update(0, &s);
		usleep(40000);
	}
}

void chars_demo(void)
{
	printf("\033[H\033[J");
	printf("\033[%d;%dH", (10), (20));
//	char happy[] = { 0xe2, 0x98, 0xba }; U+263A
	printf("\xe2\x98\xba\n");
	printf("\xe2\x98\xbb\n");
	printf("\74\n");

	printf("\xe2\x96\x80");
	printf("\xe2\x96\x84");
	printf("\xe2\x96\x88\n");
}

/*

 e2 98 ba

 * */