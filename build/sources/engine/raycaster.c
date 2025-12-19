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

void perform_raycasting(t_cube *cube){
    int x;
    t_ray ray;

    x = 0;
    while (x < WIN_WIDTH)
    {
        init_ray(&ray, cube);

        run_dda(&ray, cube);

        calculate_wall_height(&ray, cube);

        render_wall_strip(&ray, cube);

        x++;
    }
}

// void perform_raycasting(t_cube *cube){

    // In the loop for columns x from 0 to WIN_WIDTH:

    //    1. Calculate ray vectors

    //    2. Run the DDA (to find the wall)

    //    3. Calculate distance (perpendicular) and wall height

    //    4. Texture math

    //    5. Draw the vertical line
// }
