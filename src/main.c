/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 14:02:32 by chustei           #+#    #+#             */
/*   Updated: 2023/10/12 15:05:53 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

static void init_board(t_board *board)
{
	board->no = NULL;
	board->so = NULL;
	board->we = NULL;
	board->ea = NULL;
	board->c = NULL;
	board->f = NULL;
	board->fd = 0;
	board->flag = 0;
	board->width = 0;
	board->height = 0;
	board->map = NULL;
}

void print_struc(t_board *board)
{
	printf("board->no: %s", board->no );
	printf("board->so: %s", board->so);
	printf("board->we: %s", board->we);
	printf("board->ea: %s", board->ea);
	printf("board->width: %d\n", board->width);
	printf("board->height: %d\n", board->height);
 	int j;
	j = 0;
	if (board->f)
	{
		while (j < 3)
		{
			printf("board->f[%d]: %d\n", j, board->f[j]);
			j++;
		}
	}
	j = 0;
	if (board->c)
	{
		while (j < 3)
		{
			printf("board->c[%d]: %d\n", j, board->c[j]);
			j++;
		}
	}
	j = 0;
	if (board->map)
	{
		while (board->map[j])
		{
			printf("board->map[%d]: %s", j, board->map[j]);
			j++;
		}
	}
}

int32_t	main(int argc, char **argv)
{
	t_game	game;
	char	*sub;

	if (argc != 2)
		die("Invalid number of arguments!", 0);
	sub = ft_substr(argv[1], ft_strlen(argv[1]) - 4, 5);
	if (ft_strncmp(sub, ".cub", 5) != 0)
	{
		free(sub);
		die("Invalid file type, use .cub!", 0);
	}
	free(sub);
	game.board = malloc(sizeof(t_board));
	if (!game.board)
			return (ft_error(NULL, "malloc init\n", 0));
	init_board(game.board);
	game.board->fd = open(argv[1], O_RDONLY);
	if (game.board->fd < 0)
		return (ft_error(game.board, "File doesn't exit\n", 1));
	map_reading(game.board);
	print_struc(game.board);
	check_empty_lines(game.board);
	print_struc(game.board);
	check_identifier_factor(game.board->no);
	check_identifier_factor(game.board->so);
	check_identifier_factor(game.board->we);
	check_identifier_factor(game.board->ea);
 	check_map_walls(game.board);
	print_struc(game.board);
	/* ++++++++++++++++++++++++++++++++++++++++++++++++ */
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
