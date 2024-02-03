
#include "cub3d.h"

int main(void)
{
    t_dis   display;

    display.win_x = 900;
    display.win_y = 675;
    display.mlx = mlx_init();
    display.win_ptr = mlx_new_window(display.mlx, display.win_x, display.win_y, "cub3d");
    mlx_loop(display.mlx);
    return (0);
}