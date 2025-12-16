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

void    test_set_ceil_floor(t_cube *cube);

int	main(int argc, char **argv)
{
	t_cube	*cube;

	(void)argc;
	(void)argv;
	cube = init_data_cube();
	// PARSING IS HAPPENING HERE
	// +
	// DATA FOR ENGINE WRITTEN TO STRUCT
	parsing_report();
	engine_report();

	char	*miaou = "\e[1;35mմյաու մյաու մյաու մյաու մյաու\e[0m\n";
	ft_strlen(miaou);
	printf("%s", miaou);
	// THEN THE ENGINE DOES HIS GAME LOOP
	// Here we init the window
	init_mlx_cube(cube);
	// Then hooks with the game_loop inside
	init_hooks(cube);

    test_set_ceil_floor(cube);

	mlx_loop(cube->mlx_ptr);
	ft_cleanup(cube);
	return (OKI);
}

void    test_set_ceil_floor(t_cube *cube){
    int R_c,G_c,B_c;

    R_c = 41;
    G_c = 240;
    B_c = 207;
    cube->map.color_ceil = ((R_c << 16) | (G_c << 8) | B_c);

    int R_f,G_f,B_f;
    R_f = 240;
    G_f = 41;
    B_c = 240;
    cube->map.color_ceil = ((R_f << 16) | (G_f << 8) | B_f);

}
