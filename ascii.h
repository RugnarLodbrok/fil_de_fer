#ifndef ASCII_H
# define ASCII_H

typedef struct
{
	int **data;
	int w;
	int h;
} t_screen_buff;

# define PIX_11 "\xe2\x96\x88"
# define PIX_10 "\xe2\x96\x80"
# define PIX_01 "\xe2\x96\x84"
# define PIX_00 " "

void ascii_draw_new(t_screen_buff *s, int w, int h);
void ascii_draw_flush(t_screen_buff *s);

#endif
