/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudemare <gudemare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/11 07:04:16 by gudemare          #+#    #+#             */
/*   Updated: 2017/08/25 00:44:22 by gudemare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "fractol.h"

static void	quit(t_fractol *d)
{
	mlx_destroy_image(d->mlx, d->img);
	mlx_destroy_window(d->mlx, d->win);
	free(d->bitshifts);
	ft_putstr("Goodbye\n");
	exit(EXIT_SUCCESS);
}

int			handle_mouse_movement(int x, int y, void *param)
{
	t_fractol *d;

	d = param;
	if (!(d->mouse_change))
		return (1);
	d->z_pow = fabs(cos(x / 100.0f)) + fabs(sin(x / 100.0f) * y / 100.0f) * I;
	d->keys |= k_p_NOT_DRAWN;
	return (1);
}

int			handle_key_press(int x_event, void *param)
{
	t_fractol *d;

	d = param;
	if (x_event == k_ESC)
		quit(d);
	else if (x_event == k_KP_0)
		init_values(d);
	else if (x_event == k_SPACE)
		d->mouse_change = 1 - d->mouse_change;
	else
		d->keys |= d->bitshifts[x_event];
	d->keys &= ~(1 << 0);
	d->keys |= k_p_NOT_DRAWN;
	return (1);
}

int			handle_key_release(int x_event, void *param)
{
	t_fractol *d;

	d = param;
	d->keys &= ~(d->bitshifts[x_event]);
	return (1);
}
