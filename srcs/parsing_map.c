/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fserpe <fserpe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 17:10:04 by kle-rest          #+#    #+#             */
/*   Updated: 2024/03/04 13:19:07 by fserpe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	create_map(t_pars *p, char *mapy)
{
	char	**map;
	int		tab_len;

	map = NULL;
	if (!mapy)
		return (1);
	if (!p->map)
	{
		p->map = malloc(sizeof(char *) * 2);
		if (!p->map)
			return (1);
		p->map[0] = mapy;
		p->map[1] = NULL;
		return (0);
	}
	tab_len = ft_strlen_tab(p->map);
	map = malloc(sizeof(char *) * (tab_len + 2));
	if (!map)
	{
		free(mapy);
		return (1);
	}
	set_map(map, p, mapy);
	return (0);
}

int	parsing_map(char *line, t_pars *p)
{
	int		i;
	int		len;
	char	*mapy;

	i = 0;
	len = ft_strlen(line) - 2;
	while (line[i] && check_char_map(line[i], p, i, len))
	{
		if ((i > 0 && line[i - 1] == ' ' && check_char(line[i]))
			|| (i < len && line[i + 1] == ' ' && check_char(line[i])))
			return (error("map unclosed !"));
		if (i < len && line[i + 1] == '0' && line[i] == ' ')
			return (error("map unclosed !"));
		i++;
	}
	if (i != (int)ft_strlen(line))
		return (1);
	mapy = ft_strdup(line);
	if (create_map(p, mapy))
		return (error("failed alloc map !"));
	return (0);
}

int	check_map_is_open(char **map)
{
	int	len_tab;
	int	i;
	int	j;

	len_tab = ft_strlen_tab(map) - 1;
	if (same_char_line(map[0], '1') || same_char_line(map[len_tab], '1'))
		return (1);
	j = 0;
	while (map[j])
	{
		i = 0;
		while (map[j][i] && map[j][i] != '\n')
		{
			if (check_verti_line(map, map[j][i], j, i))
				return (1);
			i++;
		}
		j++;
	}
	return (0);
}

int	check_map(char *line, int fd, t_pars *p)
{
	int	e;

	e = 0;
	while (line)
	{
		if (!check_line_is_empty(line))
			e++;
		else if (e && check_line_is_empty(line))
		{
			free(line);
			get_next_line(fd, 1);
			return (error("Map have to be the last elements !"));
		}
		if (parsing_map(line, p) && !e)
		{
			free(line);
			get_next_line(fd, 1);
			return (1);
		}
		free(line);
		line = get_next_line(fd, 0);
	}
	return (0);
}

int	get_map(char *line, int fd, t_pars *p)
{
	if (check_map(line, fd, p))
		return (1);
	if (p->player == 0)
		return (error("No player found !"));
	else if (p->player > 1)
		return (error("to much player found !"));
	if (check_map_is_open(p->map))
		return (error("Map unclosed !"));
	p->map = remove_backn(p->map);
	return (0);
}
