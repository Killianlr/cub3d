/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles_parsing_map.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fserpe <fserpe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 12:25:56 by kle-rest          #+#    #+#             */
/*   Updated: 2024/03/04 13:15:40 by fserpe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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

int	check_char(char c)
{
	if (c == '0')
		return (1);
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
	if (i > len_j_less && check_char(c))
		return (1);
	else if (i < len_j_less && map[j - 1][i] == ' ' && check_char(c))
		return (1);
	if (i > len_j_more && check_char(c))
		return (1);
	else if (i < len_j_more && map[j + 1][i] == ' ' && check_char(c))
		return (1);
	return (0);
}
