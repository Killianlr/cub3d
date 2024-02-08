/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:06:51 by kle-rest          #+#    #+#             */
/*   Updated: 2024/02/07 17:08:40 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

char	*ft_strndup(char *src, int size)
{
	int		i;
	char	*dest;

	i = 0;
	dest = malloc(sizeof(char) * size + 1);
	if (!dest)
		return (NULL);
	while (src[i] && i < size)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

void	set_data_mini_map(t_mm *mm, t_g *game)
{
	mm->posx = floor(game->player->posx);
	mm->posy = floor(game->player->posy);
	mm->deltax1 = 0;
	mm->deltay1 = 0;
	mm->deltax2 = 0;
	mm->deltay2 = 0;
	// printf("posx %d, posy %d\n", mm->posx, mm->posy);
	// while (mm->deltax1 < mm->posx - 7)
	// 	mm->deltax1++;
	// while (mm->deltay1 < mm->posy - 7)
	// 	mm->deltay1++;
	// mm->deltax2 = mm->deltax1 + 15;
	// mm->deltay2 = mm->deltay1 + 15;
}

char	*cut_minimap(t_mm *mm, char *map)
{
	char	*new_y_map;

	while (mm->deltax1)
	{
		map++;
		mm->deltay1--;
		mm->deltay2--;
	}
	new_y_map = ft_strndup(map, mm->deltay2);
	return (new_y_map);
}

char	**get_mini_map(t_g *game)
{
	t_mm	mm;
	// char	**minimap;
	// int		i;
	// int		mmy;

	set_data_mini_map(&mm, game);
	// minimap = malloc(sizeof(char *) * 16);
	// mmy = 0;
	// while (mmy <= 15)
	// {
	// 	minimap[mmy] = cut_minimap(&mm, game->map[mm.deltax1]);
	// 	mm.deltax1++;
	// 	mmx++;
	// }
	return (NULL);
}

void	draw_minimap(int x1, int x2, int y1, int y2, t_g *game)
{
	// int	x;
	// int	y;
	// int	pix;
	char	**mini_map;
	// int		mapx;
	// int		mapy;

	// x = 0;
	mini_map = get_mini_map(game);
	(void)x1;
	(void)x2;
	(void)y1;
	(void)y2;
	(void)mini_map;
	// while (x <= x2)
	// {
	// 	y = 0;
	// 	while (y <= y2)
	// 	{
	// 		pix = 15;
	// 		while (pix)

	// 		y++;
	// 	}
	// 	x++;
	// }
	// printf("minimap : x = %d, y = %d\n", x, y);
}

int	looking_dir(t_p *player)
{
	if (player->angle >= SOUTH && player->angle < EAST)
	{
		printf("im looking SOUTH EAST : %f\n", player->angle);
		return (1);
	}
	else if (player->angle <= NORTH && player->angle > EAST)
	{
		printf("im looking NORTH EAST : %f\n", player->angle);
		return (2);
	}
	else if (player->angle <= WEST && player->angle > NORTH)
	{
		printf("im looking NORTH WEST : %f\n", player->angle);
		return (3);
	}
	else if (player->angle >= WEST)
	{
		printf("im looking SOUTH WEST : %f\n", player->angle);
		return (4);
	}
	else
		return (0);
}

int	check_texture(t_ray *ray, float prev_perp, int dir)
{

	/* SI PREV_PERP < PERP CÉST QUE LE MUR SE RAPROCHE DU CENTRE DE L'ECRAN DONC TEXTURE WEST, SINON TEXTURE EAST POUR SIDE*/

	if (dir == 1)
	{
		if (prev_perp >= ray->perpualldist)
		{
			if (!ray->side)
				return (ROUGE_NORTH);
			else
				return (ROSE_EAST);
		}
	
		else if (prev_perp <= ray->perpualldist)
		{
			if (!ray->side)
				return (JAUNE_SOUTH);
			else
				return (VERT_WEST);
		}
	}
	else if (dir == 2)
	{
		if (prev_perp >= ray->perpualldist)
		{
			if (!ray->side)
				return (ROUGE_NORTH);
			else
				return (VERT_WEST);
		}
	
		else if (prev_perp <= ray->perpualldist)
		{
			if (!ray->side)
				return (JAUNE_SOUTH);
			else
				return (ROSE_EAST);
		}
	}
	else if (dir == 3)
	{
		if (prev_perp >= ray->perpualldist)
		{
			if (!ray->side)
				return (JAUNE_SOUTH);
			else
				return (VERT_WEST);
		}
	
		else if (prev_perp <= ray->perpualldist)
		{
			if (!ray->side)
				return (ROUGE_NORTH);
			else
				return (ROSE_EAST);
		}
	}
	else
	{
		if (prev_perp >= ray->perpualldist)
		{
			if (!ray->side)
				return (JAUNE_SOUTH);
			else
				return (ROSE_EAST);
		}
	
		else if (prev_perp <= ray->perpualldist)
		{
			if (!ray->side)
				return (ROUGE_NORTH);
			else
				return (VERT_WEST);
		}
	}
	return (0);
}

void	draw_line(t_mlx *mlx, int pix, int y1, int y2, t_ray *ray, float prev_perp, t_p *player)
{
	int	y;
	int	dir;

	y = 0;
	dir = looking_dir(player);
	while (y <= RESY)
	{
		if (pix > RESX / RESX + 50 && pix < (RESX / 4) - 1 && y > RESY / RESY + 50 && y < RESY / 4)
		{
			// mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr, pix, y, create_trgb(255, 0, 255, 0));
			y++;
		}
		else if (y < y1)
			mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr, pix, y, create_trgb(255, 0, 255, 255));
		else if (y > y2)
			mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr, pix, y, create_trgb(255, 192, 192, 192));
		else
		{
			// mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr, pix, y, create_trgb(255, 192, 0, 192));
			mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr, pix, y, check_texture(ray, prev_perp, dir));
		}
		y++;
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
	int hit;
	int	intmapy;
	int	intmapx;

	hit = 0;
	while (!hit)
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
			hit = 1;
	}
}

float	set_raycasting(t_ray *ray, t_p *player, char **map)
{
	float perpualldist;
	ray->dirx = cos(player->angle) / 2 + cos(player->angle - (M_PI / 2)) * ray->ratio;
	ray->diry = sin(player->angle) / 2 + sin(player->angle - (M_PI / 2)) * ray->ratio;
	ray->mapx = floor(player->posx);
	ray->mapy = floor(player->posy);
	ray->deltadistx = sqrt(1 + (pow(ray->diry, 2) / pow(ray->dirx, 2)));
	ray->deltadisty = sqrt(1 + (pow(ray->dirx, 2) / pow(ray->diry, 2)));
	check_dir(ray, player);
	check_wall(ray, map);
	if (ray->side == 0)
		perpualldist = (ray->mapx - player->posx + (1 - ray->stepx) / 2) / ray->dirx;
	else
		perpualldist = (ray->mapy - player->posy + (1 - ray->stepy) / 2) / ray->diry;
	return (perpualldist);
}

// void	print_angle(t_p *player)
// {

// }

void    render_3d(t_g *game, t_mlx *mlx)
{
	t_ray	ray;
    double pix;
	float	prev_perp;

	// prev_perp = 0;
    // pix = 0;
    pix = 2;
	// print_angle(game->player);
	ray.ratio = (0 - (RESX / 2))/ (RESX / 2);
	prev_perp = set_raycasting(&ray, game->player, game->map);
	ray.ratio = (1 - (RESX / 2))/ (RESX / 2);
	ray.perpualldist = set_raycasting(&ray, game->player, game->map);
	draw_line(mlx, pix, ((RESY / 2) - (RESY / 4) / ray.perpualldist), ((RESY / 2) + (RESY / 4) / ray.perpualldist), &ray, prev_perp, game->player);
	prev_perp = ray.perpualldist;
    while (pix <= RESX)
    {
		ray.ratio = (pix - (RESX / 2))/ (RESX / 2);
		ray.perpualldist = set_raycasting(&ray, game->player, game->map);
		// printf("%f\n", ray.perpualldist);
		printf("perpualldist = %f\n", ray.perpualldist);
		draw_line(mlx, pix, ((RESY / 2) - (RESY / 4) / ray.perpualldist), ((RESY / 2) + (RESY / 4) / ray.perpualldist), &ray, prev_perp, game->player);
		prev_perp = ray.perpualldist;
		pix++;
    }
	// draw_minimap(RESX / RESX + 50, (RESX / 4) - 1, RESY / RESY + 50, RESY / 4, game);
}