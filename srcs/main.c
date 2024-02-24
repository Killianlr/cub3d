/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavian <flavian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 17:27:28 by kle-rest          #+#    #+#             */
/*   Updated: 2024/02/24 22:56:23 by flavian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// int	error(char *msg)
// {
// 	printf("Error\n");
// 	printf("%s\n", msg);
// 	return (1);
// }

// void	mem_set_p(t_pars *p, t_mlx *mlx)
// {
// 	t_img *EA;
// 	t_img *SO;
// 	t_img *NO;
// 	t_img *WE;

// 	EA = malloc(sizeof(t_img));
// 	SO = malloc(sizeof(t_img));
// 	NO = malloc(sizeof(t_img));
// 	WE = malloc(sizeof(t_img));
// 	EA->img = NULL;
// 	SO->img = NULL;
// 	NO->img = NULL;
// 	WE->img = NULL;

// 	p->EA = EA;
// 	p->SO = SO;
// 	p->NO = NO;
// 	p->WE = WE;
// 	p->C = 0;
// 	p->F = 0;
// 	p->map = NULL;
//     p->mlx_ptr = mlx->mlx_ptr;
// 	p->player = 0;
// }

// void	set_walls(t_g *game)
// {
// 	t_img	*NO;
// 	t_img	*SO;
// 	t_img	*EA;
// 	t_img	*WE;
// 	t_walls	*walls;

// 	NO = malloc(sizeof(t_img));
// 	if (!NO)
// 		return ;
// 	SO = malloc(sizeof(t_img));
// 	if (!SO)
// 		return ;
// 	EA = malloc(sizeof(t_img));
// 	if (!EA)
// 		return ;
// 	WE = malloc(sizeof(t_img));
// 	if (!WE)
// 		return ;

// 	NO->img = mlx_xpm_file_to_image(game->mlx.mlx_ptr, "./texture/NORD.xmp", 64, 64);
// 	SO->img = mlx_xpm_file_to_image(game->mlx.mlx_ptr, "./texture/SUD.xmp", 64, 64);
// 	EA->img = mlx_xpm_file_to_image(game->mlx.mlx_ptr, "./texture/EST.xmp", 64, 64);
// 	WE->img = mlx_xpm_file_to_image(game->mlx.mlx_ptr, "./texture/OUEST.xmp", 64, 64);
// 	walls = malloc(sizeof(t_walls));
// 	if (!walls)
// 		return ;
// 	walls->NO = *NO;
// 	walls->SO = *SO;
// 	walls->EA = *EA;
// 	walls->WE = *WE;

// 	game->walls = walls;
// }

void	set_event(t_g *game)
{
	t_ev	*event;

	event = malloc(sizeof(t_ev));
	if(!event)
		return ;
	event->mv_forth = 0;
	event->mv_back = 0;
	event->mv_left = 0;
	event->mv_right = 0;
	event->rot_left = 0;
	event->rot_right = 0;
	game->ev = event;
}

int main(void)
{
	t_g		game;
	t_mlx	mlx;

	game.map = get_map();
	game.player = (t_p *)malloc(sizeof(t_p));
	set_mlx(&mlx);
	game.mlx = mlx;
	set_event(&game);
	// set_walls(&game);
    find_player_pos(game.player, game.map);
    mlx_hook(mlx.win_ptr, ClientMessage, NoEventMask, ft_end, &game);
	mlx_hook(game.mlx.win_ptr, 2, 1L << 0, key_pressed, &game);
	mlx_loop_hook(game.mlx.win_ptr, key_action, &game);
	mlx_hook(game.mlx.win_ptr, 3, 1L << 1, key_released, &game);
    // mlx_loop_hook(mlx.mlx_ptr, &handle_no_event, &game.player);
    // mlx_key_hook(mlx.win_ptr, &ft_input, &game);
    render_3d(&game, &game.mlx);
    mlx_loop(mlx.mlx_ptr);
    return (0);
}