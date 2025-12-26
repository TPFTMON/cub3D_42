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

void		*free_cube(t_cube *cube);
void		*free_mlx(t_cube *cube);

// Purpose: Clean all the memory and destroy mlx components
int	ft_cleanup(t_cube *cube)
{
	if (!cube)
		return (FAIL);
	free_mlx(cube);
	free_cube(cube);
	return (OKI);
}

static void	destroy_image(t_cube *cube, t_img *image)
{
	if (image->img_ptr && cube->mlx_ptr)
	{
		mlx_destroy_image(cube->mlx_ptr, image->img_ptr);
		image->img_ptr = NULL;
	}
}

void	*free_mlx(t_cube *cube)
{
	destroy_image(cube, &cube->screen);
	destroy_image(cube, &cube->textures[NO]);
	destroy_image(cube, &cube->textures[SO]);
	destroy_image(cube, &cube->textures[EA]);
	destroy_image(cube, &cube->textures[WE]);
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
	return (NULL);
}

void	*free_cube(t_cube *cube)
{
	if (cube->map.grid)
		free_string_array(cube->map.grid);
	if (cube)
		free(cube);
	return (NULL);
}
