
#include "cub3d.h"

char	**get_map(void)
{
	int	fd;
	char	**map;
	int	i;

	fd = open("map/map.cub", O_RDONLY);
	if (fd < 0)
		return (NULL);
	map = malloc(sizeof(char *) * 6);
	if (!map)
		return (NULL);
	i = 0;
	while (i < 6)
	{
		map[i] = get_next_line(fd, 0);
		printf("%s", map[i]);
		i++;
	}
	printf("\n");
	map[i] = NULL;
	return (map);
}

int main(void)
{
    t_dis   display;

	display.map = get_map();
    display.win_x = 900;
    display.win_y = 675;
    display.mlx = mlx_init();
    display.win_ptr = mlx_new_window(display.mlx, display.win_x, display.win_y, "cub3d");
    mlx_loop_hook(display.mlx, &handle_no_event, &display);
    mlx_hook(display.win_ptr, ClientMessage, NoEventMask, ft_end, &display);
    mlx_key_hook(display.win_ptr, &ft_input, &display);
    mlx_loop(display.mlx);
    return (0);
}