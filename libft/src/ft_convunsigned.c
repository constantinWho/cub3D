/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convunsigned.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarbois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 10:54:46 by mdarbois          #+#    #+#             */
/*   Updated: 2023/01/05 10:54:53 by mdarbois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/libft.h"

static int	ft_len(unsigned int nb)
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

static char	*ft_unsitoa(unsigned int nb)
{
	char	*str;
	size_t	i;

	i = ft_len(nb);
	str = (char *)malloc(sizeof(*str) * (i + 1));
	if (!(str))
		return (0);
	str[i] = '\0';
	i--;
	if (nb == 0)
		str[i] = '0';
	while (nb != 0)
	{
		str[i] = (nb % 10) + 48;
		nb = nb / 10;
		i--;
	}
	return (str);
}

int	ft_printunsdec(unsigned int n)
{
	int		l;
	char	*num;

	l = 0;
	if (n == 0)
		l += write (1, "0", 1);
	else
	{
		num = ft_unsitoa(n);
		l += ft_printstring(num);
		free(num);
	}
	return (l);
}
