/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavian <flavian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:56:04 by kle-rest          #+#    #+#             */
/*   Updated: 2024/02/24 20:29:07 by flavian          ###   ########.fr       */
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
	printf("path = %s\n", path);
	if (elem == 1)
	{
		if (p->NO->img != NULL)
			return (error("NO already set"));
		p->NO->img = mlx_xpm_file_to_image(p->mlx_ptr, "./texture/NORD.xpm", &p->NO->width, &p->NO->height);
		free(path);
		if (!p->NO->img)
			return (error("Invalid XPM !"));
	}
	else if (elem == 2)
	{
		if (p->SO->img)
			return (error("SO already set"));
		p->SO->img = mlx_xpm_file_to_image(p->mlx_ptr, "./texture/SUD.xpm", &p->SO->width, &p->SO->height);
		free(path);
		if (!p->SO->img)
			return (error("Invalid XPM !"));
	}
	else if (elem == 3)
	{
		if (p->WE->img)
			return (error("WE already set"));
		p->WE->img = mlx_xpm_file_to_image(p->mlx_ptr, "./texture/OUEST.xpm", &p->WE->width, &p->WE->height);
		free(path);
		if (!p->WE->img)
			return (error("Invalid XPM !"));
	}
	else if (elem == 4)
	{
		if (p->EA->img)
			return (error("EA already set"));
		p->EA->img = mlx_xpm_file_to_image(p->mlx_ptr, "./texture/EST.xpm", &p->EA->width, &p->EA->height);
		free(path);
		if (!p->EA->img)
			return (error("Invalid XPM !"));
	}
	return (0);
}

int	ft_strlen_c(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

int	get_texture(char *line, t_pars *p, char *id, int elem)
{
	int	i;
	int	j;
	char	*path;

	printf("I\n");
	(void) id;
	i = 0;
	j = 0;
	while (line[i] == ' ')
		i++;
	while (line[i] != ' ')
		i++;
	while (line[i] && line[i] == ' ')
		i++;
	path = malloc(sizeof(char) * (ft_strlen(&line[i]))); //ft_strlen sans les espaces
	if (!path)
		return (error("malloc failed !"));
	while (line[i] && line[i] != ' ' && line[i] != '\n')
		path[j++] = line[i++];
	path[j] = 0;
	printf(" II\n");

	if (set_data_img(elem, path, p))
		return (1);
	printf("  III\n");

	return (0);
}

int	catch_value_color(char *line, int idx)
{
	int	i;
	int	j;
	int	len;
	char	*nb;
	int		ret;

	i = 0;
	j = 0;
	while (idx)
	{
		while (line[i] != ',')
			i++;
		if (line[i])
			i++;
		idx--;
	}
	len = ft_strlen_c(&line[i], ',');
	if (len > 3)
		return (-1);
	nb = malloc(sizeof(char) * (len + 1));
	if (!nb)
		return (-1);
	while (line[i] && line[i] != ',')
		nb[j++] = line[i++];
	nb[j] = 0;
	ret = ft_atoi(nb); // check si + 255
	free(nb);
	return (ret);
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
	{
		printf("BBBBBBBBBBBBBBBBBBBBB\n");

		return (error("Wrong identifiant !"));
	}
	i++;
	while (line[i] && line[i] == ' ')
		i++;
	r = catch_value_color(line, 0);
	g = catch_value_color(line, 1);
	b = catch_value_color(line, 2);
	if (r < 0 || g < 0 || b < 0)
		return (1);
	if (elem == 5)
	{
		if (p->F)
			return (error("F already set !"));
		p->F = create_trgb(255, r, g, b);
	}
	else
	{
		if (p->C)
			return (error("C already set !"));
		p->C = create_trgb(255, r, g, b);
	}
	return (0);
}

int	check_line_space(char *line)
{
	int	i;
	int	s;

	i = 0;
	s = 0;
	printf("string = %s", line);
	while (line[i])
	{
		printf("char = %c\n", line[i]);
		if (line[i] != ' ')
			s++;
		while (line[i] && line[i] != ' ')
			i++;
		i++;
	}
	printf("s = %d\n", s);
	if (s >= 3)
		return (1);
	return (0);
}

int	check_char_map(char c, t_pars *p, int i, int len)
{
	if ((i == 0 && c == '0') || (i == len && c == '0'))
		return (error("map unclose !")); // return 0
	if (c == '1' || c == '0')
		return (1);
	else if (c == '\n' || c == ' ')
		return (1);
	else if (c == 'N' || c == 'S')
	{
		p->player++;
		return (1);
	}
	else if (c == 'E' || c == 'W')
	{
		p->player++;
		return (1);
	}
	return (0);
}

int	ft_strlen_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
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
	free_tab(p->map);
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
	map = malloc(sizeof(char *) * (tab_len + 1));
	if (!map)
	{
		free(mapy);
		return (1);
	}
	set_map(map, p, mapy);
	return (0);
}

int	check_line_is_empty(char *line, t_pars *p)
{
	int		i;

	(void) p; //enlever p en arg
	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (!line[i])
		return (0);
	return (1);
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
			return (error("map unclosed !"));
		if (i < len && line[i + 1] == '0' && line[i] == ' ')
			return (error("map unclosed !"));
		i++;
	}
	if (i != (int)ft_strlen(line))
		return (error("Invalid caracteres in map !"));
	mapy = ft_strdup(line);
	if (create_map(p, mapy))
		return (error("failed alloc map !"));
	return (0);
}

int	get_map(char *line, int fd, t_pars *p)
{
	int	e;

	e = 0;
	while (line)
	{
		if (!check_line_is_empty(line, p))
			e++;
		else if (e && check_line_is_empty(line, p))
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
	return (0);
}

char *get_id(char *line)
{
	int	i;
	int	c;
	char *id;

	i = 0;
	c = 0;
	printf("line = %s\n", line);
	while (line[i] && line[i] == ' ')
		i++;
	while (line[i] != ' ')
	{
		i++;
		c++;
	}
	printf("c = %d\n", c);
	if (c > 2)
	{
		printf("AAAAAAAAAAAAAAAAA\n");
		printf("Wrong identifiant !\n");
		return (NULL);
	}
	id = malloc(sizeof(char) * (c + 1));
	if (!id)
		return (NULL);
	i = i - c;
	c = 0;
	while (line[i] != ' ')
		id[c++] = line[i++];
	id[c] = 0;
	return (id);
}

int	check_id(char *id, t_pars *p)
{
	(void) p;
	
	if (!ft_strncmp(id, "NO", 3))
		return (1);
	if (!ft_strncmp(id, "SO", ft_strlen(id)))
		return (2);
	if (!ft_strncmp(id, "WE", ft_strlen(id)))
		return (3);
	if (!ft_strncmp(id, "EA", ft_strlen(id)))
		return (4);
	if (!ft_strncmp(id, "F", ft_strlen(id)))
		return (5);
	if (!ft_strncmp(id, "C", ft_strlen(id)))
		return (6);
	return (0);
}

int	set_data_texture(char *line, t_pars *p, int e)
{
	if (e == 1)
		return (get_texture(line, p, "NO", e));
	else if (e == 2)
		return (get_texture(line, p, "SO", e));
	else if (e == 3)
		return (get_texture(line, p, "WE", e));
	else if (e == 4)
		return (get_texture(line, p, "EA", e));
	else if (e == 5)
	 	return (get_color(line, p, 'F', e));
	else if (e == 6)
	 	return (get_color(line, p, 'C', e));
	return (0);
}

int	check_element(char *line, t_pars *p, int elem)
{
	char	*id;
	int		e;

	id = NULL;
	printf("A\n");
	if (elem < 7 && check_is_map(line))
		return (error("Missing elements !"));
	printf(" B\n");
	
	// if (elem < 7 && check_line_space(line))
	// 	return (error("Invalid data !"));
	printf("  C\n");
	
	if (elem > 7)
	{
	printf("   D\n");
		//free map
		return (error("To much element in this file !"));
	}
	id = get_id(line);
	if (!id)
		return (1);
	printf("     E\n");

	e = check_id(id, p);
	free(id);
	printf("	 F\n");
	printf("e = %d\n", e);
	if (!e)
	{	
		printf("CCCCCCCCCCCCCC\n");

		return (error("Wrong identifiant !"));
	}
	if (set_data_texture(line, p, e))
		return (1);
	printf("	  G\n");
	
	return (0);
}


int	parsing(t_pars *p, char *file)
{
	int	fd;
	char	*line;
	int		elem;

	printf("1\n");
	fd = open(file, O_RDONLY);
	if (!fd)
		return (error("File unexiste or unaccess !"));
	line = get_next_line(fd, 0);
	if (!line)
		return (error("file empty !"));
	elem = 0;
	while (line)
	{
		if (check_line_is_empty(line, p))
		{
			printf(" 2\n");

			elem++;
			if (check_element(line, p, elem) && elem < 7)
			{
				printf("  3\n");

				free(line);
				get_next_line(fd, 1);
				return (1);
			}
			else if (elem > 6)
			{
				printf("   4\n");

				if (get_map(line, fd, p))
					return (1);
				break ;
			}
		}
		printf("	5\n");

		free(line);
		line = get_next_line(fd, 0);
	}
	printf("	 6\n");

	return (0);
}
