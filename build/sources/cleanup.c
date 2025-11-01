/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 06:47:34 by abaryshe          #+#    #+#             */
/*   Updated: 2025/11/01 08:55:59 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	*free_cube(t_cube *cube)
{
	// free all the stuff that needs to be freed. Like map or something
	if (cube)
		free(cube);
	return (NULL);
}

/*
 * Main cleanup function. Frees cube data and destroys MiniLibX components.
 */
int	ft_cleanup(t_cube *cube)
{
	if (!cube)
		return (FAIL);
	if (cube->screen.img_ptr && cube->mlx_ptr)
	{
		mlx_destroy_image(cube->mlx_ptr, cube->screen.img_ptr);
		cube->screen.img_ptr = NULL;
	}
	if (cube->win_ptr && cube->mlx_ptr)
	{
		mlx_destroy_window(cube->mlx_ptr, cube->win_ptr);
		cube->win_ptr = NULL;
	}
	if (cube->mlx_ptr)
	{
		mlx_destroy_display(cube->mlx_ptr);
		free(cube->mlx_ptr);
		cube->mlx_ptr = NULL;
	}
	free_cube(cube);
	return (OKI);
}
