/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_zoom.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sel-hano <sel-hano@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 03:59:49 by sel-hano          #+#    #+#             */
/*   Updated: 2023/07/27 00:19:35 by sel-hano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

void	ft_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->size_line + x * (data->bits_per_pixel / 8));
	*((unsigned int *)dst) = color;
}

void	zoom_fractal(t_data *init, int zoom_x, int zoom_y, char flag)
{
	init->center_x = init->min_x
		+ (init->max_x - init->min_x) * zoom_x / WIDTH;
	init->center_y = init->min_y
		+ (init->max_y - init->min_y) * zoom_y / HEIGHT;
	if (flag == '1')
		zoom_in(init);
	else
		zoom_out(init);
}

int	handle_mouse_wheel(int button, int x, int y, t_data *init)
{
	init->zoom_factor = 0.5;
	if (button == 5)
		zoom_fractal(init, x, y, '0');
	else if (button == 4)
		zoom_fractal(init, x, y, '1');
	mlx_clear_window(init->mlx_ptr, init->win_ptr);
	fractals_rendring(init);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	init;

	ft_error(ac, av);
	init.min_x = -2.0;
	init.max_x = 2.0;
	init.min_y = -2.0;
	init.max_y = 2.0;
	init.s = av[1];
	check_julia_args(&init, av, ac);
	init.mlx_ptr = mlx_init();
	init.win_ptr = mlx_new_window(init.mlx_ptr, WIDTH, HEIGHT, av[1]);
	init.img = mlx_new_image(init.mlx_ptr, WIDTH, HEIGHT);
	init.addr = mlx_get_data_addr(init.img, &init.bits_per_pixel,
			&init.size_line, &init.endian);
	fractals_rendring(&init);
	mlx_hook(init.win_ptr, 4, 0, &handle_mouse_wheel, &init);
	mlx_key_hook(init.win_ptr, &handle_keys_press, &init);
	mlx_hook(init.win_ptr, 17, 0, &button_cross, &init);
	mlx_loop(init.mlx_ptr);
	return (0);
}
