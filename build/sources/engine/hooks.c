/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 04:29:48 by abaryshe          #+#    #+#             */
/*   Updated: 2025/11/01 09:19:53 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	on_destroy(void *arg)
{
	t_cube *cube;

	cube = (t_cube *)arg;

	ft_cleanup(cube);
	printf(MSG_EXIT);
	exit(EXC_OK);

	return (OKI);
}

int	on_key_press(int keycode, void *arg)
{
	t_cube *cube;

	cube = (t_cube *)arg;

	if (keycode == KEY_ESC)
		on_destroy(cube);

	if (keycode == KEY_W)
		cube->key_w = 1;
	if (keycode == KEY_S)
		cube->key_w = 1;
	if (keycode == KEY_A)
		cube->key_w = 1;
	if (keycode == KEY_D)
		cube->key_w = 1;
	if (keycode == KEY_LAR)
		cube->key_w = 1;
	if (keycode == KEY_RAR)
		cube->key_w = 1;

	// Print the keycode to find out what other keys are
	printf("The key pressed: [%d]\n", keycode);

	return (OKI);
}

int	on_key_release(int keycode, void *arg)
{
	t_cube *cube;

	cube = (t_cube *)arg;
	if (keycode == KEY_W)
		cube->key_w = 0;
	if (keycode == KEY_S)
		cube->key_w = 0;
	if (keycode == KEY_A)
		cube->key_w = 0;
	if (keycode == KEY_D)
		cube->key_w = 0;
	if (keycode == KEY_LAR)
		cube->key_w = 0;
	if (keycode == KEY_RAR)
		cube->key_w = 0;

	return (OKI);
}

void	init_hooks(t_cube *cube)
{
	/*
	 * mlx_hook for the RED CROSS
	 * 17 = DestroyNotify (the red cross event)
	 * 0 = NoEventMask (this is special for DestroyNotify)
	 * on_destroy = on destroy event function
	 * cube = the (void *) param to pass to your function
	 */
	mlx_hook(cube->win_ptr, 17, 0, on_destroy, cube);

	/*
	 * mlx_hook for KEY PRESS
	 * 2 = KeyPress event
	 * (1L<<0) = KeyPressMask
	 * on_key_press = on press event function
	 * cube = your param
	 */
	mlx_hook(cube->win_ptr, 2, (1L<<0), on_key_press, cube);

	/*
	 * mlx_hook for KEY RELEASE
	 * 3 = KeyRelease event
	 * (1L<<1) = KeyReleaseMask
	 * on_key_release = on release event funtion
	 * cube = your param
	 */
	mlx_hook(cube->win_ptr, 3, (1L<<1), on_key_release, cube);

	/*
	 * Located in game_loop.c
	 * as it is, arguably,
	 * the most important hook
	 */
	mlx_loop_hook(cube->mlx_ptr, game_loop, cube);
}
