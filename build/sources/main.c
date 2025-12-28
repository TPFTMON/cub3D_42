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

	// WE DON'T HAVE A CHECK FOR NOT A .cub FILE
	if (argc != 2 || ft_strcmp(".cub", ft_strrchr(argv[1], '.')))
		handle_error("Correct format: ./cub3D <map.cub>");
	cube = init_data_cube();
	if (!cube)
		return (EXC_CRIT);
	if (!parse_cub_file(cube, argv[1]))
	{
		parser_perror_and_setexit(cube);
		ft_cleanup(cube);
		return (EXC_PARS);
	}
	//printf("has_spawn=%d spawn=(%d, %d) dir=%d\n", cube->map.has_spawn, cube->map.spawn_x, cube->map.spawn_y, cube->map.player_direction);
	print_grid(&cube->map);
	init_player(cube);
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
