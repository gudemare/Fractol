/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudemare <gudemare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 04:40:21 by gudemare          #+#    #+#             */
/*   Updated: 2016/11/21 08:13:04 by gudemare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *s1, const char *s2)
{
	int		a;
	int		b;

	if (!*s2)
		return ((char*)s1);
	a = 0;
	while (s1[a])
	{
		if (s1[a] == s2[0])
		{
			b = 1;
			while (s2[b] && s1[a + b] == s2[b])
				b++;
			if (!s2[b])
				return ((char*)&s1[a]);
		}
		a++;
	}
	return (NULL);
}
