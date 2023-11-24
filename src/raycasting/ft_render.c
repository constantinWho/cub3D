/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 14:02:32 by chustei           #+#    #+#             */
/*   Updated: 2023/11/24 01:46:43 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

uint32_t	ft_rgb_to_hex(int *rgb)
{
	uint32_t	color;

	color = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
	color = (color << 8) | 0xFF;
	return (color);
}

static void	ft_background_to_buffer(t_game *game)
{
	int	x;
	int	y;

	y = HEIGHT / 2 -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
			game->buffer[y][x] = ft_rgb_to_hex(game->board->f);
	}
	y = -1;
	while (++y < HEIGHT / 2)
	{
		x = -1;
		while (++x < WIDTH)
			game->buffer[y][x] = ft_rgb_to_hex(game->board->c);
	}
}

static void	ft_buffer_to_screen(t_game *game)
{
	int		x;
	int		y;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
			mlx_put_pixel(game->screen, x, y, game->buffer[y][x]);
	}
	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
			game->buffer[y][x] = 0;
	}
}

void	ft_render(void *param)
{
	t_game	*game;

	game = param;
	ft_bzero(game->screen->pixels, WIDTH * HEIGHT * sizeof(uint32_t));
	ft_background_to_buffer(game);
	ft_wall_to_buffer(game);
	ft_buffer_to_screen(game);
}
