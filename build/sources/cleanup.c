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
    free_string_array(cube->map.grid);
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

// void	*free_cube(t_cube *cube)
// {
	// free all the stuff that needs to be freed. Like map or something
    // free_string_array(cube->map.grid);
    // int	i;
//
	// if (!cube->map.grid)
		// return (NULL);
	// i = 0;
	// while (cube->map.grid[i])
		// i++;
	// while (i >= 0)
	// {
		// free(cube->map.grid[i]);
		// cube->map.grid[i] = NULL;
		// i--;
	// }
	// free(cube->map.grid);
	// if (cube)
		// free(cube);
	// return (NULL);
// }
