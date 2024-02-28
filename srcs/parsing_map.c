
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
	len = ft_strlen(line);
	while (line[i] && check_char_map(line[i], p, i, len))
	{
		if (i > 0 && line[i - 1] == ' ' && line[i] == '0')
			return (error("map unclosed !", p));
		if (i < len && line[i + 1] == '0' && line[i] == ' ')
			return (error("map unclosed !", p));
		i++;
	}
	if (i != (int)ft_strlen(line))
		return (1);
	mapy = ft_strdup(line);
	if (create_map(p, mapy))
		return (error("failed alloc map !", p));
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
			return (error("Map have to be the last elements !", p));
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
		return (error("No player found !", p));
	else if (p->player > 1)
		return (error("to much player found !", p));
	p->map = remove_backn(p->map);
	return (0);
}