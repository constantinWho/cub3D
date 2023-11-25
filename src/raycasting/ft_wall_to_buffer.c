/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wall_to_buffer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 14:02:32 by chustei           #+#    #+#             */
/*   Updated: 2023/11/25 03:34:04 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	ft_init_rays(t_game *game, int x)
{
	game->camera.x = 2 * x / (double)WIDTH - 1;
	game->ray_dir.x = game->dir.x + game->plane.x * game->camera.x;
	game->ray_dir.y = game->dir.y + game->plane.y * game->camera.x;
	game->map.x = (int)game->pos.x;
	game->map.y = (int)game->pos.y;
	if (game->ray_dir.x == 0)
		game->delta_dist.x = 1e30;
	else
		game->delta_dist.x = fabs(1 / game->ray_dir.x);
	if (game->ray_dir.y == 0)
		game->delta_dist.y = 1e30;
	else
		game->delta_dist.y = fabs(1 / game->ray_dir.y);
	game->hit = 0;
}

void	ft_get_tex_x(t_game *game, int *tex_x)
{
	(*tex_x) = (int)(game->wall_x * (double)TEX_WIDTH);
	if (game->side == 0 && game->ray_dir.x > 0)
		(*tex_x) = TEX_WIDTH - *tex_x - 1;
	if (game->side == 1 && game->ray_dir.y < 0)
		(*tex_x) = TEX_WIDTH - *tex_x - 1;
}

void	ft_get_tex_pixels(t_game *game, int y, int x, int tex_x)
{
	double	step;
	double	tex_pos;
	int		tex_y;
	t_point	cord;

	step = 1.0 * TEX_HEIGHT / game->line_height;
	tex_pos = (game->draw_start - HEIGHT / 2 + game->line_height / 2) * step;
	y = game->draw_start - 1;
	while (++y < game->draw_end)
	{
		tex_y = (int)tex_pos & (TEX_HEIGHT - 1);
		tex_pos += step;
		cord.x = tex_x;
		cord.y = tex_y;
		if (game->side == 0 && game->ray_dir.x > 0)
			game->color = (uint32_t)get_image_color(game->south, cord);
		else if (game->side == 0)
			game->color = (uint32_t)get_image_color(game->north, cord);
		else if (game->ray_dir.y > 0)
			game->color = (uint32_t)get_image_color(game->east, cord);
		else
			game->color = (uint32_t)get_image_color(game->west, cord);
		game->buffer[y][x] = game->color;
	}
}

void	ft_wall_to_buffer(t_game *game)
{
	int	x;
	int	y;
	int	tex_x;

	y = -1;
	x = -1;
	while (++x < WIDTH)
	{
		ft_init_rays(game, x);
		ft_calc_step_and_side_dist(game);
		ft_dda(game);
		ft_calc_lines(game);
		ft_get_tex_x(game, &tex_x);
		ft_get_tex_pixels(game, y, x, tex_x);
	}
}
