/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:31:13 by fserpe            #+#    #+#             */
/*   Updated: 2024/03/03 16:49:48 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	print_map(char **map)
{
	int	r;
	int	c;

	c = 0;
	r = 0;
	while (map[r])
	{
		while (map[r][c])
		{
			printf("%c", map[r][c]);
			c++;
		}
		printf("\n");
		c = 0;
		r++;
	}
}

int	collision(t_g *game, float x, float y)
{
	int	r;
	int	c;

	if (x < 0 || y < 0)
		return (0);
	c = (int)y;
	r = (int)x;
	if (game->p->map[r][c] == '1')
		return (0);
	else
		return (1);
}
