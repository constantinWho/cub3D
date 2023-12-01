/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarbois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 12:42:08 by mdarbois          #+#    #+#             */
/*   Updated: 2022/11/29 12:42:10 by mdarbois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;

	if (s == NULL)
		return (NULL);
	if (start >= ft_strlen(s) || len == 0)
		return (ft_strdup(""));
	if ((ft_strlen(s) - start) > len)
		i = len + 1;
	else
		i = ft_strlen(s) - start + 1;
	sub = (char *)malloc(sizeof(*sub) * i);
	if (sub == NULL)
		return (NULL);
	ft_strlcpy(sub, (s + start), i);
	return (sub);
}
