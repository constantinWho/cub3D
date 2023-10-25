/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 15:41:20 by chustei           #+#    #+#             */
/*   Updated: 2023/10/24 15:42:32 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

static void	ft_color_map(t_game *game, int tile_size)
{
	int	i;
	int	y;

	i = 0;
	while (i < (int)game->map->width)
	{
		y = 0;
		while (y < (int)game->map->height)
		{
			if (i % tile_size == 0 || y % tile_size == 0)
				mlx_put_pixel(game->map, i, y, 0x40739eFF);
			else
			{
				if (i < game->board->width * tile_size && y < game->board->height * tile_size)
				{
					if (game->board->map[y / tile_size][i / tile_size] == '0' ||
						game->board->map[y / tile_size][i / tile_size] == game->board->map_face)
						mlx_put_pixel(game->map, i, y, CEILING_COLOR);
					else
						mlx_put_pixel(game->map, i, y, FLOOR_COLOR);
				}
			}
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

static void	ft_draw_player_on_the_map(mlx_image_t *map, int px, int py, int ts)
{
	int	i;
	int	y;

	i = 0;
	(void)ts;
	while (i < 1)
	{
		y = 0;
		while (y < 1)
		{
			mlx_put_pixel(map, i + px - 1, y + py - 1, 0x44bd32FF);
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
	game->tile_size = 512.0 / (double)ft_strlen(game->board->map[0]);
	ft_memset(map->pixels, 0x2f3640FF, map->height * map->width * BPP);
	ft_memset(screen->pixels, 0, screen->height * screen->width * BPP);
	ft_color_map(game, game->tile_size);
	ft_color_ceiling(screen);
	ft_color_floor(screen);
	ft_raycaster(game, map, screen);
	ft_draw_player_on_the_map(map, game->player_x, game->player_y, game->tile_size);
}
