/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudemare <gudemare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 02:03:23 by gudemare          #+#    #+#             */
/*   Updated: 2016/11/13 04:19:24 by gudemare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*dst;

	if ((dst = (t_list *)malloc(sizeof(*dst))) == NULL)
		return (NULL);
	dst->next = NULL;
	dst->content_size = content_size;
	if ((dst->content = (void *)content) == NULL)
	{
		dst->content_size = 0;
		return (dst);
	}
	dst->content = (void *)malloc(sizeof(char) * content_size);
	if (!dst->content && dst->content_size != 0)
	{
		free(dst);
		return (NULL);
	}
	while (content_size > 0)
	{
		((char *)(dst->content))[content_size] =
			((const char *)content)[content_size];
		content_size--;
	}
	((char *)(dst->content))[0] = ((const char *)content)[0];
	return (dst);
}
