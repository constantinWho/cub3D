/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 03:27:50 by chustei           #+#    #+#             */
/*   Updated: 2023/11/24 02:55:03 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

uint32_t	get_image_color(mlx_texture_t *texture, t_point p)
{
	uint32_t	color;
	uint32_t	index;

	index = ((p.y % texture->height) * texture->width + (p.x % texture->width))
		* sizeof(uint32_t);
	color = texture->pixels[index] << 24;
	color |= texture->pixels[index + 1] << 16;
	color |= texture->pixels[index + 2] << 8;
	color |= 0x000000FF;
	return (color);
}

void	ft_calc_step_and_side_dist(t_game *game)
{
	if (game->ray_dir.x < 0)
	{
		game->step.x = -1;
		game->side_dist.x = (game->pos.x - game->map.x) * game->delta_dist.x;
	}
	else
	{
		game->step.x = 1;
		game->side_dist.x = (game->map.x + 1.0 - game->pos.x) * \
			game->delta_dist.x;
	}
	if (game->ray_dir.y < 0)
	{
		game->step.y = -1;
		game->side_dist.y = (game->pos.y - game->map.y) * game->delta_dist.y;
	}
	else
	{
		game->step.y = 1;
		game->side_dist.y = (game->map.y + 1.0 - game->pos.y) * \
			game->delta_dist.y;
	}
}

void	ft_dda(t_game *game)
{
	while (game->hit == 0)
	{
		if (game->side_dist.x < game->side_dist.y)
		{
			game->side_dist.x += game->delta_dist.x;
			game->map.x += game->step.x;
			game->side = 0;
		}
		else
		{
			game->side_dist.y += game->delta_dist.y;
			game->map.y += game->step.y;
			game->side = 1;
		}
		if (game->board->map[game->map.x][game->map.y] != '0')
			game->hit = 1;
	}
}

void	ft_calc_lines(t_game *game)
{
	if (game->side == 0)
		game->perp_wall_dist = (game->side_dist.x - game->delta_dist.x);
	else
		game->perp_wall_dist = (game->side_dist.y - game->delta_dist.y);
	game->line_height = (int)(HEIGHT / game->perp_wall_dist);
	game->draw_start = -game->line_height / 2 + HEIGHT / 2;
	if (game->draw_start < 0)
		game->draw_start = 0;
	game->draw_end = game->line_height / 2 + HEIGHT / 2;
	if (game->draw_end >= HEIGHT)
		game->draw_end = HEIGHT - 1;
	if (game->side == 0)
		game->wall_x = game->pos.y + game->perp_wall_dist * game->ray_dir.y;
	else
		game->wall_x = game->pos.x + game->perp_wall_dist * game->ray_dir.x;
	game->wall_x -= floor((game->wall_x));
}
