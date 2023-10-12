/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 16:13:45 by chustei           #+#    #+#             */
/*   Updated: 2023/10/12 10:23:47 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

int map_grid3[MAP_HEIGHT][MAP_WIDTH] = {
	{1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 1, 0, 0, 1},
	{1, 0, 1, 0, 1, 0, 0, 1},
	{1, 0, 1, 0, 1, 0, 1, 1},
	{1, 0, 1, 0, 1, 0, 0, 1},
	{1, 0, 1, 0, 1, 1, 0, 1},
	{1, 0, 1, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1}
};

void	ft_init_ray_vars(t_game *game, t_ray *ray, \
	mlx_image_t *screen, double dist)
{
	ray->perp_distance = dist * cos(ray->angle - game->rotation_angle);
	ray->wall_height = (screen->height / ray->perp_distance) * 64;
	ray->wall_top = (screen->height - ray->wall_height) / 2;
	ray->wall_bottom = (screen->height + ray->wall_height) / 2;
	ray->row = ray->wall_top;
	ray->column = (int)(((ray->angle - (game->rotation_angle - FOV / 2)) / FOV) \
		* screen->width);
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

static void	ft_get_ray_distance(t_ray *ray, double *dist, double *max)
{
	while (map_grid3[(int)(ray->y / 64)][(int)(ray->x / 64)] == 0 \
		&& *dist < *max)
	{
		ray->x += cos(ray->angle);
		ray->y += sin(ray->angle);
		(*dist) += 1.0;
	}
}

static void	ft_draw_wall(t_game *game, t_ray *ray)
{
	while (ray->row < ray->wall_bottom)
	{
		if (ray->row >= 0 && ray->row < (int)game->screen->height)
			mlx_put_pixel(game->screen, ray->column, ray->row, 0x3a4b48FF);
		(ray->row)++;
	}
}

void	ft_raycaster(t_game *game, mlx_image_t *map, mlx_image_t *screen)
{
	t_ray	ray;
	int		i;
	double	max_line_length;
	double	ray_distance;

	i = 0;
	ray = game->ray;
	max_line_length = sqrt(pow(map->width, 2) + pow(map->height, 2));
	ray.angle = game->rotation_angle - PI / 6;
	while (ray.angle < game->rotation_angle + FOV / 2)
	{
		ray.x = game->player_x;
		ray.y = game->player_y;
		ray_distance = 0;
		ft_get_ray_distance(&ray, &ray_distance, &max_line_length);
		ft_put_rays_map(game, &ray, map, ray_distance);
		ft_init_ray_vars(game, &ray, screen, ray_distance);
		ft_draw_wall(game, &ray);
		ray.angle += 0.002;
	}
}
