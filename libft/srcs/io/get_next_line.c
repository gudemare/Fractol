/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudemare <gudemare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 17:27:43 by gudemare          #+#    #+#             */
/*   Updated: 2017/08/11 08:12:20 by gudemare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"

int		get_next_line(const int fd, char **line, unsigned int buff_size)
{
	static char		*buf = NULL;
	char			*end;
	int				ret;

	if (fd < 0 || !line || (!buf && !(buf = ft_strnew(buff_size))))
		return (-1);
	while (!*buf || !(end = ft_strchr(buf, '\n')))
	{
		if (!(end = ft_strextend(buf, buff_size)))
			return (-1);
		ret = read(fd, end + ft_strlen(end), buff_size);
		if (!*(buf = end) && ret < 1)
			return (ret);
		if (ret < 1 && (*line = ft_strdup(buf)))
		{
			ft_strdel(&buf);
			return ((!*line) ? -1 : 1);
		}
	}
	*line = ft_strsub(buf, 0, end - buf);
	end = ft_strdup(end + 1);
	ft_strdel(&buf);
	if (!*line || !*(buf = end))
		ft_strdel(&buf);
	return (1);
}
