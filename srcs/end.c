/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 17:27:15 by kle-rest          #+#    #+#             */
/*   Updated: 2024/02/29 11:48:55 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

// int	ft_end(t_g *game)
// {
// 	free(game->player);
// 	mlx_destroy_window(game->mlx.mlx_ptr, game->mlx.win_ptr);
// 	mlx_destroy_display(game->mlx.mlx_ptr);
// 	// free_t_pars(&game->p);
// 	free(game->mlx.mlx_ptr);
// 	exit(0);
// 	return (0);
// }

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
	if (p->iNO == 1)
		mlx_destroy_image(p->mlx_ptr, p->NO->img);
	if (p->iSO == 1)
		mlx_destroy_image(p->mlx_ptr, p->SO->img);
	if (p->iWE == 1)
		mlx_destroy_image(p->mlx_ptr, p->WE->img);
	if (p->iEA == 1)
		mlx_destroy_image(p->mlx_ptr, p->EA->img);
	if (p->NO)
		free(p->NO);
	if (p->SO)
		free(p->SO);
	if (p->WE)
		free(p->WE);
	if (p->EA)
		free(p->EA);
	if (p->map)
		free_tab(p->map);
	if (p->fd > 0)
		close(p->fd);
}