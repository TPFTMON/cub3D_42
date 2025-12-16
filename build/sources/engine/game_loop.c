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

int	game_loop(void *arg)
{
	t_cube		*cube;
	// long long	current_time;
	// double		effective_move_speed;
	// double		effective_rot_speed;

	cube = (t_cube *)arg;

	// // 1. Relative movement updates
	// //    1.1. Update the last_frame_time for smooth movement
	// //    1.2. Calculate delta_time
	// //    1.3. Also set effective move/rot speed from it
	// if (cube->last_frame_time == 0)
	// 	cube->last_frame_time = get_time_in_ms();
	// current_time = get_time_in_ms();

	// // setting delta_time and converting to seconds instead of ms:
	// cube->delta_time = ((current_time - cube->last_frame_time) / 1000);

	// effective_move_speed = cube->player.move_speed * cube->delta_time;
	// effective_rot_speed = cube->player.rot_speed * cube->delta_time;

	// 2. Update the logic (move player based on the keys pressed)
	// update_player(cube);
	//    player_movement:
	//    2.1. Move the player with w,s,a,d keys
	//    2.2. Rotate the point of view with lar,rar keys

	// 3. Render all pixels (ceiling, floor, walls)
	render_pixels(cube);

	// 4. Put the ready image to the window
	mlx_put_image_to_window(cube->mlx_ptr, cube->win_ptr, cube->screen.img_ptr, 0, 0);

	return (0);
}
