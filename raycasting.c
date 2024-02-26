/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavian <flavian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 12:06:51 by kle-rest          #+#    #+#             */
/*   Updated: 2024/02/26 11:16:13 by flavian          ###   ########.fr       */
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

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dest;

	dest = img->addr + (y * img->line_length
			+ x * (img->bits_per_pixel / 8));
	*(unsigned int *) dest = color;
}

int	my_mlx_pixel_get(t_img *img, int x, int y)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	return (*(unsigned int *) dst);
}

void	create_image(t_img *img, t_mlx *mlx)
{
	img->img = mlx_new_image(mlx->mlx_ptr, RESX, RESY);
	img->addr = NULL;
	if (img->img)
		img->addr = mlx_get_data_addr(img->img,
				&img->bits_per_pixel,
				&img->line_length, &img->endian);
}

int	color_texture(t_img *img, float ratio, int y, int hauteur_mur)
{
	float	per_x;
	float	per_y;
	int		text_x;
	int		text_y;

	// printf("ratio = %f : y = %d : hautuermur = %d\n", ratio, y, hauteur_mur);
	per_x = ratio - floor(ratio);
	// printf("y = %d\n", y);
	// printf("hauteurmur = %d\n", hauteur_mur);
	per_y = y / hauteur_mur;
	text_x = img->width * per_x;
	text_y = img->height * per_y;
	// printf("w = %d : h = %d\n", img->width, img->height);
	// printf("x = %f : y = %f\n", per_x, per_y);
	// printf("text_x = %d : text_y = %d\n", text_x, text_y);
	return (my_mlx_pixel_get(img, text_x, text_y));
}

int	check_texture(t_ray *ray, t_g *game, int y, int hauteur_mur)
{
	if (ray->side)
	{
		if (ray->stepy < 0)
			return (color_texture(game->p.WE, ray->mapx, y, hauteur_mur));
		else
			return (color_texture(game->p.EA, ray->mapx, y, hauteur_mur));
	}
	else
	{
		if (ray->stepx < 0)
			return (color_texture(game->p.SO, ray->mapy, y, hauteur_mur));
		else
			return (color_texture(game->p.NO, ray->mapy, y, hauteur_mur));
	}
	// if (ray->side)
	// {
	// 	if (ray->stepy < 0)
	// 		return (VERT_WEST);
	// 	else
	// 		return (ROSE_EAST);
	// }
	// else
	// {
	// 	if (ray->stepx < 0)
	// 		return (JAUNE_SOUTH);
	// 	else
	// 		return (ROUGE_NORTH);
	// }
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

float	length_vec(float x, float y)
{
	return (sqrt(x * x + y * y)); 
}

float	set_raycasting(t_ray *ray, t_p *player, char **map)
{
	int	intmapy;
	int	intmapx;

	ray->dirx = cos(player->angle) / 2 + cos(player->angle - (M_PI / 2)) * ray->ratio;
	ray->diry = sin(player->angle) / 2 + sin(player->angle - (M_PI / 2)) * ray->ratio;
	ray->mapx = floor(player->posx);
	ray->mapy = floor(player->posy);
	// ray->deltadistx = sqrt(1 + (pow(ray->diry, 2) / pow(ray->dirx, 2)));
	// ray->deltadisty = sqrt(1 + (pow(ray->dirx, 2) / pow(ray->diry, 2)));
	// check_dir(ray, player);
	// check_wall(ray, map);
	ray->pos[0] = player->posx;
	ray->pos[1] = player->posy;

	while(1)
	{
		float dist_x = (floor(ray->pos[0]) + (1 - 2 * (ray->dirx < 0)) ) - ray->pos[0];
		float dist_y = (floor(ray->pos[1]) + (1 - 2 * (ray->diry < 0)) ) - ray->pos[1];

		float steps_x = dist_x / ray->dirx; //steps = temps = "seconde"
		float steps_y = dist_y / ray->diry;

		if (steps_x < steps_y)
		{
			ray->pos[0] += ray->dirx * steps_x;
			ray->pos[1] += ray->diry * steps_x;
		}
		else
		{
			ray->pos[0] += ray->dirx * steps_y;
			ray->pos[1] += ray->diry * steps_y;
		}
		intmapx = floor(ray->pos[0]);
		intmapy = floor(ray->pos[1]);
		if (map[intmapx][intmapy] == '1') // check in bound
			break ;
	}

	//extraire les valeurs de pos

	//calculer taille d'un vecteur 
	return length_vec(ray->pos[0] - player->posx, ray->pos[1] - player->posy);

	// if (ray->side == 0)
	// 	perpualldist = (ray->mapx - player->posx + (1 - ray->stepx) / 2) / ray->dirx;
	// else
	// 	perpualldist = (ray->mapy - player->posy + (1 - ray->stepy) / 2) / ray->diry;
	// return (perpualldist);
}

void    render_3d(t_g *game, t_mlx *mlx)
{
	t_ray	ray;
	t_img	img;
    double pix;
	int		y;
	int		hauteur_mur;

    pix = 0;
	img.img = NULL;
	create_image(&img, mlx);
    while (pix <= RESX)
    {
		ray.ratio = (pix - (RESX / 2))/ (RESX / 2);
		ray.perpualldist = set_raycasting(&ray, game->player, game->map);
		y = 0;
		while (y <= RESY)
		{
			hauteur_mur = ((RESY / 2) + (RESY / 4) / ray.perpualldist) - ((RESY / 2) - (RESY / 4) / ray.perpualldist);
			if (y < (RESY / 2) - (RESY / 4) / ray.perpualldist)
				my_mlx_pixel_put(&img, pix, y, game->p.F);
			else if (y > (RESY / 2) + (RESY / 4) / ray.perpualldist)
				my_mlx_pixel_put(&img, pix, y, game->p.C);
			else
			{
				// recuperer le x et y de limage, 
				my_mlx_pixel_put(&img, pix, y, check_texture(&ray, game, y - (RESY / 2) + (RESY / 4) / ray.perpualldist, hauteur_mur));

			}
			y++;
		}
		pix++;
    }
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, img.img, 0, 0);
	mlx_destroy_image(mlx->mlx_ptr, img.img);
}