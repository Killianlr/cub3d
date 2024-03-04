/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   affichage.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fserpe <fserpe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 14:02:03 by kle-rest          #+#    #+#             */
/*   Updated: 2024/03/04 13:32:29 by fserpe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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

int	color_texture(t_img *img, float wallx, t_ray *ray)
{
	float	per_y;
	int		text_y;
	int		text_x;

	text_x = (int)(wallx * (float)img->width);
	if (ray->side == 0 && ray->dirx > 0)
		text_x = img->width - text_x - 1;
	if (ray->side == 1 && ray->diry < 0)
		text_x = img->width - text_x - 1;
	per_y = (float)ray->wally / (float)ray->sizewall;
	text_y = (float)img->height * per_y;
	return (my_mlx_pixel_get(img, text_x, text_y));
}

void	draw_line(t_g *game, t_ray *ray, int pixx, t_img *img)
{
	if (ray->pixy < (RESY / 2) - (RESY / 4) / ray->perpwalldist)
		my_mlx_pixel_put(img, pixx, ray->pixy, game->p->c);
	else if (ray->pixy > (RESY / 2) + (RESY / 4) / ray->perpwalldist)
		my_mlx_pixel_put(img, pixx, ray->pixy, game->p->f);
	else
		my_mlx_pixel_put(img, pixx, ray->pixy, check_texture(ray, game));
}
