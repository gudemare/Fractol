/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudemare <gudemare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/11 07:04:16 by gudemare          #+#    #+#             */
/*   Updated: 2017/08/26 06:32:53 by gudemare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "fractol.h"

int			handle_button_release(int button, int x, int y, void *param)
{
	t_fractol *d;

	(void)x;
	(void)y;
	if (button == k_RightButton || button == k_LeftButton)
	{
		d = (t_fractol *)param;
		d->keys &= ~(d->bitshifts[button + 1]);
	}
	return (1);
}

int			handle_button_press(int button, int x, int y, void *param)
{
	t_fractol *d;

	d = (t_fractol *)param;
	if (button == k_RightButton || button == k_LeftButton)
	{
		d->mouse_x = x;
		d->mouse_y = y;
		d->keys |= d->bitshifts[button + 1];
		d->keys |= k_p_NOT_DRAWN;
	}
	else if (button == k_ScrollDown || button == k_ScrollUp)
	{
		d->x_offset -= x / d->zoom;
		d->y_offset -= y / d->zoom;
		d->zoom *= (button == k_ScrollUp) ? 1.1f : 1.0f / 1.1f;
		d->x_offset += x / d->zoom;
		d->y_offset += y / d->zoom;
		d->keys |= k_p_NOT_DRAWN;
	}
	return (1);
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
