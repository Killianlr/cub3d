/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 17:27:28 by kle-rest          #+#    #+#             */
/*   Updated: 2024/02/20 15:43:21 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	error(char *msg)
{
	printf("Error\n");
	printf("%s\n", msg);
	return (1);
}

void	mem_set_p(t_pars *p, t_mlx *mlx)
{
	p->t_east = NULL;
	p->t_south = NULL;
	p->t_north = NULL;
	p->t_west = NULL;
	p->C = 0;
	p->F = 0;
	p->map = NULL;
    p->mlx_ptr = mlx->mlx_ptr;
	p->player = 0;
}

int main(int ac, char **av)
{
	t_g		game;
	t_mlx	mlx;
    t_pars  p;

    if (ac == 0)
		return (error("No map !"));
	if (ac > 1)
		return (error("To many arguments !"));
	set_mlx(&mlx);
	mem_set_p(&p, mlx);
	if (parsing(&p, av[1]))
		return (1);
	game.map = p.map;
	game.player = (t_p *)malloc(sizeof(t_p));
	game.mlx = mlx;
    find_player_pos(game.player, game.map);
    mlx_key_hook(mlx.win_ptr, &ft_input, &game);
    render_3d(&game, &game.mlx);
    mlx_loop(mlx.mlx_ptr);
    return (0);
}