/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavian <flavian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 17:27:22 by kle-rest          #+#    #+#             */
/*   Updated: 2024/02/24 23:28:37 by flavian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"


int	handle_no_event(void *data)
{
	(void) data;
	return (0);
}

void	mpc_go_up(t_g *game)
{
	if (collision(game, game->player->posx + (cos(game->player->angle) / 10)
		, game->player->posy + (sin(game->player->angle) / 10)))
	{
		game->player->posx += cos(game->player->angle) / 10;
		game->player->posy += sin(game->player->angle) / 10;
	}
	// printf("player->posx= %f\n", game->player->posx);
	render_3d(game, &game->mlx);
}

void	mpc_go_down(t_g *game)
{
	if (collision(game, game->player->posx - (cos(game->player->angle) / 10)
		, game->player->posy - (sin(game->player->angle) / 10)))
	{
		game->player->posx -= cos(game->player->angle) / 10;
		game->player->posy -= sin(game->player->angle) / 10;
	}
	// printf("player->posx= %f\n", game->player->posx);
	render_3d(game, &game->mlx);
}

void	mpc_go_left(t_g *game)
{
	if (collision(game, game->player->posx + (cos(game->player->angle + (M_PI / 2)) / 10)
		, game->player->posy + (sin(game->player->angle + (M_PI / 2)) / 10)))
	{
		game->player->posx += cos(game->player->angle + (M_PI / 2)) / 10;
		game->player->posy += sin(game->player->angle + (M_PI / 2)) / 10;
	}
	// printf("player->posy= %f\n", game->player->posy);
	render_3d(game, &game->mlx);
}

void	mpc_go_right(t_g *game)
{
	if (collision(game, game->player->posx + (cos(game->player->angle - (M_PI / 2)) / 10)
		, game->player->posy + (sin(game->player->angle - (M_PI / 2)) / 10)))
	{
		game->player->posx += cos(game->player->angle - (M_PI / 2)) / 10;
		game->player->posy += sin(game->player->angle - (M_PI / 2)) / 10;
	}
	// printf("player->posy= %f\n", game->player->posy);
	render_3d(game, &game->mlx);
}

void	mpc_turn_left(t_g *game)
{
	
	game->player->angle += M_PI / 12;
	if (game->player->angle >= (2 * M_PI) - 0.1)
		game->player->angle = 0;
	// printf("player->angle = %f\n", game->player->angle);
	render_3d(game, &game->mlx);
}

void	mpc_turn_right(t_g *game)
{
	game->player->angle -= M_PI / 12;
	if (game->player->angle <= 0.1)
		game->player->angle = 2 * M_PI;
	// printf("player->angle = %f\n", game->player->angle);
	render_3d(game, &game->mlx);
}

int	key_action(void *data)
{
	t_g *game;
	game = (t_g *)data;

	printf("KEY_ACTION\n");
	if (game->ev->mv_forth == 1)
		mpc_go_up(game);
	if (game->ev->mv_left == 1)
		mpc_go_left(game);
	if (game->ev->mv_back == 1)
		mpc_go_down(game);
	if (game->ev->mv_right == 1)
		mpc_go_right(game);
	if (game->ev->rot_left == 1)
		mpc_turn_left(game);
	if (game->ev->mv_right == 1)
		mpc_turn_right(game);
	return (0);
}

int	key_released(int keysym, t_g *game)
{
	// printf("KEY_RELEASED\n");
	if (keysym == XK_w)
	{
		game->ev->mv_forth = 0;
		// printf("var_forth = %d\n", game->ev->mv_forth);
	}
	if (keysym == XK_a)
	{
		game->ev->mv_left = 0;
		// printf("var_left = %d\n", game->ev->mv_left);
	}
	if (keysym == XK_s)
	{
		game->ev->mv_back = 0;
		// printf("var_back = %d\n", game->ev->mv_back);
	}
	if (keysym == XK_d)
	{
		game->ev->mv_right = 0;
		// printf("var_right = %d\n", game->ev->mv_right);
	}
	if (keysym == 65363)
		game->ev->rot_right = 0;
	if (keysym == 65361)		
		game->ev->rot_left = 0;
	return (0);
}

int	key_pressed(int keysym, t_g *game)
{
	// printf("KEY_PRESSED\n");
	// 	printf("var_forth = %d\n", game->ev->mv_forth);
	// printf("var_back = %d\n", game->ev->mv_back);
	// printf("var_left = %d\n", game->ev->mv_left);
	// printf("var_right = %d\n", game->ev->mv_right);
	if (keysym == XK_Escape)
		ft_end(&game->mlx, game->player);
	if (keysym == XK_w)
	{
		game->ev->mv_forth = 1;
		// printf("var_forth = %d\n", game->ev->mv_forth);
	}
	if (keysym == XK_a)
	{
		game->ev->mv_left = 1;
		// printf("var_left = %d\n", game->ev->mv_left);
	}
	if (keysym == XK_s)
	{
		game->ev->mv_back = 1;
		// printf("var_back = %d\n", game->ev->mv_back);
	}
	if (keysym == XK_d)
	{
		game->ev->mv_right = 1;
		// printf("var_right = %d\n", game->ev->mv_right);
	}
	if (keysym == 65363)
		game->ev->rot_right = 1;
	if (keysym == 65361)		
		game->ev->rot_left = 1;
	return (0);
}

int	ft_input(int keysym, t_g *game)
{
	if (keysym == XK_Escape)
		ft_end(&game->mlx, game->player);
	if (keysym == XK_w)
		mpc_go_up(game);
	if (keysym == XK_a)
		mpc_go_left(game);
	if (keysym == XK_s)
		mpc_go_down(game);
	if (keysym == XK_d)
		mpc_go_right(game);
	if (keysym == 65363)
		mpc_turn_right(game);
	if (keysym == 65361)
		mpc_turn_left(game);
	return (0);
}

// int	ft_input(int keysym, t_dis *display)
// {
// 	if (keysym == XK_Escape)
// 		ft_end(display);
// 	if (keysym == XK_z)
// 	{
// 		display->mpc.pos_y -= 8;
// 		render_map(display);
// 	}
// 	if (keysym == XK_q)
// 	{
// 		display->mpc.pos_x -= 8;
// 		render_map(display);
// 	}
// 	if (keysym == XK_s)
// 	{
// 		display->mpc.pos_y += 8;
// 		render_map(display);
// 	}
// 	if (keysym == XK_d)
// 	{
// 		display->mpc.pos_x += 8;
// 		render_map(display);
// 	}
// 	return (0);
// }