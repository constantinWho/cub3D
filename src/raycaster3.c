/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 16:13:45 by chustei           #+#    #+#             */
/*   Updated: 2023/11/02 12:26:18 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

void	ft_raycaster(t_game *game, mlx_image_t *map, mlx_image_t *screen)
{
	(void)screen;
	(void)map;
	(void)game;
	int x = 0;
	while (x < 512)
	{
		double	camera_x;
		double	ray_dir_x;
		double	ray_dir_y;
		camera_x = 2 * x / (double)512 - 1;
		ray_dir_x = game->direction_x + game->plane_x * camera_x;
		ray_dir_y = game->direction_y + game->plane_y * camera_x;

		int map_x = (int)game->player_x;
		int map_y = (int)game->player_y;

		double side_dist_x;
		double side_dist_y;

		double delta_dist_x = (ray_dir_x == 0) ? 1e30 : fabs(1 / ray_dir_x);
		double delta_dist_y = (ray_dir_y == 0) ? 1e30 : fabs(1 / ray_dir_y);

		double perp_wall_dist;

		int step_x;
		int step_y;

		int hit = 0;
		int side;

		if (ray_dir_x < 0)
		{
			step_x = -1;
			side_dist_x = (game->player_x - map_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (map_x + 1.0 - game->player_x) * delta_dist_x;
		}
		if (ray_dir_y < 0)
		{
			step_y = -1;
			side_dist_y = (game->player_y - map_y) * delta_dist_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (map_y + 1.0 - game->player_y) * delta_dist_y;
		}

		while (hit == 0)
		{
			if (side_dist_x < side_dist_y)
			{
				side_dist_x += delta_dist_x;
				map_x += step_x;
				side = 0;
			}
			else
			{
				side_dist_y += delta_dist_y;
				map_y += step_y;
				side = 1;
			}
			if (game->board->map[map_y][map_x] > 0)
				hit = 1;
		}
		if (side == 0)
			perp_wall_dist = side_dist_x - delta_dist_x;
		else
			perp_wall_dist = side_dist_y - delta_dist_y;

		int	line_height = (int)(512 / perp_wall_dist);
		printf("line_height: %d\n", line_height);
		printf("perp_wall_dist: %f\n", perp_wall_dist);
		int draw_start = -line_height / 2 + 512 / 2;
		if (draw_start < 0)
			draw_start = 0;
		int draw_end = line_height / 2 + 512 / 2;
		if (draw_end >= 512)
			draw_end = 512 - 1;
		int color = 0xFF0000;
		printf("x: %f\n", game->player_x);
		printf("y: %f\n", game->player_y);
		printf("draw_start: %d\n", draw_start);
		printf("draw_end: %d\n", draw_end);
		mlx_put_pixel(screen, draw_start, draw_end, color);
		x++;
	}
}
