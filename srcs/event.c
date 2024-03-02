/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavian <flavian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 17:27:22 by kle-rest          #+#    #+#             */
/*   Updated: 2024/03/02 16:37:01 by flavian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"


int	handle_no_event(void *data)
{
	(void) data;
	return (0);
}

void	mpc_turn_right(t_g *game)
{
	game->player->angle -= M_PI / 36;
	if (game->player->angle <= 0.1)
		game->player->angle = 2 * M_PI;
	render_3d(game, game->mlx);
}

int	key_action(t_g *game)
{
	if (game->ev->mv_fwd == 1)
		mpc_go_up(game);
	if (game->ev->mv_left == 1)
		mpc_go_left(game);
	if (game->ev->mv_bckwd == 1)
		mpc_go_down(game);
	if (game->ev->mv_right == 1)
		mpc_go_right(game);
	if (game->ev->rot_right == 1)
		mpc_turn_right(game);
	if (game->ev->rot_left == 1)
		mpc_turn_left(game);
	return (0);
}

int	key_release(int keysym, t_g *game)
{
	if (keysym == XK_w)
		game->ev->mv_fwd = 0;
	if (keysym == XK_a)
		game->ev->mv_left = 0;
	if (keysym == XK_s)
		game->ev->mv_bckwd = 0;
	if (keysym == XK_d)
		game->ev->mv_right = 0;
	if (keysym == 65363)
		game->ev->rot_right = 0;
	if (keysym == 65361)
		game->ev->rot_left = 0;
	return (0);
}

int	key_pressed(int keysym, t_g *game)
{
	if (keysym == XK_Escape)
		ft_end_0(game);
	if (keysym == XK_w)
		game->ev->mv_fwd = 1;
	if (keysym == XK_a)
		game->ev->mv_left = 1;
	if (keysym == XK_s)
		game->ev->mv_bckwd = 1;
	if (keysym == XK_d)
		game->ev->mv_right = 1;
	if (keysym == 65363)
		game->ev->rot_right = 1;
	if (keysym == 65361)
		game->ev->rot_left = 1;
	return (0);
}