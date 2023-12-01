/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarbois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 15:44:41 by mdarbois          #+#    #+#             */
/*   Updated: 2022/12/12 15:44:43 by mdarbois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = NULL;
	new = (t_list *)malloc(sizeof(*new));
	if (new == NULL)
		return ((new));
	new -> content = content;
	new -> next = NULL;
	return (new);
}
