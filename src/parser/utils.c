/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarbois <mdarbois@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:07:46 by mdarbois          #+#    #+#             */
/*   Updated: 2023/12/01 15:07:47 by mdarbois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cub3d.h"

int	read_check(t_board *board, char *readline, int i)
{
	if (is_identifier(readline, i) && !no_space(readline[i]))
		return (ft_error(board, "Map must be the last element\n", 1));
	return (0);
}
