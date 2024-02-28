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

int	color_texture(t_img *img, float precision, int y, int hauteur_mur)
{
	float	per_x;
	float	per_y;
	int		text_x;
	int		text_y;

	// printf("ratio = %f : y = %d : hautuermur = %d\n", ratio, y, hauteur_mur);
	per_x = precision - floor(precision);
	// per_x = sqrt(per_x * per_x);
	// printf("y = %d\n", y);
	// printf("y = %d : hauteurmur = %d\n", y, hauteur_mur);
	// printf("per_x = %f\n", per_x);
	per_y = (float)y / (float)hauteur_mur;
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
			return (color_texture(game->p.WE, ray->precision, y, hauteur_mur));
		else
			return (color_texture(game->p.EA, -ray->precision, y, hauteur_mur));
	}
	else
	{
		if (ray->stepx < 0)
			return (color_texture(game->p.SO, -ray->precision, y, hauteur_mur));
		else
			return (color_texture(game->p.NO, ray->precision, y, hauteur_mur));
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
		if (ray->sidedistx < ray->sidedisty)
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
	printf("fin du hit\n");
}

double	set_raycasting(t_ray *ray, t_p *player, char **map)
{
	double	perpualldist;

	ray->raydirx = ray->dirx + ray->planex * ray->camerax;
	ray->raydiry = ray->diry + ray->planey * ray->camerax; 
	ray->deltadistx = sqrt(1 + (ray->raydiry * ray->raydiry) / (ray->raydirx * ray->raydirx));
	ray->deltadisty = sqrt(1 + (ray->raydirx * ray->raydirx) / (ray->raydiry * ray->raydiry));
	ray->mapx = floor(player->posx);
	ray->mapy = floor(player->posy);
	if(ray->raydirx == 0)
		ray->deltadistx = 1e30;
	else
		ray->deltadistx = fabs(1 / ray->raydirx);
	if(ray->raydiry == 0)
		ray->deltadisty = 1e30;
	else
		ray->deltadisty = fabs(1 / ray->raydiry);
	check_dir(ray, player);
	check_wall(ray, map);
	printf("ici\n");
	if (ray->side == 0)
		perpualldist = (ray->sidedistx - ray->deltadistx);
	else
		perpualldist = (ray->sidedisty - ray->deltadisty);
	return (perpualldist);
}

void    render_3d(t_g *game, t_mlx *mlx, char **map)
{
	t_ray	ray;
	t_img	img;
    double pix;
	int		y;
	int		lineHeight;
	int		drawStart;
	int		drawEnd;

    pix = 0;
	img.img = NULL;
	ray.dirx = -1;
	ray.diry = 0;
	ray.planex = 0;
	ray.planey = 0.66;

	ray.time = 0;
	ray.oldtime = 0;
	create_image(&img, mlx);
	printf("\ndebut raycasting !\n");
    while (pix <= RESX)
    {
		ray.camerax = 2 * pix / (double)RESY - 1;
		printf("avant algo raycasting\n");
		ray.perpualldist = set_raycasting(&ray, game->player, map);
		printf("apres algo raycasting\n");
		lineHeight = (int)(RESX / ray.perpualldist);
		drawStart = -lineHeight / 2 + RESX / 2;
		if (drawStart < 0)
			drawStart = 0;
		drawEnd = lineHeight / 2 + RESX / 2;
		if (drawEnd >= RESX)
			drawEnd = RESX - 1;
		y = 0;
		printf("avant de colorier\n");
		while (y <= RESY)
		{
			if (y < drawStart)
				my_mlx_pixel_put(&img, pix, y, game->p.F);
			else if (y > drawEnd)
				my_mlx_pixel_put(&img, pix, y, game->p.C);
			else
			{
				my_mlx_pixel_put(&img, pix, y, create_trgb(255, 255, 0, 0));
			}
			y++;
		}
		pix++;
    }
	printf("fin raycasting !\n");
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, img.img, 0, 0);
	mlx_destroy_image(mlx->mlx_ptr, img.img);
}