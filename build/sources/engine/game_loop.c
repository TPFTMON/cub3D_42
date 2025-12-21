/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 04:29:11 by abaryshe          #+#    #+#             */
/*   Updated: 2025/12/16 15:17:00 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	game_loop(void *arg){
	t_cube		*cube;

	cube = (t_cube *)arg;

    // 1. Draw the background (ceiling + floor)
    draw_ceiling_floor(&cube->screen, cube->map.color_ceil, cube->map.color_floor);

    // 1. Do the whole raycasting + textures:
    perform_raycasting(cube);

	// 2. Put the ready image to the window
	mlx_put_image_to_window(cube->mlx_ptr, cube->win_ptr, cube->screen.img_ptr, 0, 0);

    // 3. Update the logic (move player based on relative time and the keys pressed)
	update_player(cube);

	return (0);
}
