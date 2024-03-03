/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:56:04 by kle-rest          #+#    #+#             */
/*   Updated: 2024/03/03 16:59:52 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	get_data_file(int elem, char *line, t_pars *p)
{
	while (line)
	{
		if (check_line_is_empty(line))
		{
			elem++;
			if (elem < 7 && check_element(line, p, elem))
			{
				free(line);
				get_next_line(p->fd, 1);
				return (1);
			}
			else if (elem > 6)
			{
				if (get_map(line, p->fd, p))
					return (1);
				break ;
			}
		}
		free(line);
		line = get_next_line(p->fd, 0);
	}
	return (0);
}

int	parsing(t_pars *p, char *file)
{
	char	*line;
	int		elem;

	if (check_file_is_cub(file))
		return (printf("Error\nWrong extentions, cub3d expected .cub\n"));
	p->fd = open(file, O_RDONLY);
	if (p->fd <= 0)
		return (error("File unexiste or unaccess !"));
	line = get_next_line(p->fd, 0);
	if (!line)
		return (error("file empty !"));
	elem = 0;
	if (get_data_file(elem, line, p))
		return (1);
	return (0);
}
