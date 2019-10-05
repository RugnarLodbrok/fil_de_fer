#ifndef FDF_H
# define FDF_H

# define BLUE 1
# define GREEN 256
# define RED 256*256
# define WHITE (255*RED + 255*GREEN + 255*BLUE)

#include "ft_linalg.h"

void line(void *M, void *win, t_vec p1, t_vec p2, int color);

#endif
