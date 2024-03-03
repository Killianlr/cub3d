/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 16:33:43 by flavian           #+#    #+#             */
/*   Updated: 2024/03/03 16:59:14 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	mpc_go_up(t_g *game)
{
	if (collision(game, game->player->posx
			+ (cos(game->player->angle) / 20)
			, game->player->posy + (sin(game->player->angle) / 20)))
	{
		game->player->posx += cos(game->player->angle) / 20;
		game->player->posy += sin(game->player->angle) / 20;
	}
	render_3d(game, game->mlx);
}

void	mpc_go_down(t_g *game)
{
	if (collision(game, game->player->posx
			- (cos(game->player->angle) / 20)
			, game->player->posy - (sin(game->player->angle) / 20)))
	{
		game->player->posx -= cos(game->player->angle) / 20;
		game->player->posy -= sin(game->player->angle) / 20;
	}
	render_3d(game, game->mlx);
}

void	mpc_go_left(t_g *game)
{
	if (collision(game, game->player->posx
			+ (cos(game->player->angle + (M_PI / 2)) / 20)
			, game->player->posy
			+ (sin(game->player->angle + (M_PI / 2)) / 20)))
	{
		game->player->posx += cos(game->player->angle + (M_PI / 2)) / 20;
		game->player->posy += sin(game->player->angle + (M_PI / 2)) / 20;
	}
	render_3d(game, game->mlx);
}

void	mpc_go_right(t_g *game)
{
	if (collision(game, game->player->posx
			+ (cos(game->player->angle - (M_PI / 2)) / 20)
			, game->player->posy
			+ (sin(game->player->angle - (M_PI / 2)) / 20)))
	{
		game->player->posx += cos(game->player->angle - (M_PI / 2)) / 20;
		game->player->posy += sin(game->player->angle - (M_PI / 2)) / 20;
	}
	render_3d(game, game->mlx);
}

void	mpc_turn_left(t_g *game)
{
	game->player->angle += M_PI / 36;
	if (game->player->angle >= (2 * M_PI) - 0.1)
		game->player->angle = 0;
	render_3d(game, game->mlx);
}
