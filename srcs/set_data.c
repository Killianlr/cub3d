/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 12:41:11 by kle-rest          #+#    #+#             */
/*   Updated: 2024/03/04 12:42:21 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	set_texture_image(t_pars *p)
{
	t_img	*ea;
	t_img	*so;
	t_img	*no;
	t_img	*we;

	ea = malloc(sizeof(t_img));
	if (!ea)
		return (1);
	p->ea = ea;
	so = malloc(sizeof(t_img));
	if (!so)
		return (2);
	p->so = so;
	no = malloc(sizeof(t_img));
	if (!no)
		return (3);
	p->no = no;
	we = malloc(sizeof(t_img));
	if (!we)
		return (4);
	p->we = we;
	return (0);
}

int	mem_set_next(t_g *game)
{
	int	i;

	if (!game->player)
	{
		free(game->mlx);
		free(game->p);
		free(game);
		return (1);
	}
	i = set_texture_image(game->p);
	if (i)
	{
		free_img(i, game->p);
		free(game->mlx);
		free(game->p);
		free(game->player);
		free(game);
		return (1);
	}
	set_mlx(game->mlx);
	init_var_struct(game);
	return (0);
}

int	mem_set(t_g *game)
{
	if (!game)
		return (1);
	game->mlx = malloc(sizeof(t_mlx));
	if (!game->mlx)
	{
		free(game);
		return (1);
	}
	game->p = malloc(sizeof(t_pars));
	if (!game->p)
	{
		free(game->mlx);
		free(game);
		return (1);
	}
	game->player = malloc(sizeof(t_p));
	if (mem_set_next(game))
		return (1);
	return (0);
}

void	set_texture(t_pars *p)
{
	p->no->addr = mlx_get_data_addr(p->no->img,
			&p->no->bits_per_pixel, &p->no->line_length, &p->no->endian);
	p->so->addr = mlx_get_data_addr(p->so->img,
			&p->so->bits_per_pixel, &p->so->line_length, &p->so->endian);
	p->we->addr = mlx_get_data_addr(p->we->img,
			&p->we->bits_per_pixel, &p->we->line_length, &p->we->endian);
	p->ea->addr = mlx_get_data_addr(p->ea->img,
			&p->ea->bits_per_pixel, &p->ea->line_length, &p->ea->endian);
}
