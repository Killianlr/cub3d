/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 17:27:28 by kle-rest          #+#    #+#             */
/*   Updated: 2024/02/06 15:16:14 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

float	get_angle(char c)
{
	if (c == 'N')
		return (M_PI / 2);
	else if (c == 'E')
		return (0);
	else if (c == 'S')
		return (3 * M_PI / 2);
	else if (c == 'W')
		return (M_PI);
	return (0);
}

void    find_player_pos(t_p *player, t_dis *display)
{
    int x;
    int y;
    int i;
    
    x = 0;
    i = 0;
    while (display->map[x])
    {
        y = 0;
        while (display->map[x][y])
        {
            if (display->map[x][y] != '1' && display->map[x][y] != '0')
			{
                i = 1;
				player->angle = get_angle(display->map[x][y]);
			}
            if (i)
                break;
            y++;
        }
        if (i)
            break;
        x++;
    }
    player->posx = x + 0.5;
    player->posy = y + 0.5;
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	draw_line(t_dis *display, int pix, int y1, int y2)
{
	int	y;

	y = 0;
	// printf("y1 = %d y2 = %d\n", y1, y2);
	while (y <= RESY)
	{
		if (y < y1)
			mlx_pixel_put(display->mlx, display->win_ptr, pix, y, create_trgb(255, 0, 255, 255));
		else if (y > y2)
			mlx_pixel_put(display->mlx, display->win_ptr, pix, y, create_trgb(255, 192, 192, 192));
		else
			mlx_pixel_put(display->mlx, display->win_ptr, pix, y, create_trgb(255, 255, 255, 255));
		y++;
	}
}

void    render_3d(t_dis *display, t_p *player)
{
    double pix;
    double   ratio;
	float		dirx;
	float		diry;
	float		mapx;
	float		mapy;
	int		intmapx;
	int		intmapy;
	float	deltadistx;
	float	deltadisty;
	float		stepx;
	float		stepy;
	float	sidedistx;
	float	sidedisty;
	int		hit;
	int		side;
	float	perpualldist;

    pix = 0;
    while (pix <= RESX)
    {
		ratio = (pix - (RESX / 2)) / (RESX / 2);
		dirx = cos(player->angle) / 2 + cos(player->angle - (M_PI / 2)) * ratio;
		diry = sin(player->angle) / 2 + sin(player->angle - (M_PI / 2)) * ratio;
		mapx = floor(player->posx);
		mapy = floor(player->posy);
		deltadistx = sqrt(1 + (pow(diry, 2) / pow(dirx, 2)));
		deltadisty = sqrt(1 + (pow(dirx, 2) / pow(diry, 2)));
		if (dirx < 0)
		{
			stepx = -1;
			sidedistx = (player->posx - mapx) * deltadistx;
		}
		else
		{
			stepx = 1;
			sidedistx = (mapx + 1 - player->posx) * deltadistx;
		}
		if (diry < 0)
		{
			stepy = -1;
			sidedisty = (player->posy - mapy) * deltadisty;
		}
		else
		{
			stepy = 1;
			sidedisty = (mapy + 1 - player->posy) * deltadisty;
		}
		hit = 0;
		while (!hit)
		{
			if (!sidedisty || (sidedistx && sidedistx < sidedisty))
			{
				sidedistx += deltadistx;
				mapx += stepx;
				side = 0;
			}
			else
			{
				sidedisty += deltadisty;
				mapy += stepy;
				side = 1;
			}
			intmapx = floor(mapx);
			intmapy = floor(mapy);
			if (display->map[intmapx][intmapy] == '1')
			{
				hit = 1;
			}
		}
		if (side == 0)
			perpualldist = (mapx - player->posx + (1 - stepx) / 2) / dirx;
		else
			perpualldist = (mapy - player->posy + (1 - stepy) / 2) / diry;
		draw_line(display, pix, ((RESY / 2) - (RESY / 4) / perpualldist), ((RESY / 2) + (RESY / 4) / perpualldist));
		pix++;
    }
}

int main(void)
{
    t_dis   display;
    t_p     *player;

	player = (t_p *)malloc(sizeof(t_p));
	display.map = get_map();
    display.mlx = mlx_init();
    display.win_ptr = mlx_new_window(display.mlx, RESX, RESY, "cub3d");
    find_player_pos(player, &display);
	display.player = player;
    mlx_loop_hook(display.mlx, &handle_no_event, &display);
    mlx_hook(display.win_ptr, ClientMessage, NoEventMask, ft_end, &display);
    mlx_key_hook(display.win_ptr, &ft_input, &display);
	printf("player->posx %f\n", player->posx);
	printf("player->posy %f\n", player->posy);
    render_3d(&display, player);
    mlx_loop(display.mlx);
    return (0);
}