/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_walls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 11:18:30 by mdarbois          #+#    #+#             */
/*   Updated: 2023/10/12 12:44:10 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

static int	check_first_row(t_board *board)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (board->map[j][i] && board->map[j][i] != '\n'
			&& board->map[j][i] == '1')
		i++;
	if (board->map[j][i] != '\n')
		return (1);
	return (0);
}

static int	check_last_row(t_board *board)
{
	int	i;
	int	j;

	i = 0;
	j = board->height - 1;
	while (board->map[j][i] && board->map[j][i] != '\n'
			&& board->map[j][i] == '1')
		i++;
	if (board->map[j][i] != '\n')
		return (1);
	return (0);
}

static int	check_columns(t_board *board)
{
	int	i;
	int	j;

	j = 0;
	while (j < board->height - 1)
	{
		i = 0;
		if (board->map[j][i] != '1')
			return (1);
		while ((size_t)i < (ft_strlen(board->map[j]) - 2))
		{
			if (board->map[j][i] != '0' && board->map[j][i] != '1'
				&& board->map[j][i] != ' ' && board->map[j][i] != 'N'
				&& board->map[j][i] != 'E' && board->map[j][i] != 'S'
				&& board->map[j][i] != 'W')
				return (2);
			i++;
		}
		if (board->map[j][i] != '1')
			return (3);
		j++;
	}
	return (0);
}

static void	fill_space(t_board *board)
{
	int	i;
	int	j;

	j = 0;
	while (j < board->height)
	{
		i = 0;
		while ((size_t)i < (ft_strlen(board->map[j]) - 2))
		{
			if (board->map[j][i] == ' ')
				board->map[j][i] = '1';
			i++;
		}
		j++;
	}
}

int	check_map_walls(t_board *board)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	fill_space(board);
	if (check_first_row(board))
		return (ft_error(board, "first row is missing walls\n", 1));
	if (check_columns(board) == 1)
		return (ft_error(board,
				"first column is missing walls\n", 1));
	if (check_columns(board) == 2)
		return (ft_error(board,
				"wrong character in the map\n", 1));
	if (check_columns(board) == 3)
		return (ft_error(board, "last column is missing walls\n", 1));
	if (check_last_row(board))
		return (ft_error(board, "last row is missing walls\n", 1));
	return (0);
}
