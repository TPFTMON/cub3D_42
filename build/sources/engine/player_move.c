/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 04:26:11 by abaryshe          #+#    #+#             */
/*   Updated: 2025/11/02 07:38:27 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	move_player_forward(t_cube *cube);
void	move_player_backward(t_cube *cube);
void	move_player_left(t_cube *cube);
void	move_player_right(t_cube *cube);
void    shift_view_left(t_cube *cube);
void    shift_view_right(t_cube *cube);

void	update_player(t_cube *cube)
{
	long long	current_time;
	double		effective_move_speed;
	double		effective_rot_speed;

	if (cube->last_frame_time == 0)
		cube->last_frame_time = get_time_in_ms();
	current_time = get_time_in_ms();

	cube->delta_time = ((current_time - cube->last_frame_time) / 1000.0);

	effective_move_speed = cube->player.move_speed * cube->delta_time;
	effective_rot_speed = cube->player.rot_speed * cube->delta_time;

	if (cube->key_w)
		move_player_forward(cube);
	// if (cube->key_s)
		// move_player_backward(cube);
	// if (cube->key_a)
		// move_player_left(cube);
	// if (cube->key_d)
		// move_player_right(cube);
    // if (cube->key_lar)
        // shift_view_left(cube);
    // if (cube->key_rar)
        // shift_view_right(cube);
}

void	move_player_forward(t_cube *cube)
{
    double  speed = cube->player.move_speed * cube->delta_time;
    double  new_x = cube->player.pos_x + cube->player.dir_x * speed;
    double  new_y = cube->player.pos_y + cube->player.dir_y * speed;

    // Basic Collision: Check if new spot is a wall ('1')
    if (cube->map.grid[(int)cube->player.pos_y][(int)new_x] != '1')
        cube->player.pos_x = new_x;
    if (cube->map.grid[(int)new_y][(int)cube->player.pos_x] != '1')
        cube->player.pos_y = new_y;
}

// void	move_player_backward(t_cube *cube)
// {

// }

// void	move_player_left(t_cube *cube)
// {

// }

// void	move_player_right(t_cube *cube)
// {

// }
