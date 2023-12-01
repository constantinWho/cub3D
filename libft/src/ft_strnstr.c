/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarbois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 12:41:32 by mdarbois          #+#    #+#             */
/*   Updated: 2022/11/29 12:41:33 by mdarbois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/libft.h"

char	*ft_strnstr(const char *big, const char *small, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (*small == '\0' || small == NULL)
		return ((char *)big);
	while (big[i] != '\0' && i < len)
	{
		j = 0;
		while (small[j] == big[i + j] && (i + j) < len)
		{
			j++;
			if (small[j] == '\0')
			{
				return ((char *)big + i);
			}
		}
		i++;
	}
	return (NULL);
}
