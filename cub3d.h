#ifndef CUB3D_H
# define CUB3D_H

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <math.h>
# include "minilibx-linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>

typedef struct s_display
{
	void	*mlx;
	void	*win_ptr;
	int		win_x;
	int		win_y;
	char	**map;
}			t_dis;

int main(void);

#endif