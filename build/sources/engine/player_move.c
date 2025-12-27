/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 04:26:11 by abaryshe          #+#    #+#             */
/*   Updated: 2025/12/27 13:02:29 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	move_player_forward(t_cube *cube, double effective_move_speed)
{
	double	speed;
	double	new_x;
	double	new_y;

	if (cube->key_a || cube->key_d)
		effective_move_speed /= 2;
	speed = effective_move_speed;
	new_x = cube->player.pos_x + cube->player.dir_x * speed;
	new_y = cube->player.pos_y + cube->player.dir_y * speed;
	if (cube->map.grid[(int)cube->player.pos_y][(int)new_x] != '1')
		cube->player.pos_x = new_x;
	if (cube->map.grid[(int)new_y][(int)cube->player.pos_x] != '1')
		cube->player.pos_y = new_y;
}

void	move_player_backward(t_cube *cube, double effective_move_speed)
{
	double	speed;
	double	new_x;
	double	new_y;

	if (cube->key_a || cube->key_d)
		effective_move_speed /= 2;
	speed = effective_move_speed;
	new_x = cube->player.pos_x - cube->player.dir_x * speed;
	new_y = cube->player.pos_y - cube->player.dir_y * speed;
	if (cube->map.grid[(int)cube->player.pos_y][(int)new_x] != '1')
		cube->player.pos_x = new_x;
	if (cube->map.grid[(int)new_y][(int)cube->player.pos_x] != '1')
		cube->player.pos_y = new_y;
}

void	move_player_left(t_cube *cube, double effective_move_speed)
{
	double	speed;
	double	new_x;
	double	new_y;

	speed = effective_move_speed;
	new_x = cube->player.pos_x + cube->player.dir_y * speed;
	new_y = cube->player.pos_y - cube->player.dir_x * speed;
	if (cube->map.grid[(int)cube->player.pos_y][(int)new_x] != '1')
		cube->player.pos_x = new_x;
	if (cube->map.grid[(int)new_y][(int)cube->player.pos_x] != '1')
		cube->player.pos_y = new_y;
}

void	move_player_right(t_cube *cube, double effective_move_speed)
{
	double	speed;
	double	new_x;
	double	new_y;

	speed = effective_move_speed;
	new_x = cube->player.pos_x - cube->player.dir_y * speed;
	new_y = cube->player.pos_y + cube->player.dir_x * speed;
	if (cube->map.grid[(int)cube->player.pos_y][(int)new_x] != '1')
		cube->player.pos_x = new_x;
	if (cube->map.grid[(int)new_y][(int)cube->player.pos_x] != '1')
		cube->player.pos_y = new_y;
}

// void	move_player_forward(t_cube *cube)
// {
// 	double	speed;
// 	double	new_x;
// 	double	new_y;

// 	speed = cube->player.move_speed * cube->delta_time;
// 	new_x = cube->player.pos_x + cube->player.dir_x * speed;
// 	new_y = cube->player.pos_y + cube->player.dir_y * speed;
// 	if (cube->map.grid[(int)cube->player.pos_y][(int)new_x] != '1')
// 		cube->player.pos_x = new_x;
// 	if (cube->map.grid[(int)new_y][(int)cube->player.pos_x] != '1')
// 		cube->player.pos_y = new_y;
// }

// void	move_player_backward(t_cube *cube)
// {
// 	double	speed;
// 	double	new_x;
// 	double	new_y;

// 	speed = cube->player.move_speed * cube->delta_time;
// 	new_x = cube->player.pos_x - cube->player.dir_x * speed;
// 	new_y = cube->player.pos_y - cube->player.dir_y * speed;
// 	if (cube->map.grid[(int)cube->player.pos_y][(int)new_x] != '1')
// 		cube->player.pos_x = new_x;
// 	if (cube->map.grid[(int)new_y][(int)cube->player.pos_x] != '1')
// 		cube->player.pos_y = new_y;
// }

// void	move_player_left(t_cube *cube)
// {
// 	double	speed;
// 	double	new_x;
// 	double	new_y;

// 	speed = cube->player.move_speed * cube->delta_time;
// 	new_x = cube->player.pos_x + cube->player.dir_y * speed;
// 	new_y = cube->player.pos_y - cube->player.dir_x * speed;
// 	if (cube->map.grid[(int)cube->player.pos_y][(int)new_x] != '1')
// 		cube->player.pos_x = new_x;
// 	if (cube->map.grid[(int)new_y][(int)cube->player.pos_x] != '1')
// 		cube->player.pos_y = new_y;
// }

// void	move_player_right(t_cube *cube)
// {
// 	double	speed;
// 	double	new_x;
// 	double	new_y;

// 	speed = cube->player.move_speed * cube->delta_time;
// 	new_x = cube->player.pos_x - cube->player.dir_y * speed;
// 	new_y = cube->player.pos_y + cube->player.dir_x * speed;
// 	if (cube->map.grid[(int)cube->player.pos_y][(int)new_x] != '1')
// 		cube->player.pos_x = new_x;
// 	if (cube->map.grid[(int)new_y][(int)cube->player.pos_x] != '1')
// 		cube->player.pos_y = new_y;
// }
