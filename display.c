#include "cub3d.h"

void	display_it(t_dis *display, char c, int x, int y)
{
	if (c == '0')
		mlx_put_image_to_window(display->mlx, display->win_ptr,
			display->img.floor,
			x * display->img.img_x, y * display->img.img_y);
	else if (c == '1')
		mlx_put_image_to_window(display->mlx, display->win_ptr,
			display->img.wall,
			x * display->img.img_x, y * display->img.img_y);
	else if (c == 'P')
	{
		mlx_put_image_to_window(display->mlx, display->win_ptr,
			display->img.floor,
			x * display->img.img_x, y * display->img.img_y);
		mlx_put_image_to_window(display->mlx, display->win_ptr,
			display->mpc.player,
			x * 4 * display->mpc.x, y * 4 * display->mpc.y);
	}
}

int	render_map(t_dis *display)
{
	int	r;
	int	c;

	r = 0;
	c = 0;
	if (!display->map[0])
		return (ft_end(display));
	while (display->map[r])
	{
		while (display->map[r][c])
		{
			display_it(display, display->map[r][c], c, r);
			c++;
		}
		c = 0;
		r++;
	}
	return (1);
}

void	create_img(t_dis *display)
{
	display->img.img_x = 64;
	display->img.img_y = 64;
	display->img.floor = mlx_xpm_file_to_image(display->mlx, "./texture/floor.xpm",
		(&display->img.img_x), (&display->img.img_y));
	display->img.wall = mlx_xpm_file_to_image(display->mlx, "./texture/wall.xpm",
		(&display->img.img_x), (&display->img.img_y));
	
	display->mpc.x = 16;
	display->mpc.y = 16;
	display->mpc.player = mlx_xpm_file_to_image(display->mlx, "./texture/mpc.xpm",
		(&display->mpc.x), (&display->mpc.y));
}