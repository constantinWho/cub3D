/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 14:02:32 by chustei           #+#    #+#             */
/*   Updated: 2023/11/24 18:11:46 by chustei          ###   ########.fr       */
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

static void	ft_set_viewpoint(t_game *game)
{
	if (game->board->map_face == 'N')
	{
		game->dir.x = -1;
		game->dir.y = 0;
		game->plane.x = 0;
		game->plane.y = 0.66;
	}
	else if (game->board->map_face == 'S')
	{
		game->dir.x = 1;
		game->dir.y = 0;
		game->plane.x = 0;
		game->plane.y = -0.66;
	}
	else if (game->board->map_face == 'E')
	{
		game->dir.x = 0;
		game->dir.y = 1;
		game->plane.x = 0.66;
		game->plane.y = 0;
	}
	else if (game->board->map_face == 'W')
	{
		game->dir.x = 0;
		game->dir.y = -1;
		game->plane.x = -0.66;
		game->plane.y = 0;
	}
}

static void	ft_init_screen(t_game *game)
{
	game->screen = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (!game->screen)
		exit(EXIT_FAILURE);
	game->pos.x = game->board->map_py + 0.5;
	game->pos.y = game->board->map_px + 0.5;
	ft_set_viewpoint(game);
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
	game->world_map = mlx_new_image(game->mlx, game->board->width * 11 , game->board->height * 11);
	if (!game->world_map)
		exit(EXIT_FAILURE);
	mlx_image_to_window(game->mlx, game->screen, 0, 0);
	mlx_image_to_window(game->mlx, game->world_map, 0, 0);
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
	check_empty_lines(game->board);
	check_identifier_factor(game->board->no);
	check_identifier_factor(game->board->so);
	check_identifier_factor(game->board->we);
	check_identifier_factor(game->board->ea);
 	check_map_walls(game->board);
	if (check_map_face(game->board) != 1)
		ft_error(game->board, "Player doesn't exist\n", 1);
}

void	ft_render_map(void *param)
{
	t_game	*game;
	int		i;
	int		j;

	game = param;
	i = -1;
	while (++i < (int)game->world_map->height)
	{
		j = -1;
		while (++j < (int)game->world_map->width)
		{
			if (game->board->map[i / 11][j / 11] == '1')
				mlx_put_pixel(game->world_map, j, i, 0xecf0f180);
			else
				mlx_put_pixel(game->world_map, j, i, 0x2c3e5080);
		}
	}
	i = -1;
	while (++i < 5)
	{
		j = -1;
		while (++j < 5)
			mlx_put_pixel(game->world_map, (game->pos.y * 11 + i ) - 2.5, (game->pos.x * 11 + j) - 2.5, 0x00FF0080);
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
