/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keys_listener.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 03:27:50 by chustei           #+#    #+#             */
/*   Updated: 2023/11/24 02:56:12 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	ft_rotate(t_game *g, double rs)
{
	if (mlx_is_key_down(g->mlx, MLX_KEY_RIGHT))
	{
		g->old_dir.x = g->dir.x;
		g->dir.x = g->dir.x * cos(-rs) - g->dir.y * sin(-rs);
		g->dir.y = g->old_dir.x * sin(-rs) + g->dir.y * cos(-rs);
		g->old_plane.x = g->plane.x;
		g->plane.x = g->plane.x * cos(-rs) - g->plane.y * sin(-rs);
		g->plane.y = g->old_plane.x * sin(-rs) + g->plane.y * cos(-rs);
	}
	if (mlx_is_key_down(g->mlx, MLX_KEY_LEFT))
	{
		g->old_dir.x = g->dir.x;
		g->dir.x = g->dir.x * cos(rs) - g->dir.y * sin(rs);
		g->dir.y = g->old_dir.x * sin(rs) + g->dir.y * cos(rs);
		g->old_plane.x = g->plane.x;
		g->plane.x = g->plane.x * cos(rs) - g->plane.y * sin(rs);
		g->plane.y = g->old_plane.x * sin(rs) + g->plane.y * cos(rs);
	}
}

static void	ft_move_y_axis(t_game *g, double ms)
{
	if (mlx_is_key_down(g->mlx, MLX_KEY_W))
	{
		if (g->board->map[(int)(g->pos.x + g->dir.x * ms)][(int)(g->pos.y)] == '0')
			g->pos.x += g->dir.x * ms;
		if (g->board->map[(int)(g->pos.x)][(int)(g->pos.y + g->dir.y * ms)] == '0')
			g->pos.y += g->dir.y * ms;
	}
	if (mlx_is_key_down(g->mlx, MLX_KEY_S))
	{
		if (g->board->map[(int)(g->pos.x - g->dir.x * ms)][(int)(g->pos.y)] == '0')
			g->pos.x -= g->dir.x * ms;
		if (g->board->map[(int)(g->pos.x)][(int)(g->pos.y - g->dir.y * ms)] == '0')
			g->pos.y -= g->dir.y * ms;
	}
}

static void	ft_move_x_axis(t_game *g, double ms)
{
	if (mlx_is_key_down(g->mlx, MLX_KEY_D))
	{
		if (g->board->map[(int)(g->pos.x + g->dir.y * ms)][(int)(g->pos.y)] == '0')
			g->pos.x += g->dir.y * ms;
		if (g->board->map[(int)(g->pos.x)][(int)(g->pos.y - g->dir.x * ms)] == '0')
			g->pos.y -= g->dir.x * ms;
	}
	if (mlx_is_key_down(g->mlx, MLX_KEY_A))
	{
		if (g->board->map[(int)(g->pos.x - g->dir.y * ms)][(int)(g->pos.y)] == '0')
			g->pos.x -= g->dir.y * ms;
		if (g->board->map[(int)(g->pos.x)][(int)(g->pos.y + g->dir.x * ms)] == '0')
			g->pos.y += g->dir.x * ms;
	}
}

static void	ft_move(t_game *game)
{
	ft_move_y_axis(game, game->move_speed);
	ft_move_x_axis(game, game->move_speed);
}

void	ft_keys_listener(void *param)
{
	t_game	*game;

	game = param;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		ft_end_game(game);
	ft_move(game);
	ft_rotate(game, game->rot_speed);
}
