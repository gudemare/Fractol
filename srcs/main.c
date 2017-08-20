/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudemare <gudemare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/11 02:47:44 by gudemare          #+#    #+#             */
/*   Updated: 2017/08/21 00:08:33 by gudemare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <math.h>
#include "fractol.h"

static void	init_bitshifts(t_fractol *d)
{
	int		i;

	ft_assert(d->bitshifts = (int *)malloc(sizeof(int *) * (MAX_KEYCODE + 1)));
	i = 0;
	while (i <= MAX_KEYCODE)
		d->bitshifts[i++] = 0;
	d->bitshifts[k_KEY_A] = k_p_KEY_A;
	d->bitshifts[k_KEY_S] = k_p_KEY_S;
	d->bitshifts[k_KP_M] = k_p_KP_M;
	d->bitshifts[k_KP_P] = k_p_KP_P;
	d->bitshifts[k_KP_1] = k_p_KP_1;
	d->bitshifts[k_KP_2] = k_p_KP_2;
	d->bitshifts[k_KP_3] = k_p_KP_3;
	d->bitshifts[k_KP_4] = k_p_KP_4;
	d->bitshifts[k_KP_5] = k_p_KP_5;
	d->bitshifts[k_KP_6] = k_p_KP_6;
	d->bitshifts[k_KP_7] = k_p_KP_7;
	d->bitshifts[k_KP_8] = k_p_KP_8;
	d->bitshifts[k_KP_9] = k_p_KP_9;
	d->bitshifts[k_LEFT] = k_p_LEFT;
	d->bitshifts[k_RIGHT] = k_p_RIGHT;
	d->bitshifts[k_DOWN] = k_p_DOWN;
	d->bitshifts[k_UP] = k_p_UP;
	d->bitshifts[k_SHIFT_R] = k_p_SHIFT_R;
	d->bitshifts[k_CTRL_R] = k_p_CTRL_R;
}

void		init_values(t_fractol *d)
{
	d->zoom = 1.0f;
	d->y_offset = SCREEN_HEIGHT / 2;
	d->x_offset = SCREEN_WIDTH / 2;
	d->l_size_4 = d->l_size / 4;
	d->keys = k_p_NOT_DRAWN;
	d->color_mod = 1;
	d->iter_nb = 5;
	d->c = 10000;
}

int			main(int ac, char **av)
{
	t_fractol	d;

	if (ac != 2)
	{
		ft_putstr_fd("usage : ./fractol <map file>\n", 2);
		return (-1);
	}
	(void)av;
	d.mlx = mlx_init();
	d.win = mlx_new_window(d.mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "fractol");
	d.img = mlx_new_image(d.mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	d.addr = mlx_get_data_addr(d.img, &d.bpp, &d.l_size, &d.endian);
	init_values(&d);
	init_bitshifts(&d);
	mlx_hook(d.win, k_KeyPress, k_KeyPressMask,
			&handle_key_press, &d);
	mlx_hook(d.win, k_KeyRelease, k_KeyReleaseMask,
			&handle_key_release, &d);
	mlx_loop_hook(d.mlx, &fractol_loop, &d);
	mlx_loop(d.mlx);
	return (0);
}
