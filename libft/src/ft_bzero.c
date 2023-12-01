/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarbois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 12:39:48 by mdarbois          #+#    #+#             */
/*   Updated: 2022/11/29 12:39:49 by mdarbois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/libft.h"

void	*ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *) s;
	while (n > 0)
	{
		ptr[n - 1] = '\0';
		n--;
	}
	return (s);
}
