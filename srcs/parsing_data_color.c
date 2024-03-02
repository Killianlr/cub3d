
#include "../include/cub3d.h"

int	len_rgb(char *rgb, int check_ws)
{
	int	i;

	i = 0;
	(void)check_ws;
	while (rgb[i] && rgb[i] != ',' && rgb[i] != '\n')
	{
		if (!ft_isdigit(rgb[i]))
		}
		i++;
	}
	if (i > 3)
	{
		return (-1);
	}
	return (i);
}

int	catch_value_color(char *line, int idx)
{
	int	i;
	int	j;
	int	len;
	char	*nb;
	int		ret;
	int		check_ws;

	i = 0;
	j = 0;
	check_ws = 0;
	if (idx == 2)
		check_ws = 1;
	while (idx && line[i])
	{
		while (line[i] && line[i] != ',')
			i++;
		if (line[i])
			i++;
		idx--;
	}
	if (idx)
		return (-1);
	len = len_rgb(&line[i], check_ws);
	if (len == -1)
		return (-1);
	nb = malloc(sizeof(char) * (len + 2));
	if (!nb)
		return (-1);
	while (line[i] && line[i] != ',')
		nb[j++] = line[i++];
	nb[j] = 0;
	ret = ft_atoi(nb);
	if (ret > 255 || ret < 0)
	{
		free(nb);
		return (-1);
	}
	free(nb);
	return (ret);
}

int	set_color(t_pars *p, int r, int g, int b)
{
	if (p->elem == 5)
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

int	get_color(char *line, t_pars *p, char c)
{
	int	r;
	int	g;
	int	b;
	int	i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (line[i] != c)
		return (error("Wrong identifiant 1 !"));
	i++;
	while (line[i] && line[i] == ' ')
		i++;
	r = catch_value_color(&line[i], 0);
	g = catch_value_color(&line[i], 1);
	b = catch_value_color(&line[i], 2);
	if (r < 0 || g < 0 || b < 0)
		return (error("Invalid RGB"));
	if (set_color(p, r, g, b))
		return (1);
	return (0);
}