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
void    test_set_player(t_cube *cube);
void	test_fill_grid(t_map *map, int width, int height);
void    print_grid(t_map *map);

int	main(int argc, char **argv)
{
	t_cube	*cube;

	(void)argc;
	(void)argv;
	cube = init_data_cube();
	// PARSING IS HAPPENING HERE
	// +
	// DATA FOR ENGINE WRITTEN TO STRUCT
    test_set_ceil_floor(cube);
    // test for player and map
    test_fill_grid(&cube->map, 10, 10);
    test_set_player(cube);
    print_grid(&cube->map);
    init_player(cube);

	parsing_report();
	engine_report();

	char	*miaou = "\e[1;35mMiaou miaou miaou miaou miaou\e[0m\n";
	ft_strlen(miaou);
	printf("%s", miaou);
	// THEN THE ENGINE DOES HIS GAME_LOOP
	// Here we init the window
	init_mlx_cube(cube);
	// Then hooks with the game_loop inside
	init_hooks(cube);

	mlx_loop(cube->mlx_ptr);

	// ft_cleanup(cube);
	return (OKI);
}

void    test_set_ceil_floor(t_cube *cube){
    int R_c,G_c,B_c;

    R_c = 128;    // 20 | 41 | 14
    G_c = 128;   // 63 | 240 | 48
    B_c = 128;   // 235 | 207 | 183
    cube->map.color_ceil = ((R_c << 16) | (G_c << 8) | B_c);

    int R_f,G_f,B_f;
    R_f = 32;    // 21 | 240 |
    G_f = 32;   // 155 | 41 |
    B_f = 32;   // 0 | 240 |
    cube->map.color_floor = ((R_f << 16) | (G_f << 8) | B_f);
}

void    test_set_player(t_cube *cube){
    cube->map.player_direction = SO;

    // Giving the player a valid starting position
    // (width / 2) + 0.5 centers them in the middle tile
    // cube->player.pos_x = (double)cube->map.width / 2.0 + 0.5;
    // cube->player.pos_y = (double)cube->map.height / 2.0 + 0.5;

    cube->player.pos_x = 6.5;
    cube->player.pos_y = 7.5;


    if (cube->map.grid[(int)cube->player.pos_y][(int)cube->player.pos_x] == '1'){
        cube->player.pos_x += 1.0; // Shift them slightly if they spawned in a wall
    }
}

void	test_fill_grid(t_map *map, int width, int height){
    int	i;
    int	j;
    if (width < 3 || height < 3)
        return ;
    map->width = width;
    map->height = height;
    map->grid = (char **)malloc(sizeof(char *) * (height + 1));
    if (!map->grid){
        perror("malloc");
        exit(EXC_CRIT);
    }
    map->grid[height] = NULL;
    i = 0;
    while (i < height){
        map->grid[i] = (char *)malloc(width + 1);
        if (!map->grid[i]){
            while (--i >= 0)
                free(map->grid[i]);
            free(map->grid);
            perror("malloc");
            exit(EXC_CRIT);
        }
        j = 0;
        while (j < width){
            if (i == 0 || i == height - 1 || j == 0 || j == width - 1)
                map->grid[i][j] = '1';
            else
                map->grid[i][j] = '0';
            j++;
        }
        map->grid[i][width] = '\0';
        i++;
    }
    map->grid[height / 2][width / 2] = '1'; // single center wall
}

void    print_grid(t_map *map){
    for (int i = 0; map->grid[i]; i++){
        for (int j = 0; map->grid[i][j]; j++){
            printf("%c", map->grid[i][j]);
        }
        printf("\n");
    }
}
