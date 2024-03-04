/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 17:27:28 by kle-rest          #+#    #+#             */
/*   Updated: 2024/03/04 12:52:11 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_var_struct(t_g *game)
{
	game->p->ea->img = NULL;
	game->p->we->img = NULL;
	game->p->no->img = NULL;
	game->p->so->img = NULL;
	game->p->c = 0;
	game->p->f = 0;
	game->p->map = NULL;
	game->p->mlx_ptr = game->mlx->mlx_ptr;
	game->p->player = 0;
	game->p->fd = 0;
	game->p->ino = 0;
	game->p->iso = 0;
	game->p->iea = 0;
	game->p->iwe = 0;
	game->p->elem = 0;
}

void	set_ev(t_g *game)
{
	t_ev	*ev;

	ev = malloc(sizeof(t_ev));
	if (!ev)
		return ;
	ev->mv_fwd = 0;
	ev->mv_bckwd = 0;
	ev->mv_left = 0;
	ev->mv_right = 0;
	ev->rot_left = 0;
	ev->rot_right = 0;
	game->ev = ev;
}

int	main(int ac, char **av)
{
	t_g	*game;

	if (ac == 1)
		return (error("No Map !"));
	if (ac > 2)
		return (error("To many arguments !"));
	game = malloc(sizeof(t_g));
	if (mem_set(game))
		return (error("Malloc failed !"));
	if (parsing(game->p, av[1]))
		return (ft_end_1(game));
	set_ev(game);
	set_texture(game->p);
	find_player_pos(game->player, game->p->map);
	mlx_hook(game->mlx->win_ptr, ClientMessage, NoEventMask, ft_end_0, game);
	mlx_hook (game->mlx->win_ptr, 2, 1L << 0, key_pressed, game);
	mlx_loop_hook(game->mlx->mlx_ptr, key_action, game);
	mlx_hook (game->mlx->win_ptr, 3, 1L << 1, key_release, game);
	render_3d(game, game->mlx);
	mlx_loop(game->mlx->mlx_ptr);
	ft_end_0(game);
	return (0);
}
