
#include "../include/cub3d.h"

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
	// free_tab(p->map);
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
	int	i;
	int	len;
	char	*mapy;

	i = 0;
	len = ft_strlen(line) - 2;
	while (line[i] && check_char_map(line[i], p, i, len))
	{
		if (i > 0 && line[i - 1] == ' ' && line[i] == '0')
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

int	check_vertical_open(char **map, int i)
{
	int	j;

	j = 0;
	while (map[j])
	{
		if (!map[j][i] || map[j][i] != ' ')
			j++;
		else
		{
			if (j > 0 && map[j - 1][i] && map[j - 1][i] != '1' && map[j][i] == ' ')
				return (1);
			// printf("map[%d] = %s\n", j, map[j]);
			while (map[j][i] && map[j][i] == ' ')
				j++;
			// printf("map[%d] = %s\n", j, map[j]);
			if (!map[j][i])
				return (0);
			else if (map[j][i] != '1')
				return (1);
			else if (map[j][i] == 'N' || map[j][i] == 'S' || map[j][i] == 'E' || map[j][i] == 'W')
				return (error("Player out of map !"));
		}
	}
	return (0);
}

// int	check_hori_line(char **map, char c, int j, int i)
// {
// 	int	len_line;

// 	len_line = ft_strlen(map[j]) - 1;
// 	if ((i > 0 && map[j][i - 1] == ' ' && c == '0') ||
// 		(i == 0 && c == '0'))
// 		return (printf("ouvert par la gauche \n"));
// 	if ((i < len_line && map[j][i + 1] == ' ' && c == '0') ||
// 		(i == len_line && c == '0'))
// 		return (printf("ouvert par la droite"));
// 	return (0);
// }

int	check_verti_line(char **map, char c, int j, int i)
{
	int	len_tab;

	len_tab = ft_strlen_tab(map) - 1;
	// printf("c = %c\n", c);
	// if (j == 2 || j == 3)
	// 	printf("map[%d] : i = %d, strlen = %d , c = %c\n", j, i, (int)ft_strlen(map[j]), c);
	// printf("j = %d : i = %d : c = %c\n", j, i, c);
	if ((j > 0 && map[j - 1][i] == ' ' && c == '0') ||
		(j == 0 && c == '0'))
		return (printf("map ouvert par le haut 1 !\n"));
	else if (j > 0 && i > ((int)ft_strlen(map[j - 1]) - 2) && c == '0')
		return (printf("map ouvert par le haut 2 !\n"));
	if ((j < len_tab && map[j + 1][i] == ' ' && c == '0') ||
		(j == len_tab && c == '0'))
		return (printf("map ouvert par le bas ! 1 \n"));
	else if (j < len_tab && i > ((int)ft_strlen(map[j + 1]) - 2) && c == '0')
	{
		// printf("map[j] = %s && c = %c\n", map[j], c);
		return (printf("map ouvert par le bas ! 2 \n"));
	}
	return (0);
}

int	check_map_is_fucking_open(char **map)
{
	int	i;
	int	j;

	j = 0;
	// printf("map[2] = %s\n", map[2]);
	// printf("map[3] = %s\n", map[3]);
	while (map[j])
	{
		i = 0;
		while (map[j][i] && map[j][i] != '\n')
		{
			// if (check_hori_line(map, map[j][i], j, i))
			// 	return (1);
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
	// while (i < max_len_i)
	// {
	// 	if (check_vertical_open(map, i))
	// 		return (1);
	// 	i++;
	// }
	return (0);
}

int	get_map(char *line, int fd, t_pars *p)
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
	if (p->player == 0)
		return (error("No player found !"));
	else if (p->player > 1)
		return (error("to much player found !"));
	if (check_map_is_open(p->map))
		return (error("Map unclosed 4!"));
	p->map = remove_backn(p->map);
	return (0);
}