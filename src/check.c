/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 12:09:29 by mdarbois          #+#    #+#             */
/*   Updated: 2023/10/12 12:44:35 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

static size_t	ft_strlen_nospace(const char *s)
{
	size_t	l;

	l = 0;
	if (!s)
		return (0);
	while (s[l + 1] != '\0' && s[l] != ' ')
		l++;
	return (l);
}

int	check_identifier_factor(char *string)
{
	int		fd;
	char	*sub;

	fd = 0;
	sub = ft_substr(string, ft_strlen_nospace(string) - 4, 5);
	if (ft_strncmp(sub, ".xpm", 4) != 0)
	{
		free(sub);
		printf("Invalid file type, use .xpm!\n");
		return (1);
	}
	free(sub);
	fd = open(string, O_RDONLY);
	if (fd < 0)
		return (1);
	return (0);
}

static void	copy_map(int start, int end, t_board *board)
{
	char	**temp;
	int		j;

	j = 0;
	board->height = end - start + 1;
	temp = (char **)malloc(sizeof(char *) * (board->height + 2));
	if (!temp)
		ft_error(board, "malloc init\n", 1);
	temp[board->height + 1] = NULL;
	while (j <= board->height)
	{
		temp[j] = board->map[start];
		j++;
		start++;
	}
	free(board->map);
	board->map = temp;
}

int	check_empty_lines(t_board *board)
{
	int	i;
	int	start;
	int	end;

	i = 0;
	start = 0;
	end = 0;
	while (board->map[i] && ft_strncmp(board->map[i],
			"\n", ft_strlen(board->map[i])) == 0)
		i++;
	start = i;
	while (board->map[i] && ft_strncmp(board->map[i],
			"\n", ft_strlen(board->map[i])) != 0)
		i++;
	end = i - 1;
	while (board->map[i] && ft_strncmp(board->map[i],
			"\n", ft_strlen(board->map[i])) == 0)
		i++;
	if (i != board->height)
		return (ft_error(board, "Empty lines in map\n", 1));
	if (start != 0 || (end != board->height - 1))
		copy_map(start, end, board);
	return (0);
}
