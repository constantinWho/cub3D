/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_end_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 16:53:26 by chustei           #+#    #+#             */
/*   Updated: 2023/12/01 15:50:20 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_end_game(t_game *game)
{
	int	i;

	i = -1;
	mlx_delete_texture(game->north);
	mlx_delete_texture(game->south);
	mlx_delete_texture(game->west);
	mlx_delete_texture(game->east);
	mlx_delete_image(game->mlx, game->screen);
	mlx_delete_image(game->mlx, game->world_map);
	mlx_close_window(game->mlx);
	if (game->buffer)
	{
		while (++i < HEIGHT)
			free(game->buffer[i]);
	}
	free(game->buffer);
}
