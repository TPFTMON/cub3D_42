/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 21:57:17 by abaryshe          #+#    #+#             */
/*   Updated: 2025/11/01 08:14:45 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int argc, char **argv)
{
	t_cube	*cube = NULL;

	(void)argc;
	(void)argv;
	cube = init_cube_data();
	// PARSING IS HAPPENING HERE
	// +
	// DATA FOR ENGINE WRITTEN TO STRUCT
	parsing_report();
	engine_report();

	char	*miaou = "\e[1;32mմյաու մյաու մյաու մյաու մյաու\e[0m\n";
	ft_strlen(miaou);
	printf("%s", miaou);
	printf("[%p]\n", cube->mlx_ptr);
	// THEN THE ENGINE DOES HIS GAME LOOP
	// Here we init the window
	init_cube_mlx(cube);
	// Then hooks
	init_hooks(cube);
	mlx_loop(cube->mlx_ptr);
	ft_cleanup(cube);
	return (OKI);
}
