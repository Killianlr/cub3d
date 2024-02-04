#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <math.h>
# include "../minilibx-linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>

typedef struct s_image
{
	void	*wall;
	void	*floor;
	int		img_x;
	int		img_y;
}			t_img;

typedef struct s_mpc
{
	float	pos_x;
	float	pos_y;
	void	*texture;
	int		tex_x;
	int		tex_y;
}			t_mpc;

typedef struct s_display
{
	void	*mlx;
	void	*win_ptr;
	int		win_x;
	int		win_y;
	char	**map;
	t_img	img;
	t_mpc	mpc;
}			t_dis;

int 	main(void);
int		ft_end(t_dis *display);
int		ft_input(int keysym, t_dis *dispaly);
int		handle_no_event(void *data);
char	**get_map(void);
void	create_img(t_dis *display);
int		render_map(t_dis *display);



#endif