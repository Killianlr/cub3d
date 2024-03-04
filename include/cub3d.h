/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fserpe <fserpe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 11:20:39 by kle-rest          #+#    #+#             */
/*   Updated: 2024/03/04 13:23:02 by fserpe           ###   ########.fr       */
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
	t_img	*no;
	t_img	*so;
	t_img	*we;
	t_img	*ea;
	int		f;
	int		c;
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

typedef struct s_p
{
	float	posx;
	float	posy;
	float	angle;
	int		fov;
	int		fdpx;
	int		fdpy;
}				t_p;

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
}				t_mlx;

typedef struct s_ray
{
	double	ratio;
	float	precision;
	float	dirx;
	float	diry;
	float	mapx;
	float	mapy;
	float	deltadistx;
	float	deltadisty;
	float	stepx;
	float	stepy;
	float	sidedistx;
	float	sidedisty;
	int		side;
	float	perpwalldist;
	int		wally;
	int		sizewall;
	int		pixy;
}				t_ray;

typedef struct s_event
{
	int	mv_fwd;
	int	mv_bckwd;
	int	mv_left;
	int	mv_right;
	int	rot_left;
	int	rot_right;
}				t_ev;

typedef struct s_game
{
	t_p		*player;
	t_ray	ray;
	t_mlx	*mlx;
	t_pars	*p;
	t_ev	*ev;
}				t_g;

/*--------------main.c--------------*/

void	init_var_struct(t_g *game);
void	set_ev(t_g *game);
int		main(int ac, char **av);

/*--------------set_data.c--------------*/

int		set_texture_image(t_pars *p);
int		mem_set_next(t_g *game);
int		mem_set(t_g *game);
void	set_texture(t_pars *p);

/*--------------utiles_1.c--------------*/

void	find_player_pos(t_p *player, char **map);
void	set_mlx(t_mlx *mlx);
char	*ft_strndup(char *src, int size);
char	**remove_backn(char **map);

/*--------------utiles_2.c--------------*/

int		collision(t_g *game, float x, float y);
int		ft_isws(int c);
int		create_trgb(int t, int r, int g, int b);
int		error(char *msg);

/*--------------affichage.c--------------*/

int		color_texture(t_img *img, float wallx, t_ray *ray);
void	create_image(t_img *img, t_mlx *mlx);
int		my_mlx_pixel_get(t_img *img, int x, int y);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
void	draw_line(t_g *game, t_ray *ray, int pixx, t_img *img);

/*--------------parsing.c--------------*/

int		parsing(t_pars *p, char *file);

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
void	free_img(int i, t_pars *p);

/*--------------event.c--------------*/

int		key_pressed(int keysym, t_g *game);
int		key_release(int keysym, t_g *game);
int		key_action(t_g *game);
int		handle_no_event(void *data);

/*--------------utiles_parsing.c--------------*/

char	*get_id(char *line);
int		ft_strlen_tab(char **tab);
int		check_line_space(char *line);
int		check_file_is_cub(char *file);
int		ft_strlen_c(char *str, char c);

/*--------------utiles_parsing_map.c--------------*/

int		same_char_line(char *line, char c);
int		find_max_len_i(char **map);
int		check_char(char c);
void	set_map(char **map, t_pars *p, char *mapy);
int		check_verti_line(char **map, char c, int j, int i);

/*--------------raycasting.c--------------*/

int		check_texture(t_ray *ray, t_g *game);
void	check_dir(t_ray *ray, t_p *player);
void	check_wall(t_ray *ray, char **map);
float	set_raycasting(t_ray *ray, t_p *player, char **map);
void	render_3d(t_g *game, t_mlx *mlx);

/*--------------movement.c--------------*/

void	mpc_turn_left(t_g *game);
void	mpc_go_right(t_g *game);
void	mpc_go_left(t_g *game);
void	mpc_go_down(t_g *game);
void	mpc_go_up(t_g *game);

#endif