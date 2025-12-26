/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_view.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 19:06:53 by abaryshe          #+#    #+#             */
/*   Updated: 2025/12/21 19:06:54 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	shift_view_left(t_cube *cube)
{
	double	rot_speed;
	double	old_dir_x;
	double	old_plane_x;

	rot_speed = cube->player.rot_speed /* * cube->delta_time*/;
	old_dir_x = cube->player.dir_x;
	old_plane_x = cube->player.plane_x;
	cube->player.dir_x = cube->player.dir_x * cos(-rot_speed)
		- cube->player.dir_y * sin(-rot_speed);
	cube->player.dir_y = old_dir_x * sin(-rot_speed) + cube->player.dir_y
		* cos(-rot_speed);
	cube->player.plane_x = cube->player.plane_x * cos(-rot_speed)
		- cube->player.plane_y * sin(-rot_speed);
	cube->player.plane_y = old_plane_x * sin(-rot_speed) + cube->player.plane_y
		* cos(-rot_speed);
}

void	shift_view_right(t_cube *cube)
{
	double	rot_speed;
	double	old_dir_x;
	double	old_plane_x;

	rot_speed = cube->player.rot_speed /* * cube->delta_time*/;
	old_dir_x = cube->player.dir_x;
	old_plane_x = cube->player.plane_x;
	cube->player.dir_x = cube->player.dir_x * cos(rot_speed)
		- cube->player.dir_y * sin(rot_speed);
	cube->player.dir_y = old_dir_x * sin(rot_speed) + cube->player.dir_y
		* cos(rot_speed);
	cube->player.plane_x = cube->player.plane_x * cos(rot_speed)
		- cube->player.plane_y * sin(rot_speed);
	cube->player.plane_y = old_plane_x * sin(rot_speed) + cube->player.plane_y
		* cos(rot_speed);
}
