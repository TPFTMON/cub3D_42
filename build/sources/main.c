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

	// PARSING IS HAPPENING HERE -> DATA FOR ENGINE WRITTEN TO STRUCT
	parse_cub_file(cube, argv[1]);

    // test for player and map
	test_ALL_engine(cube);

	init_player(cube);

	//parsing_report();
	//engine_report();
	//char	*miaou = "\e[1;35mMiaou miaou miaou miaou miaou\e[0m\n";
	//ft_strlen(miaou);
	//printf("%s", miaou);

	// THEN THE ENGINE DOES HIS GAME_LOOP
	setup_mlx_and_engine(cube);
	return (OKI);
}

void	setup_mlx_and_engine(t_cube *cube)
{
	init_mlx_cube(cube);
	init_hooks(cube);
	mlx_loop(cube->mlx_ptr);
}
