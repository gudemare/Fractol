/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudemare <gudemare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/11 06:35:30 by gudemare          #+#    #+#             */
/*   Updated: 2017/08/23 22:51:16 by gudemare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "fractol.h"

void	pxput(t_fractol *d, int x, int y, int color)
{
	if (x >= 0 && x < SCREEN_WIDTH && y >= 0 & y < SCREEN_HEIGHT)
		*((int*)d->addr + x + y * d->l_size_4) = color;
	else
		ft_putstr("BADPXL\n");
}
