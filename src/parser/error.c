/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:21:32 by mdarbois          #+#    #+#             */
/*   Updated: 2023/11/29 05:21:07 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

void	free_array(char **array)
{
	int	i;

	i = 0;
	if (array)
	{
		while (array[i])
		{
			if (array[i])
			{
				free(array[i]);
				array[i] = NULL;
			}
			i++;
		}
		free(array);
		array = NULL;
	}
}

void	free_board(t_board *board)
{
	int	i;

	i = 0;
	if (board->map)
	{
		while (board->map[i])
		{
			if (board->map[i])
			{
				free(board->map[i]);
				board->map[i] = NULL;
			}
			i++;
		}
		free(board->map);
		board->map = NULL;
	}
}

static void	free_ptr(void *ptr)
{
	free(ptr);
	ptr = NULL;
}

int	free_map(t_board *board)
{
	if (board->no)
		free(board->no);
	if (board->so)
		free(board->so);
	if (board->we)
		free(board->we);
	if (board->ea)
		free(board->ea);
	if (board->c)
		free_ptr(board->c);
	if (board->f)
		free_ptr(board->f);
	if (board->map)
		free_board(board);
	if (board)
	{
		free(board);
		board = NULL;
	}
	exit(1);
}

int	ft_error(t_board *board, char *str, int i)
{
	ft_putstr_fd("Error: ", 2);
	if (str)
		ft_putstr_fd(str, STDERR_FILENO);
	if (i == 1)
		(free_map(board));
	exit(1);
}
