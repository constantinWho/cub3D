/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_screen.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 02:13:59 by chustei           #+#    #+#             */
/*   Updated: 2023/11/29 04:34:45 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_init_screen(t_game *g)
{
	int	i;

	g->screen = mlx_new_image(g->mlx, WIDTH, HEIGHT);
	if (!g->screen)
		exit(EXIT_FAILURE);
	g->pos.x = g->board->map_py + 0.5;
	g->pos.y = g->board->map_px + 0.5;
	ft_set_viewpoint(g);
	g->move_speed = 0.08;
	g->rot_speed = 0.04;
	i = -1;
	g->buffer = ft_calloc((HEIGHT), sizeof(uint8_t *));
	while (++i < HEIGHT)
		g->buffer[i] = ft_calloc((WIDTH), sizeof(uint8_t *));
	g->world_map = mlx_new_image(g->mlx, g->board->width * 11, \
		g->board->height * 11);
	if (!g->world_map)
		exit(EXIT_FAILURE);
	mlx_image_to_window(g->mlx, g->screen, 0, 0);
	mlx_image_to_window(g->mlx, g->world_map, 0, 0);
}
