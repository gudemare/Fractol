/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_power.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudemare <gudemare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/13 14:10:54 by gudemare          #+#    #+#             */
/*   Updated: 2016/11/13 14:15:31 by gudemare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned int	ft_power(int nb, unsigned int power)
{
	unsigned int	res;
	unsigned int	tmp;

	res = 1;
	while (power > 0)
	{
		tmp = res * nb;
		if (tmp < res)
			return (0);
		res = tmp;
		power--;
	}
	return (res);
}
