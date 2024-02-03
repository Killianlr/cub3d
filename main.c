
#include "cub3d.h"

int main(void)
{
    t_dis   display;

	display.map = get_map();
    display.win_x = 900;
    display.win_y = 675;
    display.mlx = mlx_init();
	create_img(&display);
    display.win_ptr = mlx_new_window(display.mlx, display.win_x, display.win_y, "cub3d");
    mlx_loop_hook(display.mlx, &handle_no_event, &display);
    mlx_hook(display.win_ptr, ClientMessage, NoEventMask, ft_end, &display);
    mlx_key_hook(display.win_ptr, &ft_input, &display);
	render_map(&display);
    mlx_loop(display.mlx);
    return (0);
}