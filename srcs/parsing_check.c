
#include "../include/cub3d.h"

int	check_element(char *line, t_pars *p, int elem)
{
	char	*id;
	int		e;

	id = NULL;
	if (elem < 7 && check_is_map(line))
		return (error("Missing elements !"));
	if (elem < 7 && check_line_space(line))
	 	return (error("Invalid data !"));
	if (elem > 7)
		return (error("To much element in this file !"));
	id = get_id(line);
	if (!id)
		return (1);
	e = check_id(id);
	free(id);
	if (!e)
	{
		printf("WRONG ID\n");
		return (error("Wrong identifiant 3 !"));
	}
	if (set_data_texture(line, p, e))
		return (1);
	return (0);
}

int	check_id(char *id)
{
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

int	check_char_map(char c, t_pars *p, int i, int len)
{
	if ((i == 0 && c == '0') || (i == len && c == '0'))
	{
		printf("Error\n");
		printf("map unclose 3!\n");
		return (0);
	}
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
	printf("Error\n");
	printf("Invalid caractere in map : %c\n!", c);
	return (0);
}

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

int	check_line_is_empty(char *line)
{
	int		i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\n'))
		i++;
	if (!line[i])
		return (0);
	return (1);
}
