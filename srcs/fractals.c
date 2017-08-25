/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudemare <gudemare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/25 00:23:49 by gudemare          #+#    #+#             */
/*   Updated: 2017/08/25 02:04:42 by gudemare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <complex.h>
#include "fractol.h"

int		get_value_mandelbrot(const int iter_nb, const float complex c,
		const float complex z_pow)
{
	float complex		z;
	int					iter;
	float				real;
	float				imag;

	if (cabsl(c) > 2.0f)
		return (0x012345);
	z = 0 + 0 * I;
	iter = 0;
	while (iter++ < iter_nb)
	{
		z = cpow(z, z_pow) + c;
		real = crealf(z);
		imag = cimagf(z);
		if (real * real + imag * imag >= 4.0f)
			return (iter * 0x012345);
	}
	return (0x000000);
}

int		get_value_julia(const int iter_nb, const float complex c,
		const float complex z_pow)
{
	float complex		z;
	int					iter;
	float				real;
	float				imag;

	z = c;
	iter = 0;
	while (iter++ < iter_nb)
	{
		z = z * z + z_pow;
		real = crealf(z);
		imag = cimagf(z);
		if (real * real + imag * imag >= 4.0f)
			return (iter * 0x012345);
	}
	return (0x000000);
}

int		get_value_burning_ship(const int iter_nb, const float complex c,
		const float complex z_pow)
{
	float complex		z;
	int					iter;
	float				real;
	float				imag;

	z = 0;
	iter = 0;
	while (iter++ < iter_nb)
	{
		real = fabs(crealf(z));
		imag = fabs(cimagf(z));
		z = real + I * imag;
		z = z * z + c;
		if (real * real + imag * imag >= 4.0f)
			return (iter * 0x012345);
	}
	return (0x000000);
}
