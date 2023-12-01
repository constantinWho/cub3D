/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarbois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 12:39:39 by mdarbois          #+#    #+#             */
/*   Updated: 2022/11/29 12:39:40 by mdarbois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			a;
	unsigned char	*ptr;

	a = 0;
	ptr = (unsigned char *) s;
	while (a < n)
	{
		ptr[a] = c;
		a++;
	}
	return (s);
}
