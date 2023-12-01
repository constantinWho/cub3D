/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarbois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 12:42:57 by mdarbois          #+#    #+#             */
/*   Updated: 2022/11/29 12:42:58 by mdarbois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*map;
	unsigned int	i;

	i = 0;
	if (s == 0)
		return (NULL);
	map = (char *)malloc(sizeof(*map) * (ft_strlen(s) + 1));
	if (map == NULL)
		return (map);
	while (*(s + i) != '\0')
	{
		*(map + i) = (*f)(i, *(s + i));
		i++;
	}
	*(map + i) = '\0';
	return (map);
}
