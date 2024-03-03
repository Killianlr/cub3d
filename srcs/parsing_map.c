/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 17:10:04 by kle-rest          #+#    #+#             */
/*   Updated: 2024/03/03 17:11:21 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	check_char(char c)
{
	if (c == '0')
		return (printf("map open\n"));
	if (c == 'N' || c == 'E' || c == 'W' || c == 'S')
		return (printf("player out of map \n"));
	return (0);
}

void	set_map(char **map, t_pars *p, char *mapy)
{
	int	i;

	i = 0;
	while (p->map[i])
	{
		map[i] = p->map[i];
		i++;
	}
	map[i] = mapy;
	map[i + 1] = NULL;
	free(p->map);
	p->map = map;
}

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
			return (error("map unclosed 1!"));
		if (i < len && line[i + 1] == '0' && line[i] == ' ')
			return (error("map unclosed 2!"));
		i++;
	}
	if (i != (int)ft_strlen(line))
		return (1);
	mapy = ft_strdup(line);
	if (create_map(p, mapy))
		return (error("failed alloc map !"));
	return (0);
}

int	same_char_line(char *line, char c)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] != ' ' && line[i] != c)
			return (1);
		i++;
	}
	return (0);
}

int	find_max_len_i(char **map)
{
	int	i;
	int	len;

	i = 1;
	len = ft_strlen(map[0]);
	while (map[i])
	{
		if ((int)ft_strlen(map[i]) > len)
			len = ft_strlen(map[i]);
		i++;
	}
	return (len);
}

int	check_verti_line(char **map, char c, int j, int i)
{
	int	len_tab;
	int	len_j_less;
	int	len_j_more;

	len_tab = ft_strlen_tab(map) - 1;
	if (j == 0 || j == len_tab)
		return (0);
	len_j_less = (int)ft_strlen(map[j - 1]) - 1;
	len_j_more = (int)ft_strlen(map[j + 1]) - 1;
	if (i + 1 > len_j_less && check_char(c))
		return (printf("map ouvert par le haut 1\n"));
	else if (i + 1 <= len_j_less && map[j - 1][i] == ' ' && check_char(c))
		return (printf("map ouvert par le haut 2\n"));
	if (i + 1 > len_j_more && check_char(c))
		return (printf("map ouvert par le bas 1\n"));
	else if (i + 1 <= len_j_more && map[j + 1][i] == ' ' && check_char(c))
		return (printf("map ouvert par le bas 2\n"));
	return (0);
}

int	check_map_is_fucking_open(char **map)
{
	int	i;
	int	j;

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

int	check_map_is_open(char **map)
{
	int	len_tab;

	len_tab = ft_strlen_tab(map) - 1;
	if (same_char_line(map[0], '1') || same_char_line(map[len_tab], '1'))
		return (1);
	if (check_map_is_fucking_open(map))
		return (1);
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
		return (error("Map unclosed 4!"));
	p->map = remove_backn(p->map);
	return (0);
}
