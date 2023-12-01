/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdarbois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 12:12:29 by mdarbois          #+#    #+#             */
/*   Updated: 2023/01/05 12:12:37 by mdarbois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_read(int fd, char *line)
{
	char	*buf;
	int		octets;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	octets = 1;
	while (!ft_strchr(line, '\n') && octets != 0)
	{
		octets = read(fd, buf, BUFFER_SIZE);
		if (octets == -1)
		{
			free(buf);
			if (line)
				free(line);
			return (NULL);
		}
		buf[octets] = '\0';
		line = ft_strjoin(line, buf);
	}
	free (buf);
	return (line);
}

char	*get_next_line(int fd)
{
	char		*str;
	static char	*line;

	if (fd < 0 || fd > 1023 || BUFFER_SIZE <= 0)
	{
		if (fd == -2)
			free(line);
		return (NULL);
	}
	line = ft_read(fd, line);
	if (!line)
		return (NULL);
	str = ft_copy_line(line);
	line = ft_new_str(line);
	return (str);
}
