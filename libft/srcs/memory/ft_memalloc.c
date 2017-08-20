/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudemare <gudemare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/12 21:51:57 by gudemare          #+#    #+#             */
/*   Updated: 2016/11/13 04:27:43 by gudemare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void	*dst;

	dst = malloc(sizeof(char) * size);
	if (!dst)
		return (0);
	while (size > 0)
	{
		*((unsigned char *)dst + size) = 0;
		size--;
	}
	*(unsigned char *)dst = 0;
	return (dst);
}
