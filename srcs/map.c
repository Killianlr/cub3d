/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavian <flavian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 17:27:36 by kle-rest          #+#    #+#             */
/*   Updated: 2024/02/24 20:38:12 by flavian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

char **remove_backn(char **map)
{
	int	i;
	int	len;

	i = 0;
	while (map[i])
	{
		len = ft_strlen(map[i]);
		if (map[i][len - 1] == '\n')
			map[i][len - 1] = '\0';
		i++;
	}
	return (map);
}

char	**get_map(void)
{
	int	fd;
	char	**map;
	int	i;

	fd = open("map/map.cub", O_RDONLY);
	if (fd < 0)
		return (NULL);
	map = malloc(sizeof(char *) * 6);
	if (!map)
		return (NULL);
	i = 0;
	while (i < 6)
	{
		map[i] = get_next_line(fd, 0);
		i++;
	}
	map[i] = NULL;
	map = remove_backn(map);
	return (map);
}