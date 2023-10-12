/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:06:38 by mdarbois          #+#    #+#             */
/*   Updated: 2023/10/12 12:44:06 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3D.h"

static int	get_color_ceiling(t_board *board, char **split)
{
	board->c = (int *)malloc(sizeof(int) * 3);
	board->c[0] = ft_atoi(split[0]);
	board->c[1] = ft_atoi(split[1]);
	board->c[2] = ft_atoi(split[2]);
	free_array(split);
	if (board->c[0] < 0 || board->c[0] > 255)
		return (ft_error(board, "Color input is invalid\n", 1));
	else if (board->c[1] < 0 || board->c[1] > 255)
		return (ft_error(board, "Color input is invalid\n", 1));
	else if (board->c[2] < 0 || board->c[2] > 255)
		return (ft_error(board, "Color input is invalid\n", 1));
	return (EXIT_SUCCESS);
}

static int	get_color_floor(t_board *board, char **split)
{
	board->f = (int *)malloc(sizeof(int) * 3);
	board->f[0] = ft_atoi(split[0]);
	board->f[1] = ft_atoi(split[1]);
	board->f[2] = ft_atoi(split[2]);
	free_array(split);
	if (board->f[0] < 0 || board->f[0] > 255)
		return (ft_error(board, "Color input is invalid\n", 1));
	else if (board->f[1] < 0 || board->f[1] > 255)
		return (ft_error(board, "Color input is invalid\n", 1));
	else if (board->f[2] < 0 || board->f[2] > 255)
		return (ft_error(board, "Color input is invalid\n", 1));
	return (EXIT_SUCCESS);
}

static int	get_colors(t_board *board, char **split, int type)
{
	int	i;

	i = 0;
	while (split[i] != 0)
		i++;
	if (i != 3)
		return (EXIT_FAILURE);
	if (type == 1)
		return (get_color_floor(board, split));
	else if (type == 2)
		return (get_color_ceiling(board, split));
	return (EXIT_SUCCESS);
}

static int	check_color_comma(t_board *board, char *string, int i)
{
	int		comma;

	comma = 0;
	if (string[i] == ',')
		return (ft_error(board, "Color input is invalid beg comma\n", 1));
	while (string[i] != '\0')
	{
		if (string[i] == ',' && string[i + 1] == ',')
			return (ft_error(board, "Color is invalid comma in a row\n", 1));
		else if (string[i] == ',' && string[i + 1] != ',')
			comma++;
		i++;
	}
	if (string[i] == ',')
		return (ft_error(board, "Color input is invalid last comma\n", 1));
	if (comma != 2)
		return (ft_error(board, "Color input is invalid\n", 1));
	return (EXIT_SUCCESS);
}

int	check_color(t_board *board, char *string, int i, int type)
{
	char	**split;
	char	*color;
	int		j;

	j = ft_strlen(string) - 1;
	i++;
	while (string[i] != '\0' && string[i] == ' ')
		i++;
	while (string[j] == ' ')
		j--;
	if (check_color_comma(board, string, i))
		return (EXIT_FAILURE);
	color = ft_substr(string, i, j - i + 1);
	split = ft_split(color, ',');
	free(color);
	if (get_colors(board, split, type))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
