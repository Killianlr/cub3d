/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:08:13 by kle-rest          #+#    #+#             */
/*   Updated: 2024/03/01 14:04:17 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

float	get_angle(char c)
{
	if (c == 'E')
		return (EAST);
	else if (c == 'S')
		return (SOUTH);
	else if (c == 'W')
		return (WEST);
	else if (c == 'N')
		return (NORTH);
	return (0);
}

void    find_player_pos(t_p *player, char **map)
{ 
    int i;
    
    player->fdpx = 0;
    i = 0;
    while (map[player->fdpx])
    {
        player->fdpy = 0;
        while (!i && map[player->fdpx][player->fdpy])
        {
            if (map[player->fdpx][player->fdpy] != '1' 
				&& map[player->fdpx][player->fdpy] != '0' 
					&& map[player->fdpx][player->fdpy] != ' ')
			{
                i = 1;
				player->angle = get_angle(map[player->fdpx][player->fdpy]);
			}
            player->fdpy++;
        }
        if (i)
            break;
        player->fdpx++;
    }
    player->posx = player->fdpx + 0.5;
    player->posy = player->fdpy + 0.5;
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	set_mlx(t_mlx *mlx)
{
	mlx->mlx_ptr = mlx_init();
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, RESX, RESY, "cub3d");
}

char	*ft_strndup(char *src, int size)
{
	int		i;
	char	*dest;

	i = 0;
	dest = malloc(sizeof(char) * size + 1);
	if (!dest)
		return (NULL);
	while (src[i] && i < size)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}