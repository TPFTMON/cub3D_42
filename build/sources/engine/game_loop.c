/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 04:29:11 by abaryshe          #+#    #+#             */
/*   Updated: 2025/12/27 12:54:44 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	game_loop(void *arg)
{
	t_cube	*cube;

	cube = (t_cube *)arg;
	draw_ceiling_floor(&cube->screen, cube->map.color_ceil,
		cube->map.color_floor);
	perform_raycasting(cube);
	mlx_put_image_to_window(cube->mlx_ptr, cube->win_ptr, cube->screen.img_ptr,
		0, 0);
	update_player(cube);
	return (0);
}

void	update_player(t_cube *cube)
{
	if (cube->key_w)
		move_player_forward(cube);
	if (cube->key_s)
		move_player_backward(cube);
	if (cube->key_a)
		move_player_left(cube);
	if (cube->key_d)
		move_player_right(cube);
	if (cube->key_lar)
		shift_view_left(cube);
	if (cube->key_rar)
		shift_view_right(cube);
}
