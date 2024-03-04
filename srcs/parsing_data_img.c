/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_data_img.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 17:08:16 by kle-rest          #+#    #+#             */
/*   Updated: 2024/03/03 17:09:47 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	set_data_texture(char *line, t_pars *p, int e)
{
	p->elem = e;
	if (e == 1)
		return (get_texture(line, p, e));
	else if (e == 2)
		return (get_texture(line, p, e));
	else if (e == 3)
		return (get_texture(line, p, e));
	else if (e == 4)
		return (get_texture(line, p, e));
	else if (e == 5)
		return (get_color(line, p, 'F'));
	else if (e == 6)
		return (get_color(line, p, 'C'));
	return (0);
}

int	set_data_img_next(int elem, char *path, t_pars *p)
{
	if (elem == 3)
	{
		if (p->we->img)
			return (error("we already set"));
		p->we->img = mlx_xpm_file_to_image(p->mlx_ptr, path,
				&p->we->width, &p->we->height);
		if (!p->we->img)
			return (error("Invalid XPM !"));
		p->iwe = 1;
	}
	else if (elem == 4)
	{
		if (p->ea->img)
			return (error("ea already set"));
		p->ea->img = mlx_xpm_file_to_image(p->mlx_ptr, path,
				&p->ea->width, &p->ea->height);
		if (!p->ea->img)
			return (error("Invalid XPM !"));
		p->iea = 1;
	}
	return (0);
}

int	set_data_img(int elem, char *path, t_pars *p)
{
	if (elem == 1)
	{
		if (p->no->img != NULL)
			return (error("no already set"));
		p->no->img = mlx_xpm_file_to_image(p->mlx_ptr, path,
				&p->no->width, &p->no->height);
		if (!p->no->img)
			return (error("Invalid XPM !"));
		p->ino = 1;
	}
	else if (elem == 2)
	{
		if (p->so->img)
			return (error("so already set"));
		p->so->img = mlx_xpm_file_to_image(p->mlx_ptr, path,
				&p->so->width, &p->so->height);
		if (!p->so->img)
			return (error("Invalid XPM !"));
		p->iso = 1;
	}
	if (set_data_img_next(elem, path, p))
		return (1);
	free(path);
	return (0);
}

int	get_texture(char *line, t_pars *p, int elem)
{
	int		i;
	int		j;
	char	*path;

	i = 0;
	j = 0;
	while (line[i] == ' ')
		i++;
	while (line[i] != ' ')
		i++;
	while (line[i] && line[i] == ' ')
		i++;
	path = malloc(sizeof(char) * (ft_strlen_c(&line[i], ' ') + 1));
	if (!path)
		return (error("malloc failed !"));
	while (line[i] && line[i] != ' ' && line[i] != '\n')
		path[j++] = line[i++];
	path[j] = 0;
	if (set_data_img(elem, path, p))
	{
		free(path);
		return (1);
	}
	return (0);
}
