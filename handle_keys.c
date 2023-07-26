/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-hano <sel-hano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 04:34:36 by sel-hano          #+#    #+#             */
/*   Updated: 2023/07/27 00:21:30 by sel-hano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	button_cross(t_data *init)
{
	mlx_destroy_image(init->mlx_ptr, init->img);
	mlx_destroy_window(init->mlx_ptr, init->win_ptr);
	exit(EXIT_SUCCESS);
	return (0);
}

int	handle_key_press(int button, t_data *init)
{
	init->step_size = 0.025;
	if (button == ARROW_LEFT)
	{
		init->max_x += init->step_size;
		init->min_x += init->step_size;
	}
	else if (button == ARROW_RIGHT)
	{
		init->max_x -= init->step_size;
		init->min_x -= init->step_size;
	}
	else if (button == ARROW_UP)
	{
		init->max_y += init->step_size;
		init->min_y += init->step_size;
	}
	else if (button == ARROW_DOWN)
	{
		init->max_y -= init->step_size;
		init->min_y -= init->step_size;
	}
	mlx_clear_window(init->mlx_ptr, init->win_ptr);
	fractals_rendring(init);
	return (0);
}

int	handle_keys_press(int button, t_data *init)
{
	if (button == ESC_KEY)
	{
		mlx_destroy_image(init->mlx_ptr, init->img);
		mlx_destroy_window(init->mlx_ptr, init->win_ptr);
		exit(EXIT_SUCCESS);
	}
	if (button == ARROW_RIGHT
		|| button == ARROW_LEFT
		|| button == ARROW_UP
		|| button == ARROW_DOWN)
		handle_key_press(button, init);
	return (0);
}

double	ft_strtod(const char *str, t_data *init)
{
	init->fraction_length = 0;
	init->result = 0.0;
	init->fraction = 0.0;
	init->negative = 1;
	str = (const char *)mini_atod(init, str);
	if (*str == '.')
	{
		str++;
		while (*str && *str != '.' && *(str) >= '0' && *str <= '9')
		{
			init->fraction = init->fraction * 10.0 + (*str - '0');
			init->fraction_length++;
			str++;
		}
		if (*str)
		{
			write(1, "BAD ARGUMENTS PLEASE WRITE NUMBERS OF TYPE DOUBLE\n", 50);
			exit(EXIT_FAILURE);
		}
	}
	init->result += init->fraction / pow(10.0, init->fraction_length);
	return (init->result * init->negative);
}

int	check_julia_args(t_data *init, char *av[], int ac)
{
	if ((ac != 2 && ac != 4) && !ft_strcmp(av[1], "julia"))
	{
		write(1, "BAD ARGUMENTS PLEASE WRITE REAL IMAG\n", 38);
		exit(EXIT_FAILURE);
	}
	else if (ac == 4 && !ft_strcmp(av[1], "julia"))
	{
		init->x_holder = ft_strtod(av[2], init);
		init->y_holder = ft_strtod(av[3], init);
		if ((init->x_holder < -2.0 || init->x_holder > 2.0)
			&& (init->y_holder < -2.0 || init->y_holder > 2.0))
		{
			write(1, "THE INTERVAL SET IS [-2.0, 2.0]", 31);
			exit(EXIT_FAILURE);
		}
	}
	else if ((ac != 4
			&& !ft_strcmp(av[1], "julia")))
	{
		init->x_holder = -0.70176;
		init->y_holder = 0.3842;
	}
	return (0);
}
