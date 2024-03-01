
#include "../include/cub3d.h"

int	ft_strlen_c(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c && str[i] != '\n')
		i++;
	return (i);
}

int	check_file_is_cub(char *file)
{
	int	i;

	i = ft_strlen(file) - 1;
	if (file[i] != 'b')
		return (1);
	i--;
	if (file[i] != 'u')
		return (1);
	i--;
	if (file[i] != 'c')
		return (1);
	i--;
	if (file[i] != '.')
		return (1);
	return (0);
}

int	check_line_space(char *line)
{
	int	i;
	int	s;

	i = 0;
	s = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] != ' ')
			s++;
		while (line[i] && line[i] != ' ' && line[i] != '\n')
			i++;
		i++;
	}
	if (s >= 3 || s < 1)
		return (1);
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

char *get_id(char *line)
{
	int	i;
	int	c;
	char *id;

	i = 0;
	c = 0;
	while (line[i] && line[i] == ' ')
		i++;
	while (line[i] && line[i] != ' ')
	{
		i++;
		c++;
	}
	if (c > 2)
		return (NULL);
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