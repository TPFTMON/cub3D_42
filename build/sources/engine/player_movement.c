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

static void	move_player_forward(t_cube *cube);
static void	move_player_backward(t_cube *cube);
static void	move_player_left(t_cube *cube);
static void	move_player_right(t_cube *cube);

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
}

void	move_player_forward(t_cube *cube)
{

}

void	move_player_backward(t_cube *cube)
{

}

void	move_player_left(t_cube *cube)
{

}

void	move_player_right(t_cube *cube)
{

}

