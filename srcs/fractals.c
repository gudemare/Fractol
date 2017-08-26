/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudemare <gudemare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/25 00:23:49 by gudemare          #+#    #+#             */
/*   Updated: 2017/08/26 07:57:25 by gudemare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <complex.h>
#include "fractol.h"

int		get_value_mandelbrot(const int iter_nb, const DOUBLE_COMPLEX c,
		const DOUBLE_COMPLEX z_pow)
{
	DOUBLE_COMPLEX		z;
	int					iter;
	double				real;
	double				imag;

	z = 0 + 0 * I;
	iter = 0;
	(void)z_pow;
	while (iter++ < iter_nb)
	{
		z = z * z + c;
		real = creal(z);
		imag = cimag(z);
		if (real * real + imag * imag >= 4.0f)
			return (iter * 0x012345);
	}
	return (0x000000);
}

int		get_value_julia(const int iter_nb, const DOUBLE_COMPLEX c,
		const DOUBLE_COMPLEX z_pow)
{
	DOUBLE_COMPLEX		z;
	int					iter;
	double				real;
	double				imag;

	z = c;
	iter = 0;
	while (iter++ < iter_nb)
	{
		z = z * z + z_pow;
		real = creal(z);
		imag = cimag(z);
		if (real * real + imag * imag >= 4.0f)
			return (iter * 0x012345);
	}
	return (0x000000);
}

int		get_value_burning_ship(const int iter_nb, const DOUBLE_COMPLEX c,
		const DOUBLE_COMPLEX z_pow)
{
	DOUBLE_COMPLEX		z;
	int					iter;
	double				real;
	double				imag;

	if (cabs(c) > 2.0f)
		return (0x012345);
	z = 0;
	iter = 0;
	(void)z_pow;
	while (iter++ < iter_nb)
	{
		real = fabs(creal(z));
		imag = fabs(cimag(z));
		z = real + I * imag;
		z = z * z + c;
		if (real * real + imag * imag >= 4.0f)
			return (iter * 0x012345);
	}
	return (0x000000);
}
