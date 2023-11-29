/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chustei <chustei@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:06:38 by mdarbois          #+#    #+#             */
/*   Updated: 2023/11/24 00:44:27 by chustei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	get_color_ceiling(t_board *board, char **split)
{
	board->c = (int *)malloc(sizeof(int) * 3);
	board->c[0] = ft_atoi(split[0]);
	board->c[1] = ft_atoi(split[1]);
	board->c[2] = ft_atoi(split[2]);
	free_array(split);
	if (board->c[0] < 0 || board->c[0] > 255)
		return (ft_error(board, "Ceiling first number is invalid\n", 1));
	else if (board->c[1] < 0 || board->c[1] > 255)
		return (ft_error(board, "Ceiling second number is invalid\n", 1));
	else if (board->c[2] < 0 || board->c[2] > 255)
		return (ft_error(board, "Ceiling third number is invalid\n", 1));
	return (EXIT_SUCCESS);
}

int	get_color_floor(t_board *board, char **split)
{
	board->f = (int *)malloc(sizeof(int) * 3);
	board->f[0] = ft_atoi(split[0]);
	board->f[1] = ft_atoi(split[1]);
	board->f[2] = ft_atoi(split[2]);
	free_array(split);
	if (board->f[0] < 0 || board->f[0] > 255)
		return (ft_error(board, "Floor first number is invalid\n", 1));
	else if (board->f[1] < 0 || board->f[1] > 255)
		return (ft_error(board, "Floor second number is invalid\n", 1));
	else if (board->f[2] < 0 || board->f[2] > 255)
		return (ft_error(board, "Floor third number is invalid\n", 1));
	return (EXIT_SUCCESS);
}

int	get_colors(t_board *board, char **split, int type)
{
	int	i;

	i = 0;
	while (split[i] != 0)
		i++;
	if (i != 3)
		return (free_array(split), ft_error(board, "Color input is invalid, \
				three numbers needed\n", 1));
	if (type == 1)
		return (get_color_floor(board, split));
	else if (type == 2)
		return (get_color_ceiling(board, split));
	return (EXIT_SUCCESS);
}

int	check_color_comma(t_board *board, char *string, int i)
{
	int		comma;

	comma = 0;
	if (string[i] == ',')
		return (free(string), \
			ft_error(board, "Color input is invalid beg comma\n", 1));
	while (string[i] != '\0')
	{
		if (string[i] == ',' && string[i + 1] == ',')
			return (free(string), \
				ft_error(board, "Color is invalid comma in a row\n", 1));
		else if (string[i] == ',' && string[i + 1] != ',')
			comma++;
		i++;
	}
	if (string[i] == ',')
		return (free(string), \
			ft_error(board, "Color input is invalid last comma\n", 1));
	if (comma != 2)
		return (free(string), \
			ft_error(board, "Color invalid: too many commas\n", 1));
	return (EXIT_SUCCESS);
}

int	check_comma_digit(t_board *board, char *string, int i)
{
	int	count;

	count = 0;
	while (string[i] != '\0' && string[i] != '\n')
	{
		if (string[i] != ',' && string[i] != 32 && !ft_isdigit((int)string[i]))
			return (free(string), ft_error(board, "Color input is invalid \
						only comma and digits allowed\n", 1));
		if (ft_isdigit((int)string[i]) && !ft_isdigit((int)string[i + 1]))
			count++;
		i++;
	}
	if (count != 3)
		return (free(string), ft_error(board, "Color input is invalid \
					only three numbers\n", 1));
	return (EXIT_SUCCESS);
}
