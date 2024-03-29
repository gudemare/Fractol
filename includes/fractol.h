/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gudemare <gudemare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/20 22:33:45 by gudemare          #+#    #+#             */
/*   Updated: 2017/09/20 18:24:05 by gudemare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <math.h>
# include <complex.h>
# include "libft.h"
# include "mlx.h"

# define DOUBLE_COMPLEX double complex
# define SCREEN_WIDTH 800
# define SCREEN_HEIGHT 600
# define NUM_THREADS 60
# define HEIGHT_BY_THREAD SCREEN_HEIGHT / NUM_THREADS

typedef	int	(*t_fractal)(const int, const DOUBLE_COMPLEX, const DOUBLE_COMPLEX);

typedef struct	s_fractol
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*addr;
	int				bpp;
	int				endian;
	int				l_size;
	int				l_size_4;
	double			x_offset;
	double			y_offset;
	int				iter_nb;
	int				mouse_change;
	double			zoom;
	DOUBLE_COMPLEX	z_pow;
	double			color_mod;
	int				keys;
	int				*bitshifts;
	int				mouse_x;
	int				mouse_y;
	t_fractal		fract_func;
}				t_fractol;

typedef struct	s_thread
{
	int			thread_nb;
	t_fractol	*d;
}				t_thread;

# define MAX_KEYCODE 269

enum			e_keycodes
{
	k_KEY_A = 0,
	k_KEY_S = 1,
	k_KEY_G = 5,
	k_KEY_C = 8,
	k_KEY_B = 11,
	k_KEY_R = 15,
	k_NUM_1 = 18,
	k_NUM_2 = 19,
	k_NUM_3 = 20,
	k_NUM_4 = 21,
	k_NUM_6 = 22,
	k_NUM_5 = 23,
	k_NUM_9 = 25,
	k_NUM_7 = 26,
	k_NUM_8 = 28,
	k_NUM_0 = 29,
	k_SPACE = 49,
	k_ESC = 53,
	k_KP_F = 67,
	k_KP_P = 69,
	k_KP_D = 75,
	k_KP_M = 78,
	k_KP_0 = 82,
	k_KP_1 = 83,
	k_KP_2 = 84,
	k_KP_3 = 85,
	k_KP_4 = 86,
	k_KP_5 = 87,
	k_KP_6 = 88,
	k_KP_7 = 89,
	k_KP_8 = 91,
	k_KP_9 = 92,
	k_LEFT = 123,
	k_RIGHT = 124,
	k_DOWN = 125,
	k_UP = 126,
	k_CTRL_L = 256,
	k_SHIFT_L = 257,
	k_SHIFT_R = 258,
	k_CTRL_R = 269,
};

enum			e_mousecodes
{
	k_LeftButton = 1,
	k_RightButton = 2,
	k_ScrollUp = 4,
	k_ScrollDown = 5
};
enum			e_events
{
	k_KeyPress = 2,
	k_KeyRelease = 3,
	k_ButtonPress = 4,
	k_ButtonRelease = 5,
	k_MotionNotify = 6,
	k_KeyPressMask = (1L << 0),
	k_KeyReleaseMask = (1L << 1),
	k_ButtonPressMask = (1L << 2),
	k_ButtonReleaseMask = (1L << 3),
	k_ButtonMotionMask = (1L << 13)
};

enum			e_keys_pressed
{
	k_p_KEY_A = 1 << 1,
	k_p_KEY_S = 1 << 2,
	k_p_KP_P = 1 << 3,
	k_p_KP_M = 1 << 4,
	k_p_KP_1 = 1 << 5,
	k_p_KP_2 = 1 << 6,
	k_p_KP_3 = 1 << 7,
	k_p_KP_4 = 1 << 8,
	k_p_KP_5 = 1 << 9,
	k_p_KP_6 = 1 << 10,
	k_p_KP_7 = 1 << 11,
	k_p_KP_8 = 1 << 12,
	k_p_KP_9 = 1 << 13,
	k_p_LEFT = 1 << 14,
	k_p_RIGHT = 1 << 15,
	k_p_DOWN = 1 << 16,
	k_p_UP = 1 << 17,
	k_p_MOUSE_LEFT = 1 << 18,
	k_p_MOUSE_RIGHT = 1 << 19,
	k_p_NOT_DRAWN = 1 << 32
};

void			init_values(t_fractol *d);
int				fractol_loop(void *param);
void			quit(t_fractol *d);

int				handle_button_release(int button, int x, int y, void *param);
int				handle_button_press(int button, int x, int y, void *param);
int				handle_mouse_movement(int x, int y, void *param);
int				handle_key_press(int x_event, void *param);
int				handle_key_release(int x_event, void *param);

int				get_value_mandelbrot(const int iter_nb,
		const DOUBLE_COMPLEX c, const DOUBLE_COMPLEX z_pow);
int				get_value_julia(const int iter_nb,
		const DOUBLE_COMPLEX c, const DOUBLE_COMPLEX z_pow);
int				get_value_burning_ship(const int iter_nb,
		const DOUBLE_COMPLEX c, const DOUBLE_COMPLEX z_pow);
#endif
