/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 17:27:22 by kle-rest          #+#    #+#             */
/*   Updated: 2024/02/04 17:31:15 by kle-rest         ###   ########.fr       */
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

void	mpc_go_up(t_dis *display)
{
	if (floor_or_wall(display, display->mpc.pos_x, display->mpc.pos_y - 8) == 1)
		return ;
	else
		display->mpc.pos_y -= 8;
	render_map(display);
}

void	mpc_go_left(t_dis *display)
{
	if (floor_or_wall(display, display->mpc.pos_x - 8, display->mpc.pos_y) == 1)
		return ;
	else
		display->mpc.pos_x -= 8;
	render_map(display);
}

void	mpc_go_down(t_dis *display)
{
	if (floor_or_wall(display, display->mpc.pos_x, display->mpc.pos_y + 24) == 1)
		return ;
	else
		display->mpc.pos_y += 8;
	render_map(display);
}

void	mpc_go_right(t_dis *display)
{
	if (floor_or_wall(display, display->mpc.pos_x + 24, display->mpc.pos_y) == 1)
		return ;
	else
		display->mpc.pos_x += 8;
	render_map(display);
}

int	ft_input(int keysym, t_dis *display)
{
	// bool key;

	// key = false;
	if (keysym == XK_Escape)
		ft_end(display);
	if (keysym == XK_z)
	{
		// printf("UP\n");
		mpc_go_up(display);
	}
	if (keysym == XK_q)
		mpc_go_left(display);
	if (keysym == XK_s)
		mpc_go_down(display);
	if (keysym == XK_d)
		mpc_go_right(display);
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