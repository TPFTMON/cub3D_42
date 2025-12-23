/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 07:12:45 by abaryshe          #+#    #+#             */
/*   Updated: 2025/11/01 09:16:54 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_cube	*init_data_cube()
{
	t_cube	*cube;

	cube = (t_cube *)ft_calloc(1, sizeof(t_cube));
	if (!cube)
	{
		print_error_with_code("cub3D", ERR_CRITICAL, CRITICAL);
		return (NULL);
	}

	return (cube);
}

int	init_mlx_cube(t_cube *cube)
{
	// if (!cube)
	// 	return (print_error_with_code(NULL, "cube is NULL\n", CRITICAL));

	printf("Entered init_mlx_cude:\n");
	cube->mlx_ptr = mlx_init();
	if (!cube->mlx_ptr)
		return (print_error_with_code("cub3D: mlx_init",
				"Failed to initialize MiniLibX\n", CRITICAL));
	printf("mlx_ptr: [%p]\n", cube->mlx_ptr);

	cube->win_ptr = mlx_new_window(cube->mlx_ptr, WIN_WIDTH,
			WIN_HEIGHT, "cube");
	if (!cube->win_ptr)
		return (print_error_with_code("cub3D: mlx_new_window",
				"Failed to create window\n", CRITICAL));
	printf("win_ptr: [%p]\n", cube->win_ptr);

	cube->screen.img_ptr = mlx_new_image(cube->mlx_ptr, WIN_WIDTH,
			WIN_HEIGHT);
	if (!cube->screen.img_ptr)
		return (print_error_with_code("cub3D: mlx_new_image",
				"Failed to create image buffer\n", CRITICAL));
	printf("screen.img_ptr: [%p]\n", cube->screen.img_ptr);

	cube->screen.addr = mlx_get_data_addr(cube->screen.img_ptr,
			&cube->screen.bpp, &cube->screen.line_len, &cube->screen.endian);
	if (!cube->screen.addr)
		return (print_error_with_code("cub3D: mlx_get_data_addr",
				"Failed to get image data address\n", CRITICAL));
	printf("screen.addr: [%p]\n", cube->screen.addr);
	return (OKI);
}

void    init_player(t_cube *cube)
{
    if (cube->map.player_direction == NO)
    {
        cube->player.dir_x = 0;
        cube->player.dir_y = -1;
        cube->player.plane_x = 0.66; // Perpendicular to (0, -1) is (1, 0)
        cube->player.plane_y = 0;
    }
    else if (cube->map.player_direction == SO)
    {
        cube->player.dir_x = 0;
        cube->player.dir_y = 1;
        cube->player.plane_x = -0.66;
        cube->player.plane_y = 0;
    }
    else if (cube->map.player_direction == EA)
    {
        cube->player.dir_x = 1;
        cube->player.dir_y = 0;
        cube->player.plane_x = 0;
        cube->player.plane_y = 0.66;
    }
    else if (cube->map.player_direction == WE)
    {
        cube->player.dir_x = -1;
        cube->player.dir_y = 0;
        cube->player.plane_x = 0;
        cube->player.plane_y = -0.66;
    }
    cube->player.move_speed = 0.01;
    cube->player.rot_speed = 0.01;
}

// static void	init_t_imgs(t_cube *cube);

// t_cube	*init_data_cube(/*int argc, char **argv*/)
// {
// 	t_cube	*cube;

// 	cube = (t_cube *)malloc(sizeof(t_cube));
// 	if (!cube)
// 		return (print_error_with_code("cub3D", ERR_CRITICAL, EXC_CRIT));
// 	ft_bzero(cube, sizeof(t_cube));
// 	cube->mlx_ptr = NULL;
// 	cube->win_height = NULL;
// 	cube->win_width = 0;
// 	cube->win_height = 0;

// 	init_t_imgs(cube);
// 	cube->floor_color = 0;
// 	cube->ceil_color = 0;



// 	cube->key_w = 0;
// 	cube->key_s = 0;
// 	cube->key_a = 0;
// 	cube->key_d = 0;
// 	cube->key_lar = 0;
// 	cube->key_rar = 0;

// 	cube->delta_time = 0;
// }

// static void	init_t_imgs(t_cube *cube)
// {
// 	int	i = 0;

// 	cube->screen.img_ptr = NULL;
// 	cube->screen.addr = NULL;
// 	cube->screen.bpp = 0;
// 	cube->screen.line_len = 0;
// 	cube->screen.endian = 0;
// 	cube->screen.width = 0;
// 	cube->screen.height = 0;

// 	while (i < TEX_NB)
// 	{
// 		cube->textures[i].img_ptr = NULL;
// 		cube->textures[i].addr = NULL;
// 		cube->textures[i].bpp = 0;
// 		cube->textures[i].line_len = 0;
// 		cube->textures[i].endian = 0;
// 		cube->textures[i].width = 0;
// 		cube->textures[i].height = 0;
// 		i++;
// 	}
// }

// static void	init_t_player(t_cube *cube)
// {}

// static void	init_t_map(t_cube *cube)
// {}
