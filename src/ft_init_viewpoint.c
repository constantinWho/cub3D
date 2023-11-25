/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_viewpoint.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 02:13:59 by chustei           #+#    #+#             */
/*   Updated: 2023/11/25 03:04:11 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	ft_add_viepoint_dir(t_game *game, double dir_x, double dir_y)
{
	game->dir.x = dir_x;
	game->dir.y = dir_y;
}

static void	ft_add_viepoint_plane(t_game *game, double plane_x, double plane_y)
{
	game->plane.x = plane_x;
	game->plane.y = plane_y;
}

void	ft_set_viewpoint(t_game *game)
{
	if (game->board->map_face == 'N')
	{
		ft_add_viepoint_dir(game, -1, 0);
		ft_add_viepoint_plane(game, 0, 0.66);
	}
	else if (game->board->map_face == 'S')
	{
		ft_add_viepoint_dir(game, 1, 0);
		ft_add_viepoint_plane(game, 0, -0.66);
	}
	else if (game->board->map_face == 'E')
	{
		ft_add_viepoint_dir(game, 0, 1);
		ft_add_viepoint_plane(game, 0.66, 0);
	}
	else if (game->board->map_face == 'W')
	{
		ft_add_viepoint_dir(game, 0, -1);
		ft_add_viepoint_plane(game, -0.66, 0);
	}
}
