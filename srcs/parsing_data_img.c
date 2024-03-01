
#include "../include/cub3d.h"

int	set_data_texture(char *line, t_pars *p, int e)
{
	p->elem = e;
	if (e == 1)
		return (get_texture(line, p, e));
	else if (e == 2)
		return (get_texture(line, p, e));
	else if (e == 3)
		return (get_texture(line, p, e));
	else if (e == 4)
		return (get_texture(line, p, e));
	else if (e == 5)
	 	return (get_color(line, p, 'F'));
	else if (e == 6)
	 	return (get_color(line, p, 'C'));
	return (0);
}

int	set_data_img(int elem, char *path, t_pars *p)
{
	if (elem == 1)
	{
		if (p->NO->img != NULL)
			return (error("NO already set"));
		p->NO->img = mlx_xpm_file_to_image(p->mlx_ptr, path, &p->NO->width, &p->NO->height);
		if (!p->NO->img)
			return (error("Invalid XPM !"));
		p->iNO = 1;
	}
	else if (elem == 2)
	{
		if (p->SO->img)
			return (error("SO already set"));
		p->SO->img = mlx_xpm_file_to_image(p->mlx_ptr, path, &p->SO->width, &p->SO->height);
		if (!p->SO->img)
			return (error("Invalid XPM !"));
		p->iSO = 1;
	}
	else if (elem == 3)
	{
		if (p->WE->img)
			return (error("WE already set"));
		p->WE->img = mlx_xpm_file_to_image(p->mlx_ptr, path, &p->WE->width, &p->WE->height);
		if (!p->WE->img)
			return (error("Invalid XPM !"));
		p->iWE = 1;
	}
	else if (elem == 4)
	{
		if (p->EA->img)
			return (error("EA already set"));
		p->EA->img = mlx_xpm_file_to_image(p->mlx_ptr, path, &p->EA->width, &p->EA->height);
		if (!p->EA->img)
			return (error("Invalid XPM !"));
		p->iEA = 1;
	}
	return (0);
}

int	get_texture(char *line, t_pars *p, int elem)
{
	int	i;
	int	j;
	char	*path;

	i = 0;
	j = 0;
	while (line[i] == ' ')
		i++;
	while (line[i] != ' ')
		i++;
	while (line[i] && line[i] == ' ')
		i++;
	path = malloc(sizeof(char) * (ft_strlen_c(&line[i], ' ') + 1)); //ft_strlen sans les espaces
	if (!path)
		return (error("malloc failed !"));
	while (line[i] && line[i] != ' ' && line[i] != '\n')
		path[j++] = line[i++];
	path[j] = 0;
	if (set_data_img(elem, path, p))
	{
		free(path);
		return (1);
	}
	free(path);
	return (0);
}