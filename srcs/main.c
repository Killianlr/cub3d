/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fserpe <fserpe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 17:27:28 by kle-rest          #+#    #+#             */
/*   Updated: 2024/02/07 15:07:00 by fserpe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int main(void)
{
	t_g		game;
	t_mlx	mlx;

	game.map = get_map();
	game.player = (t_p *)malloc(sizeof(t_p));
	set_mlx(&mlx);
	game.mlx = mlx;
    find_player_pos(game.player, game.map);
    // mlx_loop_hook(mlx.mlx_ptr, &handle_no_event, &game.player);
    // mlx_hook(mlx.win_ptr, ClientMessage, NoEventMask, ft_end, game.player);
    mlx_key_hook(mlx.win_ptr, &ft_input, &game);
    render_3d(&game, &game.mlx);
    mlx_loop(mlx.mlx_ptr);
    return (0);
}