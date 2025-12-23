/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 21:57:17 by abaryshe          #+#    #+#             */
/*   Updated: 2025/11/05 15:29:48 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int argc, char **argv)
{
	t_cube	*cube;

	//(void)argc;
	//(void)argv;
	if (argc != 2)
		handle_error("Correct format: ./cub3D <map.cub>");
	cube = init_data_cube();
	if (!cube)//maybe useless
		return (1);//maybe useless
	// PARSING IS HAPPENING HERE
	// +
	// DATA FOR ENGINE WRITTEN TO STRUCT
	//parsing_report();
	parse_cub_file(cube, argv[1]);
	//engine_report();

	//char	*miaou = "\e[1;35mմյաու մյաու մյաու մյաու մյաու\e[0m\n";
	//ft_strlen(miaou);
	//printf("%s", miaou);
	// THEN THE ENGINE DOES HIS GAME LOOP
	// Here we init the window
	init_mlx_cube(cube);
	// Then hooks with the game_loop inside
	init_hooks(cube);

	mlx_loop(cube->mlx_ptr);
	ft_cleanup(cube);
	return (OKI);
}
