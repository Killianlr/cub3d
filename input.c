#include "cub3d.h"

int	handle_no_event(void *data)
{
	(void) data;
	return (0);
}

int	ft_input(int keysym, t_dis *display)
{
	if (keysym == XK_Escape)
		ft_end(display);
	// if (keysym == XK_w)
	// if (keysym == XK_a)
	// if (keysym == XK_s)
	// if (keysym == XK_d)
	return (0);
}