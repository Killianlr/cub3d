/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:31:13 by fserpe            #+#    #+#             */
/*   Updated: 2024/03/04 12:43:29 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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

int	ft_isws(int c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	error(char *msg)
{
	printf("Error\n");
	printf("%s\n", msg);
	return (1);
}
