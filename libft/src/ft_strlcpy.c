/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarbois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 12:40:18 by mdarbois          #+#    #+#             */
/*   Updated: 2022/11/29 12:40:19 by mdarbois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	n;

	n = 0;
	if (size > 0)
	{
		while (n < (size - 1) && src[n] != '\0')
		{
			dst[n] = src[n];
			n++;
		}
		dst[n] = '\0';
	}
	while (src[n])
		n++;
	return (n);
}
