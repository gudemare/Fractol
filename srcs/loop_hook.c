/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudemare <gudemare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/11 06:37:01 by gudemare          #+#    #+#             */
/*   Updated: 2017/08/23 23:14:53 by gudemare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <pthread.h>
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

	if (cabsl(c) > 2.0f)
		return (0x123456);
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

void	*draw_img_part_by_thread(void *data)
{
	t_thread *thr_d;
	int		i;
	int		j;
	int		jmax;

	thr_d = (t_thread *)data;
	j = thr_d->thread_nb * (SCREEN_HEIGHT / NUM_THREADS) - 1;
	jmax = (thr_d->thread_nb + 1) * (SCREEN_HEIGHT / NUM_THREADS);
	while (++j < jmax)
	{
		i = -1;
		while (++i < SCREEN_WIDTH)
		{
			if ((*((int*)thr_d->d->addr + i + j * thr_d->d->l_size_4)) == 0x000000)
				pxput(thr_d->d, i, j, get_point_color(thr_d->d->iter_nb, ((i - thr_d->d->x_offset) / thr_d->d->zoom)
					+ ((j - thr_d->d->y_offset) / thr_d->d->zoom) * I, thr_d->d->c + cos(thr_d->d->x) * thr_d->d->y + sin(thr_d->d->x) * thr_d->d->y * I));
		}
	}
	return (NULL);
}

static void	draw_img(t_fractol *d)
{
	pthread_t	threads[NUM_THREADS];
	t_thread	threads_data[NUM_THREADS];

	int			i;

	i = 0;
	while (i < NUM_THREADS)
	{
		threads_data[i].thread_nb = i;
		threads_data[i].d = d;
		if (pthread_create(&threads[i], NULL, &draw_img_part_by_thread, (void *)&(threads_data[i])))
			exit(EXIT_FAILURE);
		i++;
	}
	i = 0;
	while (i < NUM_THREADS)
	{
		if (pthread_join(threads[i], NULL))
			exit(EXIT_FAILURE);
		i++;
	}

/*	if (--process_nb < 0)
		return ;
	pid = fork();
	if (pid == 0)
	{
	//	return (draw_img_part(d, process_nb * (SCREEN_HEIGHT / PROCESS_NB), (process_nb + 1) * (SCREEN_HEIGHT / PROCESS_NB)));
	}
	else
	{
		wait(&pid);
		draw_img(d, process_nb);
	}*/
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
		if (d->keys & ~(k_p_KP_7 | k_p_KP_9))
		{
			mlx_destroy_image(d->mlx, d->img);
			d->img = mlx_new_image(d->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
			d->addr = mlx_get_data_addr(d->img, &d->bpp, &d->l_size, &d->endian);
		}
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
