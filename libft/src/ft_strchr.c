/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarbois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 12:40:51 by mdarbois          #+#    #+#             */
/*   Updated: 2022/11/29 12:40:52 by mdarbois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/libft.h"

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (0);
	if ((char)c == '\0')
		return ((char *)s);
	while (*s != '\0')
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	return (0);
}
