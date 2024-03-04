/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fserpe <fserpe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:08:13 by kle-rest          #+#    #+#             */
/*   Updated: 2024/03/04 13:01:21 by fserpe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

float	get_angle(char c)
{
	if (c == 'W')
		return (M_PI / 2);
	else if (c == 'S')
		return (0);
	else if (c == 'E')
		return (3 * M_PI / 2);
	else if (c == 'N')
		return (M_PI);
	return (0);
}

void	find_player_pos(t_p *player, char **map)
{
	int	i;
	int	x;
	int	y;

	x = 0;
	i = 0;
	while (i == 0 && map[x])
	{
		y = 0;
		while (map[x][y])
		{
			if (map[x][y] != '1' && map[x][y] != '0' && map[x][y] != ' ')
			{
				i = 1;
				player->angle = get_angle(map[x][y]);
				break ;
			}
			y++;
		}
		if (i == 0)
			x++;
	}
	player->posx = x + 0.5;
	player->posy = y + 0.5;
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

char	**remove_backn(char **map)
{
	int	i;
	int	len;

	i = 0;
	while (map[i])
	{
		len = ft_strlen(map[i]);
		if (map[i][len - 1] == '\n')
			map[i][len - 1] = '\0';
		i++;
	}
	return (map);
}
