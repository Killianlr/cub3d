/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 17:27:28 by kle-rest          #+#    #+#             */
/*   Updated: 2024/03/03 16:57:02 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	error(char *msg)
{
	printf("Error\n");
	printf("%s\n", msg);
	return (1);
}

int	set_texture_image(t_pars *p)
{
	t_img	*ea;
	t_img	*so;
	t_img	*no;
	t_img	*we;

	ea = malloc(sizeof(t_img));
	if (!ea)
		return (1);
	p->ea = ea;
	so = malloc(sizeof(t_img));
	if (!so)
		return (2);
	p->so = so;
	no = malloc(sizeof(t_img));
	if (!no)
		return (3);
	p->no = no;
	we = malloc(sizeof(t_img));
	if (!we)
		return (4);
	p->we = we;
	return (0);
}

void	free_img(int i, t_pars *p)
{
	if (!i)
	{
		free(p->ea);
		free(p->we);
		free(p->so);
		free(p->no);
	}
	else if (i == 1)
		return ;
	else if (i == 2)
		free(p->ea);
	else if (i == 3)
	{
		free(p->ea);
		free(p->so);
	}
	else if (i == 4)
	{
		free(p->ea);
		free(p->so);
		free(p->no);
	}
}

void	init_var_struct(t_g *game)
{
	game->p->ea->img = NULL;
	game->p->we->img = NULL;
	game->p->no->img = NULL;
	game->p->so->img = NULL;
	game->p->C = 0;
	game->p->F = 0;
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

int	mem_set_next(t_g *game)
{
	int	i;

	if (!game->player)
	{
		free(game->mlx);
		free(game->p);
		free(game);
		return (1);
	}
	i = set_texture_image(game->p);
	if (i)
	{
		free_img(i, game->p);
		free(game->mlx);
		free(game->p);
		free(game->player);
		free(game);
		return (1);
	}
	set_mlx(game->mlx);
	init_var_struct(game);
	return (0);
}

int	mem_set(t_g *game)
{
	if (!game)
		return (1);
	game->mlx = malloc(sizeof(t_mlx));
	if (!game->mlx)
	{
		free(game);
		return (1);
	}
	game->p = malloc(sizeof(t_pars));
	if (!game->p)
	{
		free(game->mlx);
		free(game);
		return (1);
	}
	game->player = malloc(sizeof(t_p));
	if (mem_set_next(game))
		return (1);
	return (0);
}

void	set_texture(t_pars *p)
{
	p->no->addr = mlx_get_data_addr(p->no->img,
			&p->no->bits_per_pixel, &p->no->line_length, &p->no->endian);
	p->so->addr = mlx_get_data_addr(p->so->img,
			&p->so->bits_per_pixel, &p->so->line_length, &p->so->endian);
	p->we->addr = mlx_get_data_addr(p->we->img,
			&p->we->bits_per_pixel, &p->we->line_length, &p->we->endian);
	p->ea->addr = mlx_get_data_addr(p->ea->img,
			&p->ea->bits_per_pixel, &p->ea->line_length, &p->ea->endian);
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
	{
		printf("FAIL PARSING\n");
		return (ft_end_1(game));
	}
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
