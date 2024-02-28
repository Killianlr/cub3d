/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavian <flavian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 11:56:04 by kle-rest          #+#    #+#             */
/*   Updated: 2024/02/26 11:00:33 by flavian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	print_scene(t_pars *p)
{
	if (p->NO->img)
		printf("p->NO->img : SET !\n");
	else
		printf("p->NO->img : UNSET !\n");
	if (p->SO->img)
		printf("p->SO->img : SET !\n");
	else
		printf("p->SO->img : UNSET !\n");
	if (p->WE->img)
		printf("p->WE->img : SET !\n");
	else
		printf("p->WE->img : UNSET !\n");
	if (p->EA->img)
		printf("p->EA->img : SET !\n");
	else
		printf("p->EA->img : UNSET !\n");
	printf("p.F = %d\n", p->F);
	printf("p.C = %d\n", p->C);
	printf("p.player = %d\n", p->player);
	int	m = 0;
	while (p->map[m])
	{
		printf("map : %s\n", p->map[m]);
		m++;
	}
}

int	parsing(t_pars *p, char *file)
{
	char	*line;
	int		elem;

	if (check_file_is_cub(file))
		return (printf("Error\nWrong extentions, cub3d expected .cub\n"));
	p->fd = open(file, O_RDONLY);
	if (p->fd <= 0)
		return (error("File unexiste or unaccess !", p));
	line = get_next_line(p->fd, 0);
	if (!line)
		return (error("file empty !", p));
	elem = 0;
	while (line)
	{
		// printf("line = %s", line);
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
				// printf("break\n");
				break ;
			}
		}
		free(line);
		line = get_next_line(p->fd, 0);
	}
	print_scene(p);
	return (0);
}
