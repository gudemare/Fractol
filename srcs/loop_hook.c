/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudemare <gudemare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/11 06:37:01 by gudemare          #+#    #+#             */
/*   Updated: 2017/08/23 17:52:53 by gudemare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> //

#include <stdlib.h>
#include <math.h>
#include <complex.h>
#include "fractol.h"

static int	get_point_color(const int iter_nb, const float complex c,
		const float z_pow)
{
	float complex		z;
	int					iter;
	float				real;
	float				imag;

	z = 0 + 0 * I;
	iter = 0;
	while (iter++ < iter_nb)
	{
		z = cpow(z, z_pow) + c;
		real = crealf(z);
		imag = cimagf(z);
		if (real * real + imag * imag >= 4.0f)
			break;
	}
	if (iter < iter_nb)
		return (iter * 0x123456);
	return (0x000000);
}

static void	draw_img(t_fractol *d)
{
	int		i;
	int		j;

	j = -1;
	while (++j < SCREEN_HEIGHT)
	{
		i = -1;
		while (++i < SCREEN_WIDTH)
			*((int*)d->addr + i + j * d->l_size_4) = d->color_mod *
				get_point_color(d->iter_nb, ((i - d->x_offset) / d->zoom)
						+ ((j - d->y_offset) / d->zoom) * I, d->c);
	}
}

static void	apply_key(t_fractol *d)
{
	if (d->keys & k_p_LEFT)
		d->x_offset += d->zoom / 10 + 3.4E-38;
	if (d->keys & k_p_RIGHT)
		d->x_offset -= d->zoom / 10 + 3.4E-38;
	if (d->keys & k_p_UP)
		d->y_offset += d->zoom / 10 + 3.4E-38;
	if (d->keys & k_p_DOWN)
		d->y_offset -= d->zoom / 10 + 3.4E-38;
	if (d->keys & k_p_KP_P)
		d->zoom *= 1.1f;
	if (d->keys & k_p_KP_M)
		d->zoom /= 1.1f;
	if (d->keys & k_p_KP_1)
		d->c *= 1.1f;
	if (d->keys & k_p_KP_3)
		d->c /= 1.1f;
	if (d->keys & k_p_KEY_A)
		d->color_mod *= 1.0001f;
	if (d->keys & k_p_KEY_S)
		d->color_mod /= 1.0001f;
	if (d->keys & k_p_KP_9)
		d->iter_nb++;
	if (d->keys & k_p_KP_7 && d->iter_nb > 1)
		d->iter_nb--;
}

int			fractol_loop(void *param)
{
	t_fractol		*d;

	d = (t_fractol *)param;
	if ((d->keys))
	{
		apply_key(d);
		mlx_destroy_image(d->mlx, d->img);
		d->img = mlx_new_image(d->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
		d->addr = mlx_get_data_addr(d->img, &d->bpp, &d->l_size, &d->endian);
		draw_img(d);
		mlx_put_image_to_window(d->mlx, d->win, d->img, 0, 0);
		mlx_string_put(d->mlx, d->win, 10, 10, 0x0000FF, ft_itoa(d->iter_nb));
		mlx_string_put(d->mlx, d->win, 10, 60, 0x0000FF, ft_itoa(d->x_offset));
		mlx_string_put(d->mlx, d->win, 10, 100, 0x0000FF, ft_itoa(d->y_offset));
		mlx_string_put(d->mlx, d->win, 10, 160, 0x0000FF, ft_itoa(d->zoom));
		d->keys &= ~k_p_NOT_DRAWN;
	}
	return (1);
}
