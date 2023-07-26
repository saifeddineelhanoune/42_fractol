/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-hano <sel-hano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 03:40:58 by sel-hano          #+#    #+#             */
/*   Updated: 2023/07/27 00:22:35 by sel-hano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>

double	complex_abs(t_complex c, int flag)
{
	if (flag)
		return (sqrt((c.imaginary * c.imaginary) + c.real * c.real));
	return (sqrt(-(c.imaginary * c.imaginary) + c.real * c.real));
}

int	my_fractal_calcul(t_data *init)
{
	t_complex	z;
	t_complex	temp;

	z.real = 0;
	z.imaginary = 0;
	init->iterations = 0;
	while (init->iterations < MAX_ITER && (complex_abs(z, 1) < ESCAPE_RADIUS))
	{
		temp = z;
		z.real = fabs(pow(temp.real, 2) - \
		pow(temp.imaginary, 2) + init->c.real);
		z.imaginary = fabs(2 * temp.real * temp.imaginary + init->c.imaginary);
		init->iterations++;
	}
	return (init->iterations);
}

int	julia_calcul(t_data *init)
{
	t_complex	z;
	t_complex	temp;

	z.real = init->c.real;
	z.imaginary = init->c.imaginary;
	init->iterations = 0;
	while (init->iterations < MAX_ITER && (complex_abs(z, 1) < ESCAPE_RADIUS))
	{
		temp = z;
		z.real = pow(temp.real, 2) - pow(temp.imaginary, 2) + init->x_holder;
		z.imaginary = 2 * temp.real * temp.imaginary + init->y_holder;
		init->iterations++;
	}
	return (init->iterations);
}

int	mandelbrot_calcul(t_data *init)
{
	t_complex	z;
	t_complex	temp;

	z.real = 0;
	z.imaginary = 0;
	init->iterations = 0;
	while (init->iterations < MAX_ITER && (complex_abs(z, 1) < ESCAPE_RADIUS))
	{
		temp = z;
		z.real = pow(temp.real, 2) - pow(temp.imaginary, 2) + init->c.real;
		z.imaginary = 2 * temp.real * temp.imaginary + init->c.imaginary;
		init->iterations++;
	}
	return (init->iterations);
}

void	fractals_rendring(t_data *init)
{
	init->y = 0;
	while (init->y < HEIGHT)
	{
		init->x = 0;
		while (init->x < WIDTH)
		{
			init->c.real = init->min_x + init->x
				* (init->max_x - init->min_x) / WIDTH;
			init->c.imaginary = init->min_y + init->y
				* (init->max_y - init->min_y) / HEIGHT;
			if (!ft_strcmp(init->s, "mandelbrot"))
				init->iterations = mandelbrot_calcul(init);
			else if (!ft_strcmp(init->s, "julia"))
				init->iterations = julia_calcul(init);
			else if (!ft_strcmp(init->s, "burningship"))
				init->iterations = my_fractal_calcul(init);
			init->color = init->iterations * 800;
			ft_mlx_pixel_put(init, init->x, init->y, init->color);
			init->x++;
		}
		init->y++;
	}
	mlx_put_image_to_window(init->mlx_ptr, init->win_ptr, init->img, 0, 0);
}
