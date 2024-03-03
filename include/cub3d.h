/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kle-rest <kle-rest@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 11:20:39 by kle-rest          #+#    #+#             */
/*   Updated: 2024/03/03 17:22:50 by kle-rest         ###   ########.fr       */
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

typedef struct s_pars
{
	t_img *no;
	t_img *so;
	t_img *we;
	t_img *ea;
	int		F;
	int		C;
	char	**map;
	int		elem;
	void	*mlx_ptr;
	int		player;
	int		fd;
	int		ino;
	int		iwe;
	int		iea;
	int		iso;
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
	int		fdpx;
	int		fdpy;
}			t_p;

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
}			t_mlx;

typedef struct s_ray
{
	double   ratio;
	float	precision;
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
	int		wally;
	int		sizewall;
	int		pixy;
}				t_ray;

typedef	struct s_event
{
	int	mv_fwd;
	int	mv_bckwd;
	int	mv_left;
	int	mv_right;
	int	rot_left;
	int	rot_right;
}			t_ev;

typedef struct s_game
{
	t_p		*player;
	t_ray	ray;
	t_mlx	*mlx;
	t_pars	*p;
	t_ev	*ev;
}				t_g;

/*--------------main.c--------------*/

int	error(char *msg);

/*--------------collision.c--------------*/

/*--------------affichage.c--------------*/

int		color_texture(t_img *img, float wallx, t_ray *ray);
void	create_image(t_img *img, t_mlx *mlx);
int		my_mlx_pixel_get(t_img *img, int x, int y);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);

/*--------------parsing.c--------------*/

int		parsing(t_pars *p, char *file);

/*--------------parsing_utiles.c--------------*/

char 	*get_id(char *line);
int		ft_strlen_tab(char **tab);
int		check_line_space(char *line);
int		check_file_is_cub(char *file);
int		ft_strlen_c(char *str, char c);

/*--------------parsing_data_img.c--------------*/

int		get_texture(char *line, t_pars *p, int elem);
int		set_data_img(int elem, char *path, t_pars *p);
int		set_data_texture(char *line, t_pars *p, int e);

/*--------------parsing_data_color.c--------------*/

int		get_color(char *line, t_pars *p, char c);
int		catch_value_color(char *line, int idx);

/*--------------parsing_map.c--------------*/

int		get_map(char *line, int fd, t_pars *p);
int		parsing_map(char *line, t_pars *p);
int		create_map(t_pars *p, char *mapy);
void	set_map(char **map, t_pars *p, char *mapy);

/*--------------parsing_check.c--------------*/

int		check_line_is_empty(char *line);
int		check_is_map(char *line);
int		check_char_map(char c, t_pars *p, int i, int len);
int		check_id(char *id);
int		check_element(char *line, t_pars *p, int elem);

/*--------------end.c--------------*/

int		ft_end_0(t_g *game);
int		ft_end_1(t_g *game);
void	free_tab(char **tab);
void	free_t_pars(t_pars *p);

/*--------------event.c--------------*/

// int		ft_input(int keysym, t_g *game);
int		key_pressed(int keysym, t_g *game);
int		key_release(int keysym, t_g *game);
int		key_action(t_g *game);
int		handle_no_event(void *data);

/*--------------map.c--------------*/

char **remove_backn(char **map);

/*--------------utiles.c--------------*/

void    find_player_pos(t_p *player, char **map);
int		create_trgb(int t, int r, int g, int b);
void	set_mlx(t_mlx *mlx);
char	*ft_strndup(char *src, int size);

/*--------------raycasting.c--------------*/

void    render_3d(t_g *game, t_mlx *mlx);

/*--------------collision.c--------------*/

int		collision(t_g *game, float x, float y);
void	print_map(char **map);

/*--------------movement.c--------------*/

void	mpc_turn_left(t_g *game);
void	mpc_go_right(t_g *game);
void	mpc_go_left(t_g *game);
void	mpc_go_down(t_g *game);
void	mpc_go_up(t_g *game);

#endif