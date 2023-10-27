/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 12:54:22 by chustei           #+#    #+#             */
/*   Updated: 2023/10/27 16:05:39 by chustei          ###   ########.fr       */
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
# define MAP_WIDTH 8
# define MAP_HEIGHT 8
# define BPP sizeof(int32_t)
# define PI 3.14159265359
# define FOV 1.0471975512
# define MOVE_SPEED 2.0
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
	double	x;
	double	y;
	double	perp_distance;
	double	wall_height;
	double	wall_top;
	double	wall_bottom;
	double	row;
	double	column;
}	t_ray;

typedef struct s_game
{
	mlx_t			*mlx;
	mlx_image_t		*map;
	mlx_image_t		*screen;
	mlx_texture_t	*texture;
	double			player_x;
	double			player_y;
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
int		map_reading(t_board *board);
int		check_color(t_board *board, char *string, int i, int type);
int		is_identifier(char *line, int j);
int		select_identifier(t_board *board, char *line);
int		check_empty_lines(t_board *board);
int		check_identifier_factor(char *string);
int		check_map_walls(t_board *board);
void	print_struc(t_board *board);
void	die(char *errmsg, int errnum);
void	free_array(char **array);
int		ft_error(t_board *board, char *str, int i);

#endif
