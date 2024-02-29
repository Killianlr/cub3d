
#include "../include/cub3d.h"

int	catch_value_color(char *line, int idx)
{
	int	i;
	int	j;
	int	len;
	char	*nb;
	int		ret;

	i = 0;
	j = 0;
	while (idx && line[i])
	{
		while (line[i] != ',')
			i++;
		if (line[i])
			i++;
		idx--;
	}
	if (idx)
		return (-1);
	len = ft_strlen_c(&line[i], ',');
	if (len > 3 || len == 0)
		return (-1);
	nb = malloc(sizeof(char) * (len + 2));
	if (!nb)
		return (-1);
	while (line[i] && line[i] != ',')
		nb[j++] = line[i++];
	nb[j] = 0;
	ret = ft_atoi(nb); // check si + 255
	if (ret > 255 || ret < 0)
	{
		free(nb);
		return (-1);
	}
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
		return (error("Wrong identifiant 1 !"));
	i++;
	while (line[i] && line[i] == ' ')
		i++;
	r = catch_value_color(&line[i], 0);
	g = catch_value_color(&line[i], 1);
	b = catch_value_color(&line[i], 2);
	// printf("r = %d\n", r);
	// printf("g = %d\n", g);
	// printf("b = %d\n", b);
	if (r < 0 || g < 0 || b < 0)
		return (error("Invalid RGB"));
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