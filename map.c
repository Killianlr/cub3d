
#include "cub3d.h"

char **remove_backn(char **map)
{
	int	i;
	int	len;

	i = 0;
	while (map[i])
	{
		len = ft_strlen(map[i]);
		map[i][len - 1] = '\0';
		printf("%s", map[i]);
		i++;
	}
	return (map);
}