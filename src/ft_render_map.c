/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 02:22:09 by chustei           #+#    #+#             */
/*   Updated: 2023/12/01 15:46:34 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	ft_render_player(t_game *game)
{
	int	i;
	int	j;

	i = -1;
	while (++i < 5)
	{
		j = -1;
		while (++j < 5)
			ft_put_pixel(game->world_map, (game->pos.y * 11 + i) - 2.5, \
			(game->pos.x * 11 + j) - 2.5, 0x00FF0080);
	}
}

void	ft_render_map(void *param)
{
	t_game	*game;
	int		i;
	int		j;

	game = param;
	i = -1;
	while (++i < (int)game->world_map->height)
	{
		j = -1;
		while (++j < (int)game->world_map->width)
		{
			if (!game->board->map[i / 11][j / 11])
				break ;
			if (game->board->map[i / 11][j / 11])
			{
				if (game->board->map[i / 11][j / 11] == '1')
					ft_put_pixel(game->world_map, j, i, 0xecf0f180);
				else
					ft_put_pixel(game->world_map, j, i, 0x2c3e5080);
			}
		}
	}
	ft_render_player(game);
}
