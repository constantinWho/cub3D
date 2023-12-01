/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarbois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 12:42:48 by mdarbois          #+#    #+#             */
/*   Updated: 2022/11/29 12:42:49 by mdarbois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/libft.h"

static int	ft_len(int nb)
{
	size_t	len;

	len = 0;
	if (nb <= 0)
		len++;
	while (nb != 0)
	{
		nb = nb / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int nb)
{
	char	*str;
	size_t	i;
	int		sign;

	i = ft_len(nb);
	str = (char *)malloc(sizeof(*str) * (i + 1));
	if (!(str))
		return (0);
	sign = 1;
	str[i] = '\0';
	i--;
	if (nb < 0)
	{
		str[0] = '-';
		sign = -1;
	}
	else if (nb == 0)
		str[i] = '0';
	while (nb != 0)
	{
		str[i] = (nb % 10 * sign) + 48;
		nb = nb / 10;
		i--;
	}
	return (str);
}
