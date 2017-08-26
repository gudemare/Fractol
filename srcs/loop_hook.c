/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudemare <gudemare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/11 06:37:01 by gudemare          #+#    #+#             */
/*   Updated: 2017/08/26 06:32:53 by gudemare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include "fractol.h"

static void	pxput(t_fractol *d, int x, int y, int color)
{
	if (x >= 0 && x < SCREEN_WIDTH && y >= 0 & y < SCREEN_HEIGHT)
		*((int*)d->addr + x + y * d->l_size_4) = color;
}

static void	*draw_img_part_by_thread(void *data)
{
	const t_thread	*thr_d = (t_thread *)data;
	int				i;
	int				j;
	int				jmax;

	j = thr_d->thread_nb * (HEIGHT_BY_THREAD) - 1;
	jmax = j + 1 + HEIGHT_BY_THREAD;
	while (++j < jmax)
	{
		i = -1;
		while (++i < SCREEN_WIDTH)
			pxput(thr_d->d, i, j, thr_d->d->color_mod * thr_d->d->fract_func(
				thr_d->d->iter_nb,
				(i / thr_d->d->zoom - thr_d->d->x_offset)
				+ (j / thr_d->d->zoom - thr_d->d->y_offset) * I,
				thr_d->d->z_pow));
	}
	return (NULL);
}

static void	draw_img(t_fractol *d)
{
	pthread_t	threads[NUM_THREADS];
	t_thread	threads_data[NUM_THREADS];
	int			i;

	i = -1;
	while (++i < NUM_THREADS)
	{
		threads_data[i].thread_nb = i;
		threads_data[i].d = d;
		if (pthread_create(&threads[i], NULL,
				&draw_img_part_by_thread, (void *)&(threads_data[i])))
			exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < NUM_THREADS)
		if (pthread_join(threads[i++], NULL))
			exit(EXIT_FAILURE);
}

static void	apply_key(t_fractol *d)
{
	if (d->keys & k_p_LEFT)
		d->x_offset += (SCREEN_WIDTH / 50) / d->zoom;
	if (d->keys & k_p_RIGHT)
		d->x_offset -= (SCREEN_WIDTH / 50) / d->zoom;
	if (d->keys & k_p_UP)
		d->y_offset += (SCREEN_HEIGHT / 50) / d->zoom;
	if (d->keys & k_p_DOWN)
		d->y_offset -= (SCREEN_HEIGHT / 25) / d->zoom;
	if (d->keys & (k_p_MOUSE_LEFT | k_p_MOUSE_RIGHT))
	{
		d->x_offset -= d->mouse_x / d->zoom;
		d->y_offset -= d->mouse_y / d->zoom;
		d->zoom *= (d->keys & (k_p_MOUSE_LEFT)) ? 1.1f : 1.0f / 1.1f;
		d->x_offset += d->mouse_x / d->zoom;
		d->y_offset += d->mouse_y / d->zoom;
	}
	if (d->keys & k_p_KEY_A)
		d->color_mod *= 1.05f;
	if (d->keys & k_p_KEY_S)
		d->color_mod /= 1.05f;
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
		mlx_string_put(d->mlx, d->win, 10, 10, 0xFF0000, "Max iteration :");
		mlx_string_put(d->mlx, d->win, 160, 10, 0xFF0000, ft_itoa(d->iter_nb));
		d->keys &= ~k_p_NOT_DRAWN;
	}
	return (1);
}
