/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 16:13:45 by chustei           #+#    #+#             */
/*   Updated: 2023/11/06 16:49:19 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

static void	ft_init_ray(t_game *game, int x)
{
	game->camera_x = 2 * x / (double)512 - 1;
	game->ray_dir_x = game->direction_x + game->plane_x * game->camera_x;
	game->ray_dir_y = game->direction_y + game->plane_y * game->camera_x;
	game->map_x = (int)game->player_x;
	game->map_y = (int)game->player_y;
}

void	set_delta_dist(t_game *game)
{
	if (game->ray_dir_x == 0)
		game->delta_dist_x = 1e30;
	else
		game->delta_dist_x = fabs(1 / game->ray_dir_x);
	if (game->ray_dir_y == 0)
		game->delta_dist_y = 1e30;
	else
		game->delta_dist_y = fabs(1 / game->ray_dir_y);
}

static void	set_ray_delta(t_game *game)
{
	set_delta_dist(game);
	if (game->ray_dir_x < 0)
	{
		game->step_x = -1;
		game->side_dist_x = (game->player_x - game->map_x) * game->delta_dist_x;
	}
	else
	{
		game->step_x = 1;
		game->side_dist_x = (game->map_x + 1.0 - game->player_x) * game->delta_dist_x;
	}
	if (game->ray_dir_y < 0)
	{
		game->step_y = -1;
		game->side_dist_y = (game->player_y - game->map_y) * game->delta_dist_y;
	}
	else
	{
		game->step_y = 1;
		game->side_dist_y = (game->map_y + 1.0 - game->player_y) * game->delta_dist_y;
	}
}

static void	perform_dda(t_game *game, char *world_map[])
{
	while (true)
	{
		if (game->side_dist_x < game->side_dist_y)
		{
			game->side_dist_x += game->delta_dist_x;
			game->map_x += game->step_x;
			game->side = NS;
		}
		else
		{
			game->side_dist_y += game->delta_dist_y;
			game->map_y += game->step_y;
			game->side = NS;
		}
		if (world_map[game->map_y / (int)game->tile_size][game->map_x / (int)game->tile_size] == '1')
			break ;
	}
}

static void	calculate_height(t_game *game)
{
	if (game->side == EW)
		game->perp_wall_dist = game->side_dist_x - game->delta_dist_x;
	else
		game->perp_wall_dist = game->side_dist_y - game->delta_dist_y;
	game->line_height = (int)(512 / game->perp_wall_dist);
	game->draw_start = 512 / 2 - game->line_height / 2;
	if (game->draw_start < 0)
		game->draw_start = 0;
	game->draw_end = game->line_height / 2 + 512 / 2;
	if (game->draw_end >= (int) 512)
		game->draw_end = 512 - 1;
}

void	draw_wall(t_game *game, int x, mlx_image_t *screen)
{
	int	y_wall;

	y_wall = game->draw_start;
	while (y_wall <= game->draw_end)
	{
		mlx_put_pixel(screen, x, y_wall, 0x00FF0000);
		y_wall++;
	}
}

void	ft_raycaster(t_game *game, mlx_image_t *map, mlx_image_t *screen)
{
	int	x;

	x = 0;
	(void)map;
	while (x < (int)screen->width)
	{
		ft_init_ray(game, x);
		set_ray_delta(game);
		perform_dda(game, game->board->map);
		calculate_height(game);
		draw_wall(game, x, screen);
		x++;
	}
}
