/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarbois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 12:41:56 by mdarbois          #+#    #+#             */
/*   Updated: 2022/11/29 12:41:59 by mdarbois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/libft.h"

char	*ft_strdup(const char *s1)
{
	char	*s;
	int		i;
	int		len;

	len = ft_strlen(s1);
	s = (char *)malloc(sizeof(*s) * (len + 1));
	i = 0;
	if (s == NULL)
		return (s);
	while (i < len)
	{
		s[i] = s1[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}
