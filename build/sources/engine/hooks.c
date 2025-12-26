/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 04:29:48 by abaryshe          #+#    #+#             */
/*   Updated: 2025/12/16 14:49:58 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	on_destroy(void *arg)
{
	t_cube	*cube;

	cube = (t_cube *)arg;
	ft_cleanup(cube);
	printf(MSG_EXIT);
	exit(EXC_OK);
	return (OKI);
}

int	on_key_press(int keycode, void *arg)
{
	t_cube	*cube;

	cube = (t_cube *)arg;
	if (keycode == KEY_ESC)
		on_destroy(cube);
	if (keycode == KEY_W)
		cube->key_w = 1;
	if (keycode == KEY_S)
		cube->key_s = 1;
	if (keycode == KEY_A)
		cube->key_a = 1;
	if (keycode == KEY_D)
		cube->key_d = 1;
	if (keycode == KEY_LAR)
		cube->key_lar = 1;
	if (keycode == KEY_RAR)
		cube->key_rar = 1;
	return (OKI);
}

int	on_key_release(int keycode, void *arg)
{
	t_cube	*cube;

	cube = (t_cube *)arg;
	if (keycode == KEY_W)
		cube->key_w = 0;
	if (keycode == KEY_S)
		cube->key_s = 0;
	if (keycode == KEY_A)
		cube->key_a = 0;
	if (keycode == KEY_D)
		cube->key_d = 0;
	if (keycode == KEY_LAR)
		cube->key_lar = 0;
	if (keycode == KEY_RAR)
		cube->key_rar = 0;
	return (OKI);
}

void	init_hooks(t_cube *cube)
{
	mlx_hook(cube->win_ptr, 17, 0, on_destroy, cube);
	mlx_hook(cube->win_ptr, 2, (1L << 0), on_key_press, cube);
	mlx_hook(cube->win_ptr, 3, (1L << 1), on_key_release, cube);
	mlx_loop_hook(cube->mlx_ptr, game_loop, cube);
}
