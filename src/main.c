/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 14:02:32 by chustei           #+#    #+#             */
/*   Updated: 2023/11/24 16:13:11 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

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

void	ft_strwrap(t_board *board)
{
	board->no = ft_strtrim(board->no, "\n");
	board->so = ft_strtrim(board->so, "\n");
	board->we = ft_strtrim(board->we, "\n");
	board->ea = ft_strtrim(board->ea, "\n");
}

static void	ft_init_screen(t_game *game)
{
	game->screen = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->screen)
		exit(EXIT_FAILURE);
	printf("x: %f y: %f\n", game->board->map_px, game->board->map_py);
	game->pos.x = 3.5;
	game->pos.y = 3.5;
	game->dir.x = -1;
	game->dir.y = 0;
	game->plane.x = 0;
	game->plane.y = 0.66;
	game->move_speed = 0.08;
	game->rot_speed = 0.04;
	ft_strwrap(game->board);
	game->north = mlx_load_png(game->board->no);
	game->south = mlx_load_png(game->board->so);
	game->west = mlx_load_png(game->board->we);
	game->east = mlx_load_png(game->board->ea);
	if (!game->north || !game->south || !game->west || !game->east)
		exit(EXIT_FAILURE);
	int i = -1;
	game->buffer = ft_calloc((HEIGHT), sizeof(uint8_t *));
	while (++i < HEIGHT)
		game->buffer[i] = ft_calloc((WIDTH), sizeof(uint8_t *));
	mlx_image_to_window(game->mlx, game->screen, 0, 0);
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
				board->map[(int)y][(int)x] = '0';
				board->map_px = x;
				board->map_py = y;
				printf("x: %f y: %f\n", board->map_px, board->map_py);
			}
			x++;
		}
		y++;
	}
	return (found);
}

void	ft_parser(t_game *game, char **argv)
{
	game->board = malloc(sizeof(t_board));
	if (!game->board)
		ft_error(NULL, "malloc init\n", 0);
	init_board(game->board);
	game->board->fd = open(argv[1], O_RDONLY);
	if (game->board->fd < 0)
		ft_error(game->board, "File doesn't exit\n", 1);
	map_reading(game->board);
	print_struc(game->board);
	check_empty_lines(game->board);
	print_struc(game->board);
	check_identifier_factor(game->board->no);
	check_identifier_factor(game->board->so);
	check_identifier_factor(game->board->we);
	check_identifier_factor(game->board->ea);
 	check_map_walls(game->board);
	print_struc(game->board);
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
	mlx_image_t *map = mlx_new_image(game.mlx, game.board->width * 10 , game.board->height * 10);
	if (!map)
		exit(EXIT_FAILURE);
	mlx_image_to_window(game.mlx, map, 0, 0);
	int i = -1;
	int j;
	while (++i < (int)map->height)
	{
		j = -1;
		while (++j < (int)map->width)
		{
			if (game.board->map[i / 10][j / 10] == '1')
				mlx_put_pixel(map, j, i, 0xecf0f180);
			else
				mlx_put_pixel(map, j, i, 0x2c3e5080);
		}
	}
	int x = -1;
	while (++x < 5)
	{
		int y = -1;
		while (++y < 5)
			mlx_put_pixel(map, game.pos.x * 10 + x, game.pos.y * 10 + y, 0x00FF0080);
	}
	mlx_loop_hook(game.mlx, &ft_render, &game);
	mlx_loop_hook(game.mlx, &ft_keys_listener, &game);
	mlx_loop(game.mlx);
	ft_end_game(&game);
	exit(EXIT_SUCCESS);
}
