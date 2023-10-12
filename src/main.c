/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 14:02:32 by chustei           #+#    #+#             */
/*   Updated: 2023/10/12 09:48:07 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

int32_t	main(void)
{
	t_game	game;

	game.mlx = mlx_init(HEIGHT, WIDTH, "cub3D", false);
	if (!game.mlx)
		exit(EXIT_FAILURE);
	game.player_x = 96;
	game.player_y = 96;
	game.rotation_angle = 0.0;
	game.map = mlx_new_image(game.mlx, 512, 512);
	game.screen = mlx_new_image(game.mlx, 512, 512);
	mlx_image_to_window(game.mlx, game.map, 0, 0);
	mlx_image_to_window(game.mlx, game.screen, 512, 0);
	mlx_loop_hook(game.mlx, &ft_render, &game.mlx);
	mlx_loop_hook(game.mlx, &ft_keys, &game.mlx);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	return (EXIT_SUCCESS);
}
