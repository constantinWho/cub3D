/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarbois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 12:41:24 by mdarbois          #+#    #+#             */
/*   Updated: 2022/11/29 12:41:25 by mdarbois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*first;
	unsigned char	*second;

	first = (unsigned char *)s1;
	second = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (*(first + i) != *(second + i))
			return ((*(first + i) - *(second + i)));
		i++;
	}
	return (0);
}
