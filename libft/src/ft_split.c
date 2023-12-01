/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarbois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 12:42:39 by mdarbois          #+#    #+#             */
/*   Updated: 2022/11/29 12:42:40 by mdarbois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/libft.h"

static void	ft_free(char **split, int j)
{
	while (j > 0)
	{
		free(split[--j]);
	}
	free(split);
}

static int	ft_delimitator(char c, char deli)
{
	if (c == deli || c == '\0')
		return (1);
	return (0);
}

static void	ft_write(char *dest, char *from, char deli)
{
	int	i;

	i = 0;
	while (ft_delimitator(from[i], deli) == 0)
	{
		dest[i] = from[i];
		i++;
	}
	dest[i] = '\0';
}

static void	*ft_copy(char **split, char *str, char deli)
{
	int	i;
	int	j;
	int	string;

	i = 0;
	string = 0;
	while (str[i] != '\0')
	{
		if (ft_delimitator(str[i], deli) == 1)
			i++;
		else
		{
			j = 0;
			while (ft_delimitator(str[i + j], deli) == 0)
				j++;
			split[string] = (char *)malloc(sizeof(char) * (j + 1));
			if (split == NULL)
				ft_free(split, string);
			ft_write(split[string], str + i, deli);
			i = i + j;
			string++;
		}
	}
	return ((void *)1);
}

char	**ft_split(char const *s, char c)
{
	int		strings;
	char	**split;
	char	*str;
	int		i;

	if (s == NULL)
		return (NULL);
	str = (char *)s;
	strings = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (ft_delimitator(str[i + 1], c) == 1
			&& ft_delimitator(str[i], c) == 0)
			strings++;
		i++;
	}
	split = (char **)malloc(sizeof(char *) * (strings + 1));
	if (split == NULL)
		return (NULL);
	split[strings] = 0;
	if (ft_copy(split, str, c) == NULL)
		return (NULL);
	return (split);
}
