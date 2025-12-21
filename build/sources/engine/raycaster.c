/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 04:29:22 by abaryshe          #+#    #+#             */
/*   Updated: 2025/10/23 04:29:23 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void    init_ray(t_ray *ray, int x, t_cube *cube);
void    find_wall_dda(t_ray *ray, t_cube *cube);
void    calculate_wall_height(t_ray *ray/*, t_cube *cube*/);
// void    render_wall_strip(t_ray *ray, int x, t_cube *cube);
void    render_test_flat_color(t_ray *ray, int x, t_cube *cube);

void perform_raycasting(t_cube *cube){
    int x;
    t_ray ray;

    x = 0;
    while (x < WIN_WIDTH)
    {
        init_ray(&ray, x, cube);

        find_wall_dda(&ray, cube);

        calculate_wall_height(&ray/*, cube*/);

        // render_wall_strip(&ray, x, cube);
        // render_test_flat_color(&ray, x, cube);

        x++;
    }
}

// Purpose: Calculate dir, delta_dist, step, and initial side_dist
void    init_ray(t_ray *ray, int x, t_cube *cube){
    ray->map_x = cube->player.pos_x;
    ray->map_y = cube->player.pos_y;

    ray->camera_x = 2 * x / (double)WIN_WIDTH - 1;

    ray->dir_x = cube->player.dir_x + cube->player.plane_x * ray->camera_x;
    ray->dir_y = cube->player.dir_y + cube->player.plane_y * ray->camera_x;

    ray->delta_dist_x = fabs(1 / ray->dir_x); // division by 0 (?)
    ray->delta_dist_y = fabs(1 / ray->dir_y);

    if (ray->dir_x < 0){
        ray->step_x = -1;
        ray->side_dist_x = (cube->player.pos_x - ray->map_x) * ray->delta_dist_x;
    } else {
        ray->step_x = 1;
        ray->side_dist_x = (ray->map_x + 1.0 - cube->player.pos_x) * ray->delta_dist_x;
    }
    if (ray->dir_y < 0){
        ray->step_y = -1;
        ray->side_dist_y = (cube->player.pos_y - ray->map_y) * ray->delta_dist_y;
    } else {
        ray->step_y = 1;
        ray->side_dist_y = (ray->map_y + 1.0 - cube->player.pos_y) * ray->delta_dist_y;
    }
}

// Purpose: Loop until wall is hit
void    find_wall_dda(t_ray *ray, t_cube *cube){
    (void)cube;

    int hit = 0;
    while (hit == 0)
    {
        if (ray->side_dist_x < ray->side_dist_y)
        {
            ray->side_dist_x += ray->delta_dist_x;
            ray->map_x += ray->step_x;
            ray->side = 0;
        }
        else
        {
            ray->side_dist_y += ray->delta_dist_y;
            ray->map_y += ray->step_y;
            ray->side = 1;
        }
        // if (cube->map.grid[ray->map_y][ray->map_x] == '1')
            hit = 1;
    }
}

// Purpose: Calculate wall height :)
void    calculate_wall_height(t_ray *ray/*, t_cube *cube*/){
    // ray->perp_wall_dist = (ray->map_x - cube->player.pos_x + (1 - ray->step_x) / 2) / ray->dir_x; // More safe approach

    if (ray->side == 0)
        ray->perp_wall_dist = (ray->side_dist_x - ray->delta_dist_x);
    else
        ray->perp_wall_dist = (ray->side_dist_y - ray->delta_dist_y);

    ray->line_height = (int)WIN_HEIGHT / ray->perp_wall_dist;

    ray->draw_start = -ray->line_height / 2 + WIN_HEIGHT / 2;
    if (ray->draw_start < 0){
        ray->draw_start = 0;
    }

    ray->draw_end = ray->line_height / 2 + WIN_HEIGHT / 2;
    if (ray->draw_end > WIN_HEIGHT){
        ray->draw_end = WIN_HEIGHT - 1;
    }
}

void    render_test_flat_color(t_ray *ray, int x, t_cube *cube)
{
    int color;

    // Determine color based on side and direction
    if (ray->side == 0) // Hit a vertical grid line
    {
        if (ray->dir_x > 0)
            color = 0x00FF00; // Green (East-facing wall)
        else
            color = 0xFF0000; // Red (West-facing wall)
    }
    else // Hit a horizontal grid line
    {
        if (ray->dir_y > 0)
            color = 0x0000FF; // Blue (South-facing wall)
        else
            color = 0xFFFF00; // Yellow (North-facing wall)
    }

    // Draw the vertical line
    int y = ray->draw_start;
    while (y <= ray->draw_end)
    {
        my_pixel_put(&cube->screen, x, y, color);
        y++;
    }
}

// Purpose: Calculate exactly what pixel of the texture to paint and paint it
// (For now I want it to just paint different sides of the walls in different colors)
// void    render_wall_strip(t_ray *ray, int x, t_cube *cube){

// }

// void perform_raycasting(t_cube *cube){

    // In the loop for columns x from 0 to WIN_WIDTH:

    //    1. Calculate ray vectors

    //    2. Run the DDA (to find the wall)

    //    3. Calculate distance (perpendicular) and wall height

    //    4. Texture math

    //    5. Draw the vertical line
// }
