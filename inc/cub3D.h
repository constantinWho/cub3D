/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 12:54:22 by chustei           #+#    #+#             */
/*   Updated: 2023/11/09 13:40:22 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../lib/MLX42/include/MLX42/MLX42.h"
# include "../lib/libft/include/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# define MAP_WIDTH 8
# define MAP_HEIGHT 8
# define BPP sizeof(int32_t)
# define PI 3.14159265359
# define FOV 1.0471975512
# define MOVE_SPEED 1.0
# define CEILING_COLOR 0x7f8fa6FF
# define FLOOR_COLOR   0x353b48FF

# define WIDTH 512
# define HEIGHT 1024

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

typedef struct s_ray
{
	double	angle;
	double	side;
	double	x;
	double	y;
	double	direction_x;
	double	direction_y;
	double	perp_distance;
	double	wall_height;
	double	wall_top;
	double	wall_bottom;
	double	row;
	double	column;
	double	tex_offset_x;
	double	tex_offset_y;
}	t_ray;

typedef struct s_game
{
	mlx_t			*mlx;
	mlx_image_t		*map;
	mlx_image_t		*screen;
	mlx_texture_t	*texture;
	double			player_x;
	double			player_y;
	double			delta_x;
	double			delta_y;

	int				map_x;
	int				map_y;
	int				step_x;
	int				step_y;
	int				side;
	int				hit;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	double			camera_x;
	double			ray_dir_x;
	double			ray_dir_y;
	double			side_dist_x;
	double			side_dist_y;
	double			delta_dist_x;
	double			delta_dist_y;
	double			perp_wall_dist;
	double			wall_x;
	int				line_h;
	int				draw_start;
	int				draw_end;

	double			tile_size;
	double			rotation_angle;
	t_ray			ray;
	t_board			*board;
}	t_game;

// Raycaster
void	ft_render(void* param);
void	ft_raycaster(t_game *game, mlx_image_t *map, mlx_image_t *screen);
void	ft_keys(void* param);

// Parser
// colors
int	get_color_ceiling(t_board *board, char **split);
int	get_color_floor(t_board *board, char **split);
int	get_colors(t_board *board, char **split, int type);
int	check_color_comma(t_board *board, char *string, int i);
int	check_comma_digit(t_board *board, char *string, int i);
//identifier
int		is_identifier(char *line, int j);
int		select_identifier(t_board *board, char *line);
int		no_space(char readline);

// walls
int		check_map_walls(t_board *board);

int		map_reading(t_board *board);
int		check_color(t_board *board, char *string, int i, int type);

int		check_empty_lines(t_board *board);
int		check_identifier_factor(char *string);

void	print_struc(t_board *board);
void	die(char *errmsg, int errnum);
void	free_array(char **array);
int		ft_error(t_board *board, char *str, int i);

#endif
