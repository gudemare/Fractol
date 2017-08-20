/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudemare <gudemare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/06 07:27:25 by gudemare          #+#    #+#             */
/*   Updated: 2017/07/11 12:56:29 by gudemare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char		*ft_strndup(const char *src, size_t n)
{
	char	*dst;
	size_t	len;

	len = ft_min(ft_strlen(src), (int)n);
	if (!(dst = ft_strnew(len)))
		return (NULL);
	ft_strncpy(dst, src, len);
	return (dst);
}
