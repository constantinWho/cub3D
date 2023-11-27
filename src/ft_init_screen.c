/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_screen.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 02:13:59 by chustei           #+#    #+#             */
/*   Updated: 2023/11/25 03:04:11 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	ft_strwrap(t_board *board)
{
	board->no = ft_strtrim(board->no, "\n");
	board->so = ft_strtrim(board->so, "\n");
	board->we = ft_strtrim(board->we, "\n");
	board->ea = ft_strtrim(board->ea, "\n");
}

static void	ft_load_textures(t_game *game)
{
	game->north = mlx_load_png(game->board->no);
	game->south = mlx_load_png(game->board->so);
	game->west = mlx_load_png(game->board->we);
	game->east = mlx_load_png(game->board->ea);
	if (!game->north || !game->south || !game->west || !game->east)
		ft_error(game->board, "textures wrong", 1);;
}

/* void	ft_check_path_textures(t_game *game)
{
	printf("%s\n", game->board->no);
	if (open(game->board->no, O_RDONLY) < 0)
		ft_error(game->board, "North textures wrong", 1);
	if (open(game->board->so, O_RDONLY) < 0)
		ft_error(game->board, "South textures wrong", 1);
	if (open(game->board->we, O_RDONLY) < 0)
		ft_error(game->board, "West textures wrong", 1);
	if (open(game->board->ea, O_RDONLY) < 0)
		ft_error(game->board, "East textures wrong", 1);
} */

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
	ft_strwrap(g->board);
	ft_load_textures(g);
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