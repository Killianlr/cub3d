/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 17:27:15 by kle-rest          #+#    #+#             */
/*   Updated: 2024/03/03 17:02:09 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	ft_end_1(t_g *game)
{
	free_t_pars(game->p);
	free(game->p);
	mlx_destroy_window(game->mlx->mlx_ptr, game->mlx->win_ptr);
	mlx_destroy_display(game->mlx->mlx_ptr);
	free(game->mlx->mlx_ptr);
	free(game->mlx);
	free(game->player);
	free(game);
	exit(1);
	return (0);
}

int	ft_end_0(t_g *game)
{
	free_t_pars(game->p);
	free(game->p);
	mlx_destroy_window(game->mlx->mlx_ptr, game->mlx->win_ptr);
	mlx_destroy_display(game->mlx->mlx_ptr);
	free(game->mlx->mlx_ptr);
	free(game->mlx);
	free(game->player);
	free(game->ev);
	free(game);
	exit(0);
	return (0);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	if (tab[i])
	{
		while (tab[i])
		{
			free(tab[i]);
			i++;
		}
	}
	free(tab);
}

void	free_t_pars(t_pars *p)
{
	if (p->ino == 1)
		mlx_destroy_image(p->mlx_ptr, p->no->img);
	if (p->iso == 1)
		mlx_destroy_image(p->mlx_ptr, p->so->img);
	if (p->iwe == 1)
		mlx_destroy_image(p->mlx_ptr, p->we->img);
	if (p->iea == 1)
		mlx_destroy_image(p->mlx_ptr, p->ea->img);
	if (p->no)
		free(p->no);
	if (p->so)
		free(p->so);
	if (p->we)
		free(p->we);
	if (p->ea)
		free(p->ea);
	if (p->map)
		free_tab(p->map);
	if (p->fd > 0)
		close(p->fd);
}
