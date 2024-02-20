/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:56:04 by kle-rest          #+#    #+#             */
/*   Updated: 2024/02/20 15:58:19 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	check_is_map(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] == '1' || line[i] == '0')
		return (1);
	return (0);
}

int	set_data_img(int elem, char *path, t_pars *p)
{
	if (elem == 1)
	{
		p->t_north = mlx_xpm_file_to_image(p->mlx_ptr, path, 64, 64);
		free(path);
		if (!p->t_north)
			return (error("Invalid XPM !"));
	}
	else if (elem == 2)
	{
		p->t_south = mlx_xpm_file_to_image(p->mlx_ptr, path, 64, 64);
		free(path);
		if (!p->t_south)
			return (error("Invalid XPM !"));
	}
	else if (elem == 3)
	{
		p->t_west = mlx_xpm_file_to_image(p->mlx_ptr, path, 64, 64);
		free(path);
		if (!p->t_west)
			return (error("Invalid XPM !"));
	}
	else if (elem == 4)
	{
		p->t_east = mlx_xpm_file_to_image(p->mlx_ptr, path, 64, 64);
		free(path);
		if (!p->t_east)
			return (error("Invalid XPM !"));
	}
	return (0);
}

int	get_texture(char *line, t_pars *p, char *id, int elem)
{
	int	i;
	int	j;
	char	*path;

	i = 0;
	j = 0;
	while (line[i] == ' ')
		i++;
	if (!line[i + 1] || line[i] != id[0] || line[i + 1] != id[1])
		return (error("Wrong identifiant !"));
	i += 2;
	while (line[i] && line[i] == ' ')
		i++;
	if (!line[i])
		return (error("Missing data !"));
	path = malloc(sizeof(char) * (ft_strlen(&line[i])));
	if (!path)
		return (error("malloc failed !"));
	while (line[i] && line[i] != ' ')
		path[j++] = line[i++];
	path[j] = 0;
	if (set_data_img(elem, path, p))
		return (1);
	return (0);
}

int	get_color(char *line, t_pars *p, char c, int elem)
{
	int	r;
	int	g;
	int	b;
	int	i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (line[i] != c)
		return (error("Wrong identifiant !"));
	i++;
	while (line[i] && line[i] == ' ')
		i++;
	
}

int	check_line_space(char *line)
{
	int	i;
	int	s;

	i = 0;
	s = 0;
	while (line[i])
	{
		if (line[i] != ' ')
			s++;
		while (line[i] && line[i] != ' ')
			i++;
		i++;
	}
	if (s >= 3)
		return (1);
	return (0);
}

int	check_element(char *line, t_pars *p, int elem)
{
	if (elem < 7 && check_is_map(line))
		return (error("Missing elements !"));
	if (elem < 7 && check_line_space(line))
		return (error("Invalid data !"));
	if (elem > 7)
	{
		//free map
		return (error("To much element in this file !"));
	}
	if (elem == 1)
		return (get_texture(line, p, "NO", elem));
	else if (elem == 2)
		return (get_texture(line, p, "SO", elem));
	else if (elem == 3)
		return (get_texture(line, p, "WE", elem));
	else if (elem == 4)
		return (get_texture(line, p, "EA", elem));
	else if (elem == 5)
		return (get_color(line, p, 'F', elem));
	else if (elem == 6)
		return (get_color(line, p, 'C', elem));
	// else if (elem == 7)
	// 	get_map();
}

int	check_line_is_empty(char *line, t_pars *p)
{
	int		i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (!line[i])
		return (0);
	return (1);
}

int	parsing(t_pars *p, char *file)
{
	int	fd;
	char	*line;
	int		elem;

	fd = open(file, O_RDONLY);
	if (!fd)
		return (error("File unexiste or unaccess !"));
	line = get_next_line(fd, 0);
	if (!line)
		return (error("file empty !"));
	elem = 0;
	while (line)
	{
		if (check_line_is_empty(line, &p))
		{
			elem++;
			if (check_elem(line, &p, elem))
			{
				free(line);
				get_next_line(fd, 1);
				return (1);
			}
		}
		free(line);
		line = get_next_line(fd, 0);
	}
	return (0);
}
