/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 15:41:20 by chustei           #+#    #+#             */
/*   Updated: 2023/10/12 09:44:12 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

int map_grid2[MAP_HEIGHT][MAP_WIDTH] = {
	{1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 1, 0, 0, 1},
	{1, 0, 1, 0, 1, 0, 0, 1},
	{1, 0, 1, 0, 1, 0, 1, 1},
	{1, 0, 1, 0, 1, 0, 0, 1},
	{1, 0, 1, 0, 1, 1, 0, 1},
	{1, 0, 1, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1}
};

static void	ft_color_map(mlx_image_t *map)
{
	int	i;
	int	y;

	i = 0;
	while (i < (int)map->width)
	{
		y = 0;
		while (y < (int)map->height)
		{
			if (i % 64 == 0 || y % 64 == 0)
				mlx_put_pixel(map, i, y, 0x40739eFF);
			else if (map_grid2[y / 64][i / 64] == 1)
				mlx_put_pixel(map, i, y, 0x00a8ffFF);
			y++;
		}
		i++;
	}
}

static void	ft_color_ceiling(mlx_image_t *screen)
{
	int	i;
	int	y;

	i = 0;
	while (i < (int)screen->width)
	{
		y = 0;
		while (y < (int)screen->height / 2)
		{
			mlx_put_pixel(screen, i, y, CEILING_COLOR);
			y++;
		}
		i++;
	}
}

static void	ft_color_floor(mlx_image_t *screen)
{
	int	i;
	int	y;

	i = 0;
	while (i < (int)screen->width)
	{
		y = (int)screen->height / 2;
		while (y < (int)screen->height)
		{
			mlx_put_pixel(screen, i, y, FLOOR_COLOR);
			y++;
		}
		i++;
	}
}

static void	ft_draw_player_on_the_map(mlx_image_t *map, int px, int py)
{
	int	i;
	int	y;

	i = 0;
	while (i < 8)
	{
		y = 0;
		while (y < 8)
		{
			mlx_put_pixel(map, i + px - 4, y + py - 4, 0x44bd32FF);
			y++;
		}
		i++;
	}
}

void	ft_render(void *param)
{
	t_game		*game;
	mlx_image_t	*map;
	mlx_image_t	*screen;

	game = param;
	map = game->map;
	screen = game->screen;
	ft_memset(map->pixels, 0x2f3640FF, map->height * map->width * BPP);
	ft_memset(screen->pixels, 0, screen->height * screen->width * BPP);
	ft_color_map(map);
	ft_color_ceiling(screen);
	ft_color_floor(screen);
	ft_raycaster(game, map, screen);
	ft_draw_player_on_the_map(map, game->player_x, game->player_y);
}
