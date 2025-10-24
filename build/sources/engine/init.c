/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 07:12:45 by abaryshe          #+#    #+#             */
/*   Updated: 2025/10/24 07:46:23 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	init_mlx_cube(t_cube *cube)
{
	if (cube == NULL)
		return (print_error_with_code(NULL, "cube is NULL\n", CRITICAL));
	cube->mlx_ptr = mlx_init();
	if (!cube->mlx_ptr)
		return (print_error_with_code("mlx_init",
				"Failed to initialize MiniLibX\n", CRITICAL));
	cube->win_ptr = mlx_new_window(cube->mlx_ptr, cube->win_width,
			cube->win_height, "cube");
	if (!cube->win_ptr)
		return (print_error_with_code("mlx_new_window",
				"Failed to create window\n", CRITICAL));
	cube->screen.img_ptr = mlx_new_image(cube->mlx_ptr, cube->win_width,
			cube->win_height);
	if (!cube->screen.img_ptr)
		return (print_error_with_code("mlx_new_image",
				"Failed to create image buffer\n", CRITICAL));
	cube->screen.addr = mlx_get_data_addr(cube->screen.img_ptr,
			&cube->screen.bpp, &cube->screen.line_len, &cube->screen.endian);
	if (!cube->screen.addr)
		return (print_error_with_code("mlx_get_data_addr",
				"Failed to get image data address\n", CRITICAL));
	return (OKAY);
}
