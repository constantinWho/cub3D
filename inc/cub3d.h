/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 12:54:22 by chustei           #+#    #+#             */
/*   Updated: 2023/11/24 17:57:00 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../lib/MLX42/include/MLX42/MLX42.h"
# include "../lib/libft/inc/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# define WIDTH 1024
# define HEIGHT 512
# define texWidth 1024
# define texHeight 1024
# define mapWidth 8
# define mapHeight 8

typedef struct s_board
{
	char	**map;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		*c;
	int		*f;
	int		fd;
	int		flag;
	double	width;
	double	height;
	char	map_face;
	double	map_px;
	double	map_py;
}	t_board;

typedef struct s_vector
{
	double	x;
	double	y;
} t_vector;

typedef struct s_point
{
	int	x;
	int	y;
} t_point;

typedef struct s_game
{
	mlx_t			*mlx;
	mlx_image_t		*screen;
	mlx_image_t		*world_map;
	t_vector		pos;
	t_vector		dir;
	t_vector		plane;
	t_vector		old_dir;
	t_vector		old_plane;
	t_vector		camera;
	t_vector		ray_dir;
	t_point			map;
	t_vector		side_dist;
	t_vector		delta_dist;
	t_point			step;
	int				hit;
	int				side;
	int				line_height;
	int				draw_start;
	int				draw_end;
	uint32_t		color;
	double			perp_wall_dist;
	double			move_speed;
	double			rot_speed;
	double			wall_x;
	uint32_t		**buffer;
	mlx_texture_t	*north;
	mlx_texture_t	*south;
	mlx_texture_t	*west;
	mlx_texture_t	*east;
	uint32_t		color_c;
	uint32_t		color_f;
	t_board			*board;
} t_game;

// Raycasting
void		ft_keys_listener(void *param);
void		ft_render(void *param);
void		ft_wall_to_buffer(t_game *game);
uint32_t	get_image_color(mlx_texture_t *texture, t_point p);
void		ft_calc_step_and_side_dist(t_game *game);
void		ft_dda(t_game *game);
void		ft_calc_lines(t_game *game);
void		ft_end_game(t_game *game);

// Parser
// colors
int			get_color_ceiling(t_board *board, char **split);
int			get_color_floor(t_board *board, char **split);
int			get_colors(t_board *board, char **split, int type);
int			check_color_comma(t_board *board, char *string, int i);
int			check_comma_digit(t_board *board, char *string, int i);
//identifier
int			is_identifier(char *line, int j);
int			select_identifier(t_board *board, char *line);
int			no_space(char readline);
// walls
int			check_map_walls(t_board *board);
int			map_reading(t_board *board);
int			check_color(t_board *board, char *string, int i, int type);
int			check_empty_lines(t_board *board);
int			check_identifier_factor(char *string);
void		print_struc(t_board *board);
void		die(char *errmsg, int errnum);
void		free_array(char **array);
int			ft_error(t_board *board, char *str, int i);

#endif
