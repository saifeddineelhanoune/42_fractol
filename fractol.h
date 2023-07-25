/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-hano <sel-hano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 03:26:17 by sel-hano          #+#    #+#             */
/*   Updated: 2023/07/25 21:31:24 by sel-hano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdlib.h>
# include <mlx.h>
# include <math.h>
# include <unistd.h>
# include <stdio.h>
# include <stdbool.h>

# define WIDTH 800
# define HEIGHT 800
# define MAX_ITER 100
# define ESCAPE_RADIUS 2.0
# define ESC_KEY 53
# define MOUSE_LEFT 1
# define ARROW_UP 126
# define ARROW_DOWN 125
# define ARROW_LEFT 123
# define ARROW_RIGHT 124

typedef struct s_complex
{
	double		real;
	double		imaginary;
}t_complex;

typedef struct s_data {
	t_complex	c;
	void		*img;
	char		*addr;
	void		*mlx_ptr;
	void		*win_ptr;
	int			bits_per_pixel;
	int			size_line;
	int			endian;
	double		min_x;
	double		max_x;
	double		min_y;
	double		max_y;
	double		zoom_factor;
	double		x_holder;
	double		y_holder;
	double		step_size;
	double		center_x;
	double		center_y;
	int			iterations;
	int			color;
	int			x;
	int			y;
	char		*s;
	int			fraction_length;
	double		result;
	double		fraction;
	int			negative;
}t_data;

typedef enum s_fractals
{
	mandelbrot = 1,
	julia,
	mandeljul,
}t_fractals;

void		ft_mlx_pixel_put(t_data *data, int x, int y, int color);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
void		fractals_rendring(t_data *init);
int			handle_mouse_wheel(int button, int x, int y, t_data *init);
int			handle_keys_press(int button, t_data *init);
int			button_cross(t_data *init);
int			check_julia_args(t_data *init, char *av[], int ac);
void		ft_error(int ac, char *av[]);
void		zoom_in(t_data *init);
void		zoom_out(t_data *init);
char		*mini_atod(t_data *init, const char *str);

#endif