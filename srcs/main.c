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

int	error(char *msg, t_pars *p)
{
	free_t_pars(p);
	printf("Error\n");
	printf("%s\n", msg);
	return (1);
}

int	set_texture_image(t_pars *p)
{
	t_img *EA;
	t_img *SO;
	t_img *NO;
	t_img *WE;

	EA = malloc(sizeof(t_img));
	if (!EA)
		return (1);
	p->EA = EA;
	SO = malloc(sizeof(t_img));
	if (!SO)
		return (2);
	p->SO = SO;
	NO = malloc(sizeof(t_img));
	if (!NO)
		return (3);
	p->NO = NO;
	WE = malloc(sizeof(t_img));
	if (!WE)
		return (4);
	p->WE = WE;
	return (0);
}

void	free_img(int i, t_pars *p)
{
	if (!i)
	{
		free(p->EA);
		free(p->WE);
		free(p->SO);
		free(p->NO);
	}
	else if (i == 1)
		return ;
	else if (i == 2)
		free(p->EA);
	else if (i == 3)
	{
		free(p->EA);
		free(p->SO);
	}
	else if (i == 4)
	{
		free(p->EA);
		free(p->SO);
		free(p->NO);
	}
}

int	mem_set_p(t_pars *p, t_mlx *mlx)
{
	int	i;

	i = set_texture_image(p);
	if (i)
	{
		free_img(i, p);
		return (1);
	}
	p->EA->img = NULL;
	p->NO->img = NULL;
	p->WE->img = NULL;
	p->SO->img = NULL;
	p->C = 0;
	p->F = 0;
	p->map = NULL;
    p->mlx_ptr = mlx->mlx_ptr;
	p->player = 0;
	return (0);
}

int main(int ac, char **av)
{
	t_g		game;
	t_mlx	mlx;
    t_pars  p;

    if (ac == 0)
		return (error("No map !", &p));
	if (ac > 2)
		return (error("To many arguments !", &p));
	set_mlx(&mlx);
	if (mem_set_p(&p, &mlx))
		return (1);
	printf("avant parsing \n");
	if (parsing(&p, av[1]))
		return (1);
	printf("parsing crash pas");
	game.map = p.map;
	game.player = (t_p *)malloc(sizeof(t_p));
	game.mlx = mlx;
	game.p = p;
	ft_end(&game);
	return (0);
    find_player_pos(game.player, game.map);
    mlx_key_hook(mlx.win_ptr, &ft_input, &game);
    render_3d(&game, &game.mlx);
    mlx_loop(mlx.mlx_ptr);
	ft_end(&game);
    return (0);
}