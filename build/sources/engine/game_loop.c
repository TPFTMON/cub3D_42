/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 04:29:11 by abaryshe          #+#    #+#             */
/*   Updated: 2025/11/02 07:33:02 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	game_loop(void *arg)
{
	t_cube	*cube;

	cube = (t_cube *)arg;
	// 1. Update the logic (move player based on the keys pressed)
	// update_player(cube);
	//    player_movement:
	//    1.1. Move the player with w,s,a,d keys
	//    1.2. Rotate the point of view with lar,rar keys

	// 2. Render all pixels (ceiling, floor, walls)
	// render_pixels(cube);

	// 3. Put the ready image to the window
	mlx_put_image_to_window(cube->mlx_ptr, cube->win_ptr, cube->screen.img_ptr, 0, 0);

	return (0);
}
