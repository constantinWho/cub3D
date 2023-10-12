/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 14:43:39 by mdarbois          #+#    #+#             */
/*   Updated: 2023/10/12 13:34:02 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

static void	width(char *line, t_board *board)
{
	int	width;

	width = 0;
	width = ft_strlen(line) - 1;
	if (board->width < width)
		board->width = width;
	if (board->map)
		free(board->map);
}

static int	add_line(t_board *board, char *line)
{
	char	**temporary;
	int		i;

	i = 0;
	if (!line)
		return (0);
	board->height++;
	temporary = (char **)malloc(sizeof(char *) * (board->height + 1));
	if (!temporary)
		die("init: malloc", 0);
	temporary[board->height] = NULL;
	while (i < board->height - 1)
	{
		temporary[i] = board->map[i];
		i++;
	}
	temporary[i] = line;
	width(line, board);
	board->map = temporary;
	return (1);
}

static int	extract_color(t_board *board, char *line)
{
	int	i;

	i = 0;
	while (line[i] != '\0' && line[i] == ' ')
		i++;
	if (line[i] == 'F')
		return (check_color(board, line, i, 1));
	else if (line[i] == 'C')
		return (check_color(board, line, i, 2));
	return (EXIT_FAILURE);
}

static int	extract(t_board *board, char *readline, int i)
{
	if (readline[i + 2] == '\n')
		return (ft_error(board, "first type identifier and then info\n", 1));
	else if (readline[i] == 'F' || readline[i] == 'C')
	{
		if (extract_color(board, readline))
			return (ft_error(board, "color\n", 1));
	}
	else
	{
		if (select_identifier(board, readline))
			return (ft_error(board, "identifier\n", 1));
	}
	return (EXIT_FAILURE);
}

int	map_reading(t_board *board)
{
	char	*readline;
	int		i;

	readline = get_next_line(board->fd);
	while (readline != NULL)
	{
		i = 0;
		while (readline[i] != '\n' && readline[i] == ' ')
			i++;
		if (!is_identifier(readline, i))
			extract(board, readline, i);
		if ((board->no && board->so && board->ea && board->we
				&& board->c && board->f))
			board->flag = 1;
		if (board->flag == 1 && is_identifier(readline, i))
		{
			if (!add_line(board, readline))
				break ;
		}
		readline = get_next_line(board->fd);
	}
	close(board->fd);
	if (board->flag == 0)
		return (ft_error(board, "Map must come after the identifier\n", 1));
	return (1);
}
