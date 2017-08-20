/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudemare <gudemare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 04:37:54 by gudemare          #+#    #+#             */
/*   Updated: 2017/07/11 13:01:28 by gudemare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char		*ft_strdup(const char *src)
{
	char	*dst;
	size_t	i;

	i = 0;
	if (!(dst = ft_strnew(ft_strlen(src))))
		return (NULL);
	ft_strcpy(dst, src);
	return (dst);
}
