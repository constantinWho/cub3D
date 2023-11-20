/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 14:02:32 by chustei           #+#    #+#             */
/*   Updated: 2023/11/09 13:13:32 by chustei          ###   ########.fr       */
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
	board->map_face = 'X';
	board->map_px = 0;
	board->map_py = 0;
}

void print_struc(t_board *board)
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
}

int	check_map_face(t_board *board)
{
	int		found;
	double	y;
	double	x;

	y = 0.0;
	found = 0;
	while (board->map[(int)y])
	{
		x = 0.0;
		while (board->map[(int)y][(int)x])
		{
			if (board->map[(int)y][(int)x] == 'N' || \
				board->map[(int)y][(int)x] == 'S' || \
				board->map[(int)y][(int)x] == 'E' || \
				board->map[(int)y][(int)x] == 'W')
			{
				found++;
				board->map_face = board->map[(int)y][(int)x];
				board->map_px = x;
				board->map_py = y;
			}
			x++;
		}
		y++;
	}

	return (found);
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
	/*if (check_map_face(game.board) != 1)
		return (ft_error(game.board, "Player doesn't exist\n", 1));
	print_struc(game.board);
	 ++++++++++++++++++++++++++++++++++++++++++++++++
	 game.mlx = mlx_init(HEIGHT, WIDTH, "cub3D", false);
	if (!game.mlx)
		exit(EXIT_FAILURE);
	double size = 512.0 / game.board->width; */
/* 	printf("m_px: %f, m_py: %f\n", game.board->map_px, game.board->map_py); */
	// game.player_x = /* game.board->map_px; */(size * (game.board->map_px)) + (size / 2.0);
	//game.player_y = /* game.board->map_py; */(size * (game.board->map_py)) + (size / 2.0);
 /* 	printf("(%f * %f) + %f\n", 512/game.board->width, game.board->map_px + 1, (512/game.board->width)/2);
	//printf("x: %f, y: %f | %f : %f\n", game.player_x, game.player_y, game.board->map_px, game.board->map_py); */
	/* game.rotation_angle = 0.0;
	game.tile_size = 512.0 / (double)game.board->width;
	game.map = mlx_new_image(game.mlx, 512, 512);
	game.screen = mlx_new_image(game.mlx, 512, 512);
	game.texture = mlx_load_png("./texture.png");
	game.dir_x = 1;
	game.dir_y = 0;
	game.plane_x = 0;
	game.plane_y = 0.66;
	mlx_image_to_window(game.mlx, game.map, 0, 0);
	mlx_image_to_window(game.mlx, game.screen, 512, 0);
	mlx_loop_hook(game.mlx, &ft_render, &game.mlx);
	mlx_loop_hook(game.mlx, &ft_keys, &game.mlx);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx); */ 
	return (EXIT_SUCCESS);
}
