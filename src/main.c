/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 14:02:32 by chustei           #+#    #+#             */
/*   Updated: 2023/11/25 03:07:35 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

static void	init_board(t_board *board)
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
	board->map_face = 'X';
	board->map_px = 0;
	board->map_py = 0;
}

static int	check_map_face(t_board *board)
{
	int		found;
	double	y;
	double	x;

	y = -1;
	found = 0;
	while (board->map[(int)++y])
	{
		x = -1;
		while (board->map[(int)y][(int)++x])
		{
			if (board->map[(int)y][(int)x] == 'N' || \
				board->map[(int)y][(int)x] == 'S' || \
				board->map[(int)y][(int)x] == 'E' || \
				board->map[(int)y][(int)x] == 'W')
			{
				found++;
				board->map_face = board->map[(int)y][(int)x];
				board->map[(int)y][(int)x] = '0';
				board->map_px = x;
				board->map_py = y;
			}
		}
	}
	return (found);
}

static void	ft_parser(t_game *game, char **argv)
{
	game->board = malloc(sizeof(t_board));
	if (!game->board)
		ft_error(NULL, "malloc init\n", 0);
	init_board(game->board);
	game->board->fd = open(argv[1], O_RDONLY);
	if (game->board->fd < 0)
		ft_error(game->board, "File doesn't exit\n", 1);
	map_reading(game->board);
	check_empty_lines(game->board);
	check_identifier_factor(game->board->no);
	check_identifier_factor(game->board->so);
	check_identifier_factor(game->board->we);
	check_identifier_factor(game->board->ea);
	check_map_walls(game->board);
	if (check_map_face(game->board) != 1)
		ft_error(game->board, "Player doesn't exist\n", 1);
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
	ft_parser(&game, argv);
	game.mlx = mlx_init(WIDTH, HEIGHT, "cub3d", false);
	if (!game.mlx)
		exit(EXIT_FAILURE);
	ft_init_screen(&game);
	mlx_loop_hook(game.mlx, &ft_render, &game);
	mlx_loop_hook(game.mlx, &ft_render_map, &game);
	mlx_loop_hook(game.mlx, &ft_keys_listener, &game);
	mlx_loop(game.mlx);
	ft_end_game(&game);
	exit(EXIT_SUCCESS);
}

/* void print_struc(t_board *board)
{
	printf("board->no: %s", board->no );
	printf("board->so: %s", board->so);
	printf("board->we: %s", board->we);
	printf("board->ea: %s", board->ea);
	printf("board->width: %f\n", board->width);
	printf("board->height: %f\n", board->height);
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
} */
