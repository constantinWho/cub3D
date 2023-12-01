/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarbois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 12:42:29 by mdarbois          #+#    #+#             */
/*   Updated: 2022/11/29 12:42:30 by mdarbois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trim;
	size_t	start;
	size_t	end;

	trim = 0;
	if (s1 != 0 && set != 0)
	{
		start = 0;
		end = ft_strlen(s1);
		while (s1[start] != 0 && (ft_strchr(set, s1[start])) != 0)
			start++;
		while (end > start && ft_strchr(set, s1[end - 1]) && s1[end - 1])
			end--;
		trim = (char *)malloc(sizeof(*trim) * (end - start + 1));
		if (trim == NULL)
			return (trim);
		ft_strlcpy(trim, &s1[start], end - start + 1);
	}
	return (trim);
}
