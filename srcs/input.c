/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 17:27:22 by kle-rest          #+#    #+#             */
/*   Updated: 2024/02/06 15:16:27 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"


int	handle_no_event(void *data)
{
	(void) data;
	return (0);
}

int	floor_or_wall(t_dis *display, int x, int y)
{
	int	r;
	int	c;

	r = x / 64;
	c = y / 64;
		printf("x = %d => r = %d\ny = %d => c = %d\n", x, r, y, c);
	if (display->map[r][c] == '0' || display->map[r][c] == 'P')
	{
		// printf("floor\n");
		return (0);
	}
	else if (display->map[r][c] == '1')
	{
		// printf("wall\n");
		return (1);	
	}
	return (-1);
}

void	mpc_go_up(t_dis *display, t_p *player)
{
	player->posx += 0.2;
	printf("player->posx= %f\n", player->posx);
	render_3d(display, player);
}

void	mpc_go_down(t_dis *display, t_p *player)
{
	player->posx -= 0.2;
	printf("player->posx= %f\n", player->posx);
	render_3d(display, player);
}

void	mpc_go_left(t_dis *display, t_p *player)
{
	player->posy -= 0.2;
	printf("player->posy= %f\n", player->posy);
	render_3d(display, player);
}

void	mpc_go_right(t_dis *display, t_p *player)
{
	player->posy += 0.2;
	printf("player->posy= %f\n", player->posy);
	render_3d(display, player);
}

void	mpc_turn_left(t_dis *display, t_p *player)
{
	player->angle += 0.2;
	printf("player->angle = %f\n", player->angle);
	render_3d(display, player);
}

void	mpc_turn_right(t_dis *display, t_p *player)
{
	player->angle -= 0.2;
	printf("player->angle = %f\n", player->angle);
	render_3d(display, player);
}

int	ft_input(int keysym, t_dis *display)
{
	if (keysym == XK_Escape)
		ft_end(display);
	if (keysym == XK_w)
		mpc_go_up(display, display->player);
	if (keysym == XK_a)
		mpc_go_left(display, display->player);
	if (keysym == XK_s)
		mpc_go_down(display, display->player);
	if (keysym == XK_d)
		mpc_go_right(display, display->player);
	if (keysym == 65363)
		mpc_turn_right(display, display->player);
	if (keysym == 65361)
		mpc_turn_left(display, display->player);
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