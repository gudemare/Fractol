/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_arr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudemare <gudemare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/21 05:27:27 by gudemare          #+#    #+#             */
/*   Updated: 2017/08/11 10:16:10 by gudemare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void		ft_free_arr(char **ar)
{
	int		i;

	if (!ar)
		return ;
	i = 0;
	while (ar[i])
	{
		free(ar[i]);
		ar[i++] = NULL;
	}
	free(ar);
}
