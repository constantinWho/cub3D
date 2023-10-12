/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 16:19:22 by chustei           #+#    #+#             */
/*   Updated: 2023/10/12 09:43:18 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

int map_grid4[MAP_HEIGHT][MAP_WIDTH] = {
	{1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 1, 0, 0, 1},
	{1, 0, 1, 0, 1, 0, 0, 1},
	{1, 0, 1, 0, 1, 0, 1, 1},
	{1, 0, 1, 0, 1, 0, 0, 1},
	{1, 0, 1, 0, 1, 1, 0, 1},
	{1, 0, 1, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1}
};

static void	ft_move_player(t_game *game, int *px, int *py)
{
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
	{
		(*px) += cos(game->rotation_angle) * MOVE_SPEED;
		(*py) += sin(game->rotation_angle) * MOVE_SPEED;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
	{
		(*px) -= cos(game->rotation_angle) * MOVE_SPEED;
		(*py) -= sin(game->rotation_angle) * MOVE_SPEED;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
	{
		(*px) += cos(game->rotation_angle - PI / 2) * MOVE_SPEED;
		(*py) += sin(game->rotation_angle - PI / 2) * MOVE_SPEED;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
	{
		(*px) -= cos(game->rotation_angle - PI / 2) * MOVE_SPEED;
		(*py) -= sin(game->rotation_angle - PI / 2) * MOVE_SPEED;
	}
}

void	ft_keys(void *param)
{
	t_game		*game;
	int			new_player_x;
	int			new_player_y;

	game = param;
	new_player_x = game->player_x;
	new_player_y = game->player_y;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	ft_move_player(game, &new_player_x, &new_player_y);
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		game->rotation_angle -= 0.07;
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		game->rotation_angle += 0.07;
	if (map_grid4[new_player_y / 64][new_player_x / 64] == 0)
	{
		game->player_x = new_player_x;
		game->player_y = new_player_y;
	}
}
