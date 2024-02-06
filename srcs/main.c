/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 17:27:28 by kle-rest          #+#    #+#             */
/*   Updated: 2024/02/06 15:56:11 by kle-rest         ###   ########.fr       */
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

void    find_player_pos(t_p *player, char **map)
{
    int x;
    int y;
    int i;
    
    x = 0;
    i = 0;
    while (map[x])
    {
        y = 0;
        while (map[x][y])
        {
            if (map[x][y] != '1' && map[x][y] != '0')
			{
                i = 1;
				player->angle = get_angle(map[x][y]);
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

void	set_raycasting(t_ray *ray, t_p *player)
{
	ray->ratio = (pix - (RESX / 2) / (RESX / 2));
	ray->dirx = cos(player->angle) / 2 + cos(player->angle - (M_PI / 2)) * ray->ratio;
	ray->dirx = sin(player->angle) / 2 + sin(player->angle - (M_PI / 2)) * ray->ratio;
	ray->mapx = floor(player->posx);
	ray->mapy = floor(player->posy);
	ray->deltadistx = sqrt(1 + (pow(ray->diry, 2) / pow(ray->dirx, 2)));
	ray->deltadisty = sqrt(1 + (pow(ray->dirx, 2) / pow(ray->diry, 2)));
	check_dir

	/*---------FINIR DE METTRE AU PROPRE---------*/

	
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
}

void    render_3d(t_g *game)
{
	t_ray	ray;

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
		set_raycasting(&ray, game->player);
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

void	set_mlx(t_mlx *mlx)
{
	mlx->mlx_ptr = mlx_init();
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, RESX, RESY, "cub3d");
}

int main(void)
{
	t_g		game;
	t_mlx	mlx;

	game.map = get_map();
	game.player = (t_p *)malloc(sizeof(t_p));
	set_mlx(&mlx);
    find_player_pos(game.player, game.map);
    mlx_loop_hook(mlx.mlx_ptr, &handle_no_event, &game.player);
    mlx_hook(mlx.win_ptr, ClientMessage, NoEventMask, ft_end, game.player);
    mlx_key_hook(mlx.win_ptr, &ft_input, game.player);
    render_3d(&game);
    mlx_loop(mlx.mlx_ptr);
    return (0);
}