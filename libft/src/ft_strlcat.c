/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarbois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 12:40:28 by mdarbois          #+#    #+#             */
/*   Updated: 2022/11/29 12:40:29 by mdarbois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	dest_len;

	dest_len = ft_strlen(dst);
	i = dest_len;
	j = 0;
	if ((dest_len < (size - 1)) && size > 0)
	{
		while (src[j] != '\0' && ((dest_len + j) < (size - 1)))
		{
			dst[i] = src[j];
			j++;
			i++;
		}
		dst[i] = '\0';
	}
	if (dest_len >= size)
		dest_len = size;
	return (dest_len + ft_strlen(src));
}
