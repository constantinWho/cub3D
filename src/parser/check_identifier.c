/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_identifier.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 14:24:41 by mdarbois          #+#    #+#             */
/*   Updated: 2023/11/24 00:59:24 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	no_space(char readline)
{
	if (readline != '\n' && readline != ' ')
		return (0);
	return (1);
}

int	is_identifier(char *line, int j)
{
	if ((line[j] == 'N' && line[j + 1] == 'O')
		|| (line[j] == 'S' && line[j + 1] == 'O')
		|| (line[j] == 'W' && line[j + 1] == 'E')
		|| (line[j] == 'E' && line[j + 1] == 'A')
		|| (line[j] == 'F' || line[j] == 'C'))
		return (0);
	return (1);
}

static void	assign(t_board *board, int type, char *sub)
{
	if (type == 1)
		board->no = ft_strdup(sub);
	else if (type == 2)
		board->so = ft_strdup(sub);
	else if (type == 3)
		board->we = ft_strdup(sub);
	else if (type == 4)
		board->ea = ft_strdup(sub);
	free(sub);
}

static int	extract_path(t_board *board, char *line, int i, int type)
{
	int		j;
	char	*sub;
	char	*xpm;

	j = ft_strlen(line) - 1;
	i += 2;
	while (line[i] == ' ')
		i++;
	while (line[j] == ' ')
		j--;
	if (j < i)
		return (ft_error(board, "Invalid element info\n", 1));
	sub = ft_substr(line, i, j - i + 1);
	xpm = ft_substr(sub, ft_strlen(sub) - 5, 5);
	if (ft_strncmp(xpm, ".png", 4) != 0)
	{
		free(xpm);
		return (ft_error(board, "File should end with '.png'\n", 1));
	}
	free(xpm);
	assign(board, type, sub);
	board->flag += 1;
	return (EXIT_SUCCESS);
}

int	select_identifier(t_board *board, char *line)
{
	int	j;

	j = 0;
	while (line[j] == ' ')
		j++;
	if (line[j] == 'N' && line[j + 1] == 'O' && board->no == NULL)
		return (extract_path(board, line, j, 1));
	else if (line[j] == 'N' && line[j + 1] == 'O' && board->no != NULL)
		return (ft_error(board, "Double elements (SO)\n", 1));
	else if (line[j] == 'S' && line[j + 1] == 'O' && board->so == NULL)
		return (extract_path(board, line, j, 2));
	else if (line[j] == 'S' && line[j + 1] == 'O' && board->so != NULL)
		return (ft_error(board, "Double elements (SO)\n", 1));
	else if (line[j] == 'W' && line[j + 1] == 'E' && board->we == NULL)
		return (extract_path(board, line, j, 3));
	else if (line[j] == 'W' && line[j + 1] == 'E' && board->we != NULL)
		return (ft_error(board, "Double elements (WE)\n", 1));
	else if (line[j] == 'E' && line[j + 1] == 'A' && board->ea == NULL)
		return (extract_path(board, line, j, 4));
	else if (line[j] == 'E' && line[j + 1] == 'A' && board->ea != NULL)
		return (ft_error(board, "Double elements (EA)\n", 1));
	else
		return (EXIT_FAILURE);
}
