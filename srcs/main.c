/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavian <flavian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 17:27:28 by kle-rest          #+#    #+#             */
/*   Updated: 2024/02/24 20:10:37 by flavian          ###   ########.fr       */
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
	t_img *EA;
	t_img *SO;
	t_img *NO;
	t_img *WE;

	EA = malloc(sizeof(t_img));
	SO = malloc(sizeof(t_img));
	NO = malloc(sizeof(t_img));
	WE = malloc(sizeof(t_img));
	EA->img = NULL;
	SO->img = NULL;
	NO->img = NULL;
	WE->img = NULL;

	p->EA = EA;
	p->SO = SO;
	p->NO = NO;
	p->WE = WE;
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
	if (ac > 2)
		return (error("To many arguments !"));
	set_mlx(&mlx);
	mem_set_p(&p, &mlx);
	if (parsing(&p, av[1]))
		return (1);
	printf("parsing crash pas");
	game.map = p.map;
	game.player = (t_p *)malloc(sizeof(t_p));
	game.mlx = mlx;
	game.p = &p;
    find_player_pos(game.player, game.map);
    mlx_key_hook(mlx.win_ptr, &ft_input, &game);
    render_3d(&game, &game.mlx);
    mlx_loop(mlx.mlx_ptr);
    return (0);
}