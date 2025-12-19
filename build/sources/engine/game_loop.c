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

void perform_raycasting(t_cube *cube);
void update_player(t_cube *cube);

int	game_loop(void *arg){
	t_cube		*cube;

	cube = (t_cube *)arg;

    // 1. Draw the background (ceiling + floor)
    draw_ceiling_floor(&cube->screen, cube->map.color_ceil, cube->map.color_floor);

    // 1. Do the whole raycasting + textures:
    // perform_raycasting(cube);

	// 2. Put the ready image to the window
	mlx_put_image_to_window(cube->mlx_ptr, cube->win_ptr, cube->screen.img_ptr, 0, 0);

    // 3. Update the logic (move player based on relative time and the keys pressed)
	// update_player(cube);

	return (0);
}

void perform_raycasting(t_cube *cube){
    (void)cube;
    // In the loop for columns x from 0 to WIN_WIDTH:

    //    1. Calculate ray vectors

    //    2. Run the DDA (to find the wall)

    //    3. Calculate distance (perpendicular) and wall height

    //    4. Texture math

    //    5. Draw the vertical line
}

void update_player(t_cube *cube){
	long long	current_time;
	double		effective_move_speed;
	double		effective_rot_speed;

    // 1. Relative movement updates
	//    1.1. Update the last_frame_time for smooth movement
	if (cube->last_frame_time == 0)
		cube->last_frame_time = get_time_in_ms();
	current_time = get_time_in_ms();

    //    1.2. Calculate delta_time
	//    setting delta_time and converting to seconds instead of ms:
	cube->delta_time = ((current_time - cube->last_frame_time) / 1000.0);

	//    1.3. Set effective move/rot speed from it
	effective_move_speed = cube->player.move_speed * cube->delta_time;
	effective_rot_speed = cube->player.rot_speed * cube->delta_time;

    // 2. Update player's position
    //    update_positon():
    //    2.1.

    // 3. Update player's point of view
    //    update_view():
    //    3.1.
}
