/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 11:20:39 by kle-rest          #+#    #+#             */
/*   Updated: 2024/02/20 15:43:39 by kle-rest         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <math.h>
# include "../minilibx-linux/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>

# define RESX 1200
# define RESY 900
# define NORTH M_PI
# define EAST M_PI / 2
# define SOUTH 0
# define WEST 3 * M_PI / 2
# define ROUGE_NORTH create_trgb(255, 255, 0, 0)
# define JAUNE_SOUTH create_trgb(255, 255, 255, 0)
# define VERT_WEST create_trgb(255, 0, 255, 0)
# define ROSE_EAST create_trgb(255, 255, 0, 255)
// # define F create_trgb(255, 0, 255, 255)
// # define C create_trgb(255, 192, 192, 192)

typedef struct s_pars
{
	void *t_north;
	void *t_south;
	void *t_east;
	void *t_west;
	int		F;
	int		C;
	char	**map;
	void	*mlx_ptr;
}				t_pars;

typedef	struct s_minimap
{
	int		posx;
	int		posy;
	int		deltax1;
	int		deltay1;
	int		deltax2;
	int		deltay2;
}				t_mm;


typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}			t_img;

typedef struct s_mpc
{
	int		pos_x;
	int		pos_y;
	void	*texture;
	int		tex_x;
	int		tex_y;
}			t_mpc;

typedef struct s_p
{
	float	posx;
	float	posy;
	float	angle;
	int		fov;
}			t_p;

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
}			t_mlx;

typedef struct s_ray
{
	double   ratio;
	float		dirx;
	float		diry;
	float		mapx;
	float		mapy;
	float	deltadistx;
	float	deltadisty;
	float		stepx;
	float		stepy;
	float	sidedistx;
	float	sidedisty;
	int		side;
	float	perpualldist;
}				t_ray;

typedef struct s_game
{
	t_p		*player;
	t_ray	ray;
	t_mlx	mlx;
	char	**map;
}				t_g;

/*--------------main.c--------------*/

int 	main(void);

/*--------------collision.c--------------*/

int		parsing(t_pars *p, char *file)

/*--------------end.c--------------*/

int		ft_end(t_mlx *mlx, t_p *player);

/*--------------event.c--------------*/

int		ft_input(int keysym, t_g *game);
int		handle_no_event(void *data);

/*--------------map.c--------------*/

char	**get_map(void);

/*--------------utiles.c--------------*/

void    find_player_pos(t_p *player, char **map);
int		create_trgb(int t, int r, int g, int b);
void	set_mlx(t_mlx *mlx);

/*--------------raycasting.c--------------*/

void    render_3d(t_g *game, t_mlx *mlx);

/*--------------collision.c--------------*/

int		collision(t_g *game, float x, float y);
void	print_map(char **map);



// void	create_img(t_dis *display);
// int		render_map(t_dis *display);

#endif