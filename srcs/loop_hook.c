/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudemare <gudemare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/11 06:37:01 by gudemare          #+#    #+#             */
/*   Updated: 2017/08/21 00:09:18 by gudemare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include <complex.h>
#include "fractol.h"

static int	get_point_color(t_fractol *d, int x, int y)
{
	float complex	z;
	int				iter;

	z = 1 + 0.51 * I;
	iter = 0;
	while (iter++ < d->iter_nb)
	{
		z *= z;
		z += (float complex)x + (float complex)(y * I);
	}
	if (fabs(crealf(z)) < d->c && fabs(cimagf(z)) < d->c)
		return (0x0000FF);
	return (0x00FF00);
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
		{
			pxput(d, i, j, get_point_color(d, i - d->x_offset, j - d->y_offset));
		}
	}
}

static void	apply_key(t_fractol *d)
{
	if (d->keys & k_p_LEFT)
		d->x_offset += 50;
	if (d->keys & k_p_RIGHT)
		d->x_offset -= 50;
	if (d->keys & k_p_UP)
		d->y_offset += 50;
	if (d->keys & k_p_DOWN)
		d->y_offset -= 50;
	if (d->keys & k_p_KP_P)
		d->zoom *= 1.01f;
	if (d->keys & k_p_KP_M)
		d->zoom /= 1.01f;
	if (d->keys & k_p_KP_1)
		d->c /= 2.0f;
	if (d->keys & k_p_KP_3)
		d->c *= 2.0f;
	if (d->keys & k_p_KEY_A)
		d->color_mod *= 1.0001f;
	if (d->keys & k_p_KEY_S)
		d->color_mod /= 1.0001f;
	if (d->keys & k_p_KP_P)
		d->iter_nb++;
	if (d->keys & k_p_KP_M && d->iter_nb > 1)
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
		d->keys &= ~k_p_NOT_DRAWN;
	}
	return (1);
}
