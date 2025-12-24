/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 21:57:17 by abaryshe          #+#    #+#             */
/*   Updated: 2025/12/16 15:18:35 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	setup_mlx_and_engine(t_cube *cube);

int	main(int argc, char **argv)
{
	t_cube	*cube;

	//(void)argc;
	//(void)argv;
	if (argc != 2)
		handle_error("Correct format: ./cub3D <map.cub>");
	cube = init_data_cube();
	if (!cube)
		return (EXC_CRIT);

	parse_cub_file(cube, argv[1]);

    // test for player and map
	// test_ALL_engine(cube);
	print_grid(&cube->map);

	init_player(cube);

	// THEN THE ENGINE DOES HIS GAME_LOOP
	setup_mlx_and_engine(cube);
	return (OKI);
}

void	setup_mlx_and_engine(t_cube *cube)
{
	if (init_mlx_cube(cube) != OKI)
	{
		ft_cleanup(cube);
		return ;
	}
	if (init_textures(cube) != OKI)
	{
		ft_cleanup(cube);
		return ;
	}
	init_hooks(cube);
	mlx_loop(cube->mlx_ptr);
}
