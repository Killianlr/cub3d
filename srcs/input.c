/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fserpe <fserpe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 17:27:22 by kle-rest          #+#    #+#             */
/*   Updated: 2024/02/04 18:59:20 by fserpe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	print_map(char **map)
{
	int	r;

	r = 0;
	while (map[r])
	{
		printf("%s\n", map[r]);
		r++;
	}
}

int	handle_no_event(void *data)
{
	(void) data;
	return (0);
}

int	floor_or_wall(t_dis *display, float x, float y)
{
	int	r;
	int	c;

	printf("x = %f & y = %f\n", x, y);
	r = (int) y;
	c = (int) x;
	printf("	r = %d & c = %d ==> %c\n", r, c, display->map[r][c]);
	if (display->map[r][c] == '0' || display->map[r][c] == 'P')
		return (0);
	else if (display->map[r][c] == '1')
	{
		// printf("WALLWALLWALLWALLWALL\n");
		return (1);	
	}
	return (-1);
}

void	mpc_go_up(t_dis *display)
{
	if (floor_or_wall(display, display->mpc.pos_x, display->mpc.pos_y - 0.1) == 1)
		return ;
	else
		display->mpc.pos_y -= 0.1;
	render_map(display);
}

void	mpc_go_left(t_dis *display)
{
	if (floor_or_wall(display, display->mpc.pos_x - 0.1, display->mpc.pos_y) == 1)
		return ;
	else
		display->mpc.pos_x -= 0.1;
	render_map(display);
}

void	mpc_go_down(t_dis *display)
{
	if (floor_or_wall(display, display->mpc.pos_x, display->mpc.pos_y + 0.35) == 1)
		return ;
	else
		display->mpc.pos_y += 0.1;
	render_map(display);
}

void	mpc_go_right(t_dis *display)
{
	if (floor_or_wall(display, display->mpc.pos_x + 0.35, display->mpc.pos_y) == 1)
		return ;
	else
		display->mpc.pos_x += 0.1;
	render_map(display);
}

int	ft_input(int keysym, t_dis *display)
{
	// print_map(display->map);
	// printf("pos_x = %f & pos_y = %f\n", display->mpc.pos_x, display->mpc.pos_y);
	if (keysym == XK_Escape)
		ft_end(display);
	if (keysym == XK_w)
		mpc_go_up(display);
	if (keysym == XK_a)
		mpc_go_left(display);
	if (keysym == XK_s)
		mpc_go_down(display);
	if (keysym == XK_d)
		mpc_go_right(display);
	return (0);
}