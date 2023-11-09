/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 16:13:45 by chustei           #+#    #+#             */
/*   Updated: 2023/11/09 13:40:05 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

void	ft_get_ray_distance(t_game *game, t_ray *ray, double *dist, double *max)
{
	(void)game;
	while ((game->board->map[(int)(ray->y / (int)game->tile_size)][(int)(ray->x / (int)game->tile_size)] == '0' \
		 || game->board->map[(int)ray->y / (int)game->tile_size][(int)ray->x / (int)game->tile_size] == game->board->map_face) && *dist < *max)
	{
		ray->x += cos(ray->angle);
		ray->y += sin(ray->angle);
		(*dist) += 1;
	}
}

void ft_init_ray_vars(t_game *game, t_ray *ray, mlx_image_t *screen, double ray_distance)
{
	double	wall_height;
	double	wall_center;

	ray->perp_distance = ray_distance * cos(ray->angle - game->rotation_angle);
	wall_height = (game->tile_size / ray->perp_distance) * screen->height;
	wall_center = 0.5 * screen->height;
	ray->wall_top = (int)(wall_center - wall_height * 0.5);
	ray->wall_bottom = (int)(wall_center + wall_height * 0.5);
	if (ray->wall_top < 0)
		ray->wall_top = 0;
	if (ray->wall_bottom >= screen->height)
		ray->wall_bottom = screen->height - 1;
	ray->row = ray->wall_top;
	ray->column = (int)(((ray->angle - (game->rotation_angle - FOV / 2)) / FOV) * screen->width);
}

void	ft_put_rays_map(t_game *game, t_ray *ray, mlx_image_t *map, double dist)
{
	int	i;

	i = 0;
	while (i < dist)
	{
		ray->x = game->player_x + i * cos(ray->angle);
		ray->y = game->player_y + i * sin(ray->angle);
		mlx_put_pixel(map, ray->x, ray->y, 0x8c7ae6FF);
		i++;
	}
}

void	ft_draw_wall(t_game *game, t_ray *ray)
{
	while (ray->row < ray->wall_bottom)
	{
		if ((ray->row >= 0 && ray->row < (int)game->screen->height))
			mlx_put_pixel(game->screen, ray->column, ray->row, 0x8c7346FF);
		ray->row++;
	}
}

void	ft_calc_steps(t_game *game, t_ray *ray)
{
		game->delta_x = fabs(1 / ray->direction_x);
		game->delta_y = fabs(1 / ray->direction_y);
		if (ray->direction_x < 0)
		{
			game->step_x = -1;
			game->side_dist_x = (ray->x - (int)ray->x) * game->delta_x;
		}
		else
		{
			game->step_x = 1;
			game->side_dist_x = (1 - (ray->x - (int)ray->x)) * game->delta_x;
		}
		if (ray->direction_y < 0)
		{
			game->step_y = -1;
			game->side_dist_y = (ray->y - (int)ray->y) * game->delta_y;
		}
		else
		{
			game->step_y = 1;
			game->side_dist_y = (1 - (ray->y - (int)ray->y)) * game->delta_y;
		}
}

void	ft_dda(t_game *game, t_ray *ray)
{
	while (game->board->map[(int)ray->y / (int)game->tile_size][(int)ray->x / (int)game->tile_size] != '1')
	{
		if (game->side_dist_x < game->side_dist_y)
		{
			game->side_dist_x += game->delta_x;
			ray->x += game->step_x;
		}
		else
		{
			game->side_dist_y += game->delta_y;
			ray->y += game->step_y;
		}
	}
}

void ft_raycaster(t_game *game, mlx_image_t *map, mlx_image_t *screen)
{
	t_ray	ray;
	int		i;
	double	max_line_length;
	double	ray_distance;

	i = 0;
	max_line_length = sqrt(pow(map->width, 2) + pow(map->height, 2));
	ray.angle = game->rotation_angle - PI / 6;
	while (ray.angle < game->rotation_angle + FOV / 2)
	{
		ray.direction_x = cos(ray.angle);
		ray.direction_y = sin(ray.angle);
		ray.y = game->player_y;
		ray.x = game->player_x;
		ft_calc_steps(game, &ray);
		ft_dda(game, &ray);
		ray_distance = sqrt(pow(ray.x - game->player_x, 2) + pow(ray.y - game->player_y, 2));
		ft_put_rays_map(game, &ray, map, ray_distance);
		ft_init_ray_vars(game, &ray, screen, ray_distance);
		ft_draw_wall(game, &ray);
		ray.angle += 0.0005;
	}
}
