/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 12:26:42 by mdarbois          #+#    #+#             */
/*   Updated: 2023/11/27 19:29:03 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

static void	width(char *line, t_board *board)
{
	int	width;

	width = 0;
	width = ft_strlen(line) - 1;
	if (board->width < width)
		board->width = width;
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
		ft_error(board, "init: malloc", 1);
	temporary[(int)board->height] = NULL;
	while (i < board->height - 1)
	{
		temporary[i] = ft_strdup(board->map[i]);
		free(board->map[i]);
		board->map[i] = NULL;
		i++;
	}
	free(board->map);
	temporary[i] = ft_strdup(line);
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
		if (board->flag > 6)
			return (ft_error(board, "Multiple colors argument\n", 1));
		if (board->flag != 6 && is_identifier(readline, i)
			&& !no_space(readline[i]))
			return (ft_error(board, "Map must be the last element\n", 1));
		if (is_identifier(readline, i) && !no_space(readline[i]))
		{
			if (!add_line(board, readline))
				break ;
		}
		free(readline);
		readline = get_next_line(board->fd);
	}
	return (1);
}
