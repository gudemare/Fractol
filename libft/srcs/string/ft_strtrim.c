/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudemare <gudemare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 23:11:26 by gudemare          #+#    #+#             */
/*   Updated: 2017/02/06 14:15:56 by gudemare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	ft_trimlen(char const *s)
{
	unsigned int	start;
	unsigned int	end;

	start = 0;
	while (s[start] &&
		(s[start] == ' ' || s[start] == '\n' || s[start] == '\t'))
		start++;
	if (!s[start])
		return (0);
	end = ft_strlen(s) - 1;
	while (s[end] == ' ' || s[end] == '\n' || s[end] == '\t')
		end--;
	return (end - start + 1);
}

char		*ft_strtrim(char const *s)
{
	unsigned int	len;
	unsigned int	index;
	char			*dst;

	index = 0;
	len = ft_trimlen(s);
	dst = (char *)malloc(sizeof(*dst) * (len + 1));
	if (!dst)
		return (NULL);
	dst[len] = '\0';
	while (*s && (*s == ' ' || *s == '\n' || *s == '\t'))
		s++;
	while (index < len)
	{
		dst[index] = s[index];
		index++;
	}
	return (dst);
}
