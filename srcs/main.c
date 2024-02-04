/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 17:27:28 by kle-rest          #+#    #+#             */
/*   Updated: 2024/02/04 17:31:12 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int main(void)
{
    t_dis   display;

	display.map = get_map();
    display.win_x = 640;
    display.win_y = 384;
    display.mlx = mlx_init();
	create_img(&display);
    display.win_ptr = mlx_new_window(display.mlx, display.win_x, display.win_y, "cub3d");
    mlx_loop_hook(display.mlx, &handle_no_event, &display);
    mlx_hook(display.win_ptr, ClientMessage, NoEventMask, ft_end, &display);
    mlx_key_hook(display.win_ptr, &ft_input, &display);
	render_map(&display);
    mlx_loop(display.mlx);
    return (0);
}