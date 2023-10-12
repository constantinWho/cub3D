/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 12:54:22 by chustei           #+#    #+#             */
/*   Updated: 2023/10/12 09:50:21 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../lib/MLX42/include/MLX42/MLX42.h"
# include "../lib/libft/inc/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h>
# include <math.h>
# define MAP_WIDTH 8
# define MAP_HEIGHT 8
# define BPP sizeof(int32_t)
# define PI 3.14159265359
# define FOV 1.0471975512
# define MOVE_SPEED 3.0
# define CEILING_COLOR 0x7f8fa6FF
# define FLOOR_COLOR   0x353b48FF
# define WIDTH 512
# define HEIGHT 1024

typedef struct s_ray
{
	double	angle;
	double	x;
	double	y;
	double	perp_distance;
	double	wall_height;
	double	wall_top;
	double	wall_bottom;
	int		row;
	int		column;
}	t_ray;

typedef struct s_game
{
	mlx_t			*mlx;
	mlx_image_t		*map;
	mlx_image_t		*screen;
	int				player_x;
	int				player_y;
	double			rotation_angle;
	t_ray			ray;
}	t_game;

void	ft_render(void* param);
void	ft_raycaster(t_game *game, mlx_image_t *map, mlx_image_t *screen);
void	ft_keys(void* param);

#endif
