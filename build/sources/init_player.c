/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 16:34:15 by abaryshe          #+#    #+#             */
/*   Updated: 2025/12/23 16:34:27 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void		set_player_direction(t_cube *cube);
void		set_player_position(t_cube *cube);

void	init_player(t_cube *cube)
{
	set_player_direction(cube);
	set_player_position(cube);
	cube->player.move_speed = MOVE_SPEED;
	cube->player.rot_speed = ROT_SPEED;
}

static void	set_north_south(t_cube *cube)
{
	cube->player.dir_x = 0;
	cube->player.plane_y = 0;
	if (cube->map.player_direction == NO)
	{
		cube->player.dir_y = -1;
		cube->player.plane_x = 0.66;
	}
	else if (cube->map.player_direction == SO)
	{
		cube->player.dir_y = 1;
		cube->player.plane_x = -0.66;
	}
}

static void	set_east_west(t_cube *cube)
{
	cube->player.dir_y = 0;
	cube->player.plane_x = 0;
	if (cube->map.player_direction == EA)
	{
		cube->player.dir_x = 1;
		cube->player.plane_y = 0.66;
	}
	else if (cube->map.player_direction == WE)
	{
		cube->player.dir_x = -1;
		cube->player.plane_y = -0.66;
	}
}

void	set_player_direction(t_cube *cube)
{
	if (cube->map.player_direction == NO || cube->map.player_direction == SO)
		set_north_south(cube);
	if (cube->map.player_direction == EA || cube->map.player_direction == WE)
		set_east_west(cube);
}

void	set_player_position(t_cube *cube)
{
	int		x;
	int		y;
	bool	is_player;

	is_player = 0;
	y = 0;
	while (cube->map.grid[y] && !is_player)
	{
		x = 0;
		while (cube->map.grid[y][x] && !is_player)
		{
			if (cube->map.grid[y][x] == 'N' || cube->map.grid[y][x] == 'S'
				|| cube->map.grid[y][x] == 'E' || cube->map.grid[y][x] == 'W')
				is_player = true;
			x++;
		}
		y++;
	}
	cube->player.pos_x = (double)x - 0.5;
	cube->player.pos_y = (double)y - 0.5;
	if (cube->map.grid[(int)cube->player.pos_y][(int)cube->player.pos_x] == '1')
		cube->player.pos_x += 1.0;
}

// if (cube->map.player_direction == NO)
// {
// cube->player.dir_x = 0;
// cube->player.dir_y = -1;
// cube->player.plane_x = 0.66; // Perpendicular to (0, -1) is (1, 0)
// cube->player.plane_y = 0;
// }
// else if (cube->map.player_direction == SO)
// {
// cube->player.dir_x = 0;
// cube->player.dir_y = 1;
// cube->player.plane_x = -0.66;
// cube->player.plane_y = 0;
// }
// if (cube->map.player_direction == EA)
// {
// cube->player.dir_x = 1;
// cube->player.dir_y = 0;
// cube->player.plane_x = 0;
// cube->player.plane_y = 0.66;
// }
// else if (cube->map.player_direction == WE)
// {
// cube->player.dir_x = -1;
// cube->player.dir_y = 0;
// cube->player.plane_x = 0;
// cube->player.plane_y = -0.66;
// }
