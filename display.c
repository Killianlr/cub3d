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
	}
}

int	display_mpc(t_dis *display)
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
			if (display->map[r][c] == 'P')
				mlx_put_image_to_window(display->mlx, display->win_ptr,
					display->mpc.texture,
					display->mpc.pos_x , display->mpc.pos_y);
			c++;
		}
		c = 0;
		r++;
	}
	return (1);
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
	display_mpc(display);
	return (1);
}

int	find_mpc_pos(t_dis *display)
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
			if (display->map[r][c] == 'P')
			{
				display->mpc.pos_x = (r * 4 * display->mpc.tex_x) + 24;
				display->mpc.pos_y = (c * 4 * display->mpc.tex_y) + 24;
			}
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
	
	display->mpc.tex_x = 16;
	display->mpc.tex_y = 16;
	display->mpc.texture = mlx_xpm_file_to_image(display->mlx, "./texture/mpc.xpm",
		(&display->mpc.tex_x), (&display->mpc.tex_y));
	find_mpc_pos(display);
}