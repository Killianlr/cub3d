/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fserpe <fserpe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:06:51 by kle-rest          #+#    #+#             */
/*   Updated: 2024/03/04 13:02:27 by fserpe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	check_texture(t_ray *ray, t_g *game)
{
	float	wallx;

	if (ray->side)
	{
		wallx = game->player->posx + ray->perpualldist * ray->dirx;
		wallx -= floor(wallx);
		if (ray->stepy < 0)
			return (color_texture(game->p->ea, wallx, ray));
		else
			return (color_texture(game->p->we, wallx, ray));
	}
	else
	{
		wallx = game->player->posy + ray->perpualldist * ray->diry;
		wallx -= floor(wallx);
		if (ray->stepx < 0)
			return (color_texture(game->p->so, wallx, ray));
		else
			return (color_texture(game->p->no, wallx, ray));
	}
}

void	check_dir(t_ray *ray, t_p *player)
{
	if (ray->dirx < 0)
	{
		ray->stepx = -1;
		ray->sidedistx = (player->posx - ray->mapx) * ray->deltadistx;
	}
	else
	{
		ray->stepx = 1;
		ray->sidedistx = (ray->mapx + 1 - player->posx) * ray->deltadistx;
	}
	if (ray->diry < 0)
	{
		ray->stepy = -1;
		ray->sidedisty = (player->posy - ray->mapy) * ray->deltadisty;
	}
	else
	{
		ray->stepy = 1;
		ray->sidedisty = (ray->mapy + 1 - player->posy) * ray->deltadisty;
	}
}

void	check_wall(t_ray *ray, char **map)
{
	int	intmapy;
	int	intmapx;

	while (1)
	{
		if (!ray->sidedisty || (ray->sidedistx
				&& ray->sidedistx < ray->sidedisty))
		{
			ray->sidedistx += ray->deltadistx;
			ray->mapx += ray->stepx;
			ray->side = 0;
		}
		else
		{
			ray->sidedisty += ray->deltadisty;
			ray->mapy += ray->stepy;
			ray->side = 1;
		}
		intmapx = floor(ray->mapx);
		intmapy = floor(ray->mapy);
		if (map[intmapx][intmapy] == '1')
			break ;
	}
}

float	set_raycasting(t_ray *ray, t_p *player, char **map)
{
	float	perpualldist;

	ray->dirx = cos(player->angle) / 2
		+ cos(player->angle - (M_PI / 2)) * ray->ratio;
	ray->diry = sin(player->angle) / 2
		+ sin(player->angle - (M_PI / 2)) * ray->ratio;
	ray->mapx = floor(player->posx);
	ray->mapy = floor(player->posy);
	ray->deltadistx = sqrt(1 + (pow(ray->diry, 2)
				/ pow(ray->dirx, 2)));
	ray->deltadisty = sqrt(1 + (pow(ray->dirx, 2)
				/ pow(ray->diry, 2)));
	check_dir(ray, player);
	check_wall(ray, map);
	if (ray->side == 0)
		perpualldist = (ray->mapx - player->posx
				+ (1 - ray->stepx) / 2) / ray->dirx;
	else
		perpualldist = (ray->mapy - player->posy
				+ (1 - ray->stepy) / 2) / ray->diry;
	return (perpualldist);
}

void	render_3d(t_g *game, t_mlx *mlx)
{
	t_ray	ray;
	t_img	img;
	double	pixx;

	pixx = 0;
	img.img = NULL;
	create_image(&img, mlx);
	while (pixx <= RESX)
	{
		ray.ratio = (pixx - (RESX / 2)) / (RESX / 2);
		ray.perpualldist = set_raycasting(&ray, game->player, game->p->map);
		ray.pixy = 0;
		while (ray.pixy <= RESY)
		{
			ray.sizewall = ((RESY / 2) + (RESY / 4) / ray.perpualldist)
				- ((RESY / 2) - (RESY / 4) / ray.perpualldist);
			ray.wally = ray.pixy - (RESY / 2) + (RESY / 4) / ray.perpualldist;
			draw_line(game, &ray, pixx, &img);
			ray.pixy++;
		}
		pixx++;
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, img.img, 0, 0);
	mlx_destroy_image(mlx->mlx_ptr, img.img);
}
