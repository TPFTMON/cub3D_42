// #include "cub3D.h"

// void	test_ALL_engine(t_cube *cube){
// 	test_set_ceil_floor(cube);
//     test_fill_grid(&cube->map, 10, 10);
//     // test_set_player(cube);
//     test_set_position_on_grid(cube, 1, 8);
//     print_grid(&cube->map);
// }

// void    test_set_ceil_floor(t_cube *cube){
//     int R_c,G_c,B_c;

//     R_c = 128;    // 20 | 41 | 14
//     G_c = 128;   // 63 | 240 | 48
//     B_c = 128;   // 235 | 207 | 183
//     cube->map.color_ceil = ((R_c << 16) | (G_c << 8) | B_c);

//     int R_f,G_f,B_f;
//     R_f = 32;    // 21 | 240 |
//     G_f = 32;   // 155 | 41 |
//     B_f = 32;   // 0 | 240 |
//     cube->map.color_floor = ((R_f << 16) | (G_f << 8) | B_f);
// }

// void	test_fill_grid(t_map *map, int width, int height){
//     int	i;
//     int	j;
//     if (width < 3 || height < 3)
//         return ;
//     map->width = width;
//     map->height = height;
//     map->grid = (char **)malloc(sizeof(char *) * (height + 1));
//     if (!map->grid){
//         perror("malloc");
//         exit(EXC_CRIT);
//     }
//     map->grid[height] = NULL;
//     i = 0;
//     while (i < height){
//         map->grid[i] = (char *)malloc(width + 1);
//         if (!map->grid[i]){
//             while (--i >= 0)
//                 free(map->grid[i]);
//             free(map->grid);
//             perror("malloc");
//             exit(EXC_CRIT);
//         }
//         j = 0;
//         while (j < width){
//             if (i == 0 || i == height - 1 || j == 0 || j == width - 1)
//                 map->grid[i][j] = '1';
//             else
//                 map->grid[i][j] = '0';
//             j++;
//         }
//         map->grid[i][width] = '\0';
//         i++;
//     }
//     map->grid[height / 2][width / 2] = '1'; // single center wall
// }

// void    print_grid(t_map *map){
//     if (!map->raw)
//         return ;
//     for (int i = 0; map->raw[i]; i++){
//         for (int j = 0; map->raw[i][j]; j++){
//             printf("%c", map->raw[i][j]);
//         }
//         printf("\n");
//     }
//     printf("---\n");
//     if (!map->grid)
//         return ;
//     for (int i = 0; map->grid[i]; i++){
//         for (int j = 0; map->grid[i][j]; j++){
//             printf("%c", map->grid[i][j]);
//         }
//         printf("\n");
//     }
// }

// void    test_set_position_on_grid(t_cube *cube, int x, int y){
// 	cube->map.player_direction = NO;
//     if (cube->map.grid[y][x] != '1' /*&& x < cube->map.width && y < cube->map.height*/)
//         cube->map.grid[y][x] = 'N';
//     else
// 		printf("WRONG VALUE FOR POSITION, BRO\n");

// }

// void    render_test_flat_color(t_ray *ray, int x, t_cube *cube)
// {
//     int color;

//     // Determine color based on side and direction
//     if (ray->side == 0) // Hit a vertical grid line
//     {
//         if (ray->dir_x > 0)
//             color = 0x00FF00; // Green (East-facing wall)
//         else
//             color = 0xFF0000; // Red (West-facing wall)
//     }
//     else // Hit a horizontal grid line
//     {
//         if (ray->dir_y > 0)
//             color = 0xFFFF00; // Yellow (South-facing wall)
//         else
//             color = 0x0000FF; // Blue (North-facing wall)
//     }

//     // Draw the vertical line
//     int y = ray->draw_start;
//     while (y <= ray->draw_end)
//     {
//         my_pixel_put(&cube->screen, x, y, color);
//         y++;
//     }
// }

// void    test_set_player(t_cube *cube){
//     // Giving the player a valid starting position
//     // (width / 2) + 0.5 centers them in the middle tile
//     // cube->player.pos_x = (double)cube->map.width / 2.0 + 0.5;
//     // cube->player.pos_y = (double)cube->map.height / 2.0 + 0.5;

//     cube->player.pos_x = 1.5;
//     cube->player.pos_y = 8.5;

//     if (cube->map.grid[(int)cube->player.pos_y][(int)cube->player.pos_x] == '1'){
//         cube->player.pos_x += 1.0; // Shift them slightly if they spawned in a wall
//     }
// }
