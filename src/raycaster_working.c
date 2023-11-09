/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_working.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 21:07:04 by chustei           #+#    #+#             */
/*   Updated: 2023/11/08 12:33:21 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

/* unsigned int    get_color_textel(t_cub *cub, int x, int y)
{
    unsigned int    *color;
    unsigned int    index;
    index = (y * cub->chosen_texture->width + x) * 4;
    color = (unsigned int *) &(cub->chosen_texture->pixels[index]);
    return (*color);
} */
/* void    put_textel(mlx_image_t *img, int x, int y, unsigned int colour)
{
    unsigned int    *pixel;
    if (x < img->width && y < img->height)
    {
        pixel = (unsigned int *)&img->pixels[(x + y * img->width) * 4];
        *pixel = colour;
    }
} */
/**
 * Delta is the distance
 * the ray has to travel to go from 1 x-side to the next x-side,
 * or from 1 y-side to the next y-side.
 */
void    set_delta_dist(t_game *game)
{
    if (game->ray.x == 0)
        game->delta_dist_x = 1e30;
    else
        game->delta_dist_x = fabs(1 / game->ray.x);
    if (game->ray.y == 0)
        game->delta_dist_y = 1e30;
    else
        game->delta_dist_y = fabs(1 / game->ray.y);
}
void    calc_step(t_game *game)
{
    if (game->ray.x < 0)
    {
        game->step_x = -1;
        game->side_dist_x = (game->board->map_px - game->map_x) * \
                            game->delta_dist_x;
    }
    else
    {
        game->step_x = 1;
        game->side_dist_x = (game->map_x + 1.0 - game->board->map_px) * \
                            game->delta_dist_x;
    }
    if (game->ray.y < 0)
    {
        game->step_y = -1;
        game->side_dist_y = (game->board->map_py - game->map_y) * \
                            game->delta_dist_y;
    }
    else
    {
        game->step_y = 1;
        game->side_dist_y = (game->map_y + 1.0 - game->board->map_py) * \
                            game->delta_dist_y;
    }
}
/* void    choose_texture(t_cub *cub)
{
    if (cub->side == 0 && cub->step.x < 0)
        cub->chosen_texture = cub->map.east;
    if (cub->side == 0 && cub->step.x > 0)
        cub->chosen_texture = cub->map.west;
    if (cub->side == 1 && cub->step.y < 0)
        cub->chosen_texture = cub->map.north;
    if (cub->side == 1 && cub->step.y > 0)
        cub->chosen_texture = cub->map.south;
} */
/*
void    apply_texture(t_cub *cub, int x)
{
    double  step;
    double  tex_pos;
    int     y;
    step = 1.0 * cub->chosen_texture->height / cub->line_h;
    tex_pos = (cub->draw_start - cub->mlx->height / 2 + cub->line_h / 2) * step;
    y = cub->draw_start - 1;
    while (++y <= cub->draw_end)
    {
        cub->tex.y = (int)tex_pos ;
        if (cub->tex.y >= cub->chosen_texture->height)
            cub->tex.y = (int)(cub->chosen_texture->height - 1);
        tex_pos += step;
        put_textel(cub->img, x, y, \
                get_color_textel(cub, cub->tex.x, cub->tex.y));
    }
} */
/**
 * Where exactly the wall was hit
 */
void    measure_texture(t_cub *cub)
{
    if (cub->side == 0)
        cub->wall_x = cub->player.pos.y + cub->perp_wall_dist * cub->ray.y;
    else
        cub->wall_x = cub->player.pos.x + cub->perp_wall_dist * cub->ray.x;
    cub->wall_x -= floor(cub->wall_x);
    cub->tex.x = (int)(cub->wall_x * (double)cub->chosen_texture->width);
    if (cub->side == 0 && cub->ray.x > 0)
        cub->tex.x = cub->chosen_texture->width - cub->tex.x - 1;
    if (cub->side == 1 && cub->ray.y < 0)
        cub->tex.x = cub->chosen_texture->width - cub->tex.x - 1;
}
/**
 * Calculate distance of perpendicular ray.
 * Calculate lowest and highest pixel to fill in current stripe
 */
void    dist_to_line_height(t_game *game)
{
    if (game->side == 0)
        game->perp_wall_dist = game->side_dist_x - game->delta_dist_x;
    else
        game->perp_wall_dist = game->side_dist_y - game->delta_dist_y;
    game->line_h = (int)(game->mlx->height / game->perp_wall_dist);
    game->draw_start = game->mlx->height / 2 - game->line_h / 2;
    if (game->draw_start < 0)
        game->draw_start = 0;
    game->draw_end = game->line_h / 2 + game->mlx->height / 2;
    if (game->draw_end >= game->mlx->height)
        game->draw_end = game->mlx->height - 1;
}
/**
 * The DDA algorithm will always jump exactly one square each loop,
 * either a square in the x-direction, or a square in the y-direction.
 * If it has to go in the negative or positive x-direction,
 * and the negative or positive y-direction will depend on the direction
 * of the ray, and this fact will be stored in stepX and stepY.
 * Those variables are always either -1 or +1.
 * */
void    dda_loop(t_game *game)
{
    while (game->hit == 0)
    {
        if (game->side_dist_x < game->side_dist_y)
        {
            game->side_dist_x += game->delta_dist_x;
            game->map_x += game->step_x;
            game->side = 0;
        }
        else
        {
            game->side_dist_y += game->delta_dist_y;
            game->map_y += game->step_y;
            game->side = 1;
        }
        if (game->board->map[game->map_y * game->map_x + game->map_x] > 0)
            game->hit = 1;
    }
}
void    ft_raycaster(t_game *game, mlx_image_t *map, mlx_image_t *screen)
{
    (void)map;
    double  camera_x;
    int     x;
    x = -1;
    while (++x < game->mlx->width)
    {
        camera_x = 2 * x / 512 - 1;
        game->ray.x = game->dir_x + game->plane_x * camera_x;
        game->ray.y = game->dir_y + game->plane_y * camera_x;
        game->map_x = (int) game->board->map_px;
        game->map_y = (int) game->board->map_py;
        set_delta_dist(game);
        game->hit = 0;
        calc_step(game);
        dda_loop(game);
        dist_to_line_height(game);

        choose_texture(game);
        measure_texture(game);
        apply_texture(game, x);
        int y = game->draw_start - 1;
        while (++y <= game->draw_end)
        {
            mlx_put_pixel(screen, x, y, 0x00FF0000);
        }
    }
}
