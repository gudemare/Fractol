/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudemare <gudemare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 23:07:29 by gudemare          #+#    #+#             */
/*   Updated: 2017/07/11 10:44:33 by gudemare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	ft_sec_strlen(const char *s)
{
	size_t size;

	size = 0;
	if (s)
		while (s[size])
			size++;
	return (size);
}

char		*ft_strjoin(char const *s1, char const *s2)
{
	char			*dst;

	if (!(dst = ft_strnew(ft_sec_strlen(s1) + ft_sec_strlen(s2))))
		return (NULL);
	if (s1)
		ft_strcpy(dst, s1);
	if (s2)
		ft_strcat(dst, s2);
	return (dst);
}
