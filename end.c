#include "cub3d.h"

int	ft_end(t_dis *display)
{
	mlx_destroy_window(display->mlx, display->win_ptr);
	mlx_destroy_display(display->mlx);
	free(display->mlx);
	exit(0);
	return (0);
}