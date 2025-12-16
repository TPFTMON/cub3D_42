/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 04:28:51 by abaryshe          #+#    #+#             */
/*   Updated: 2025/12/16 15:05:19 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void    render_pixels(t_cube *cube){

    draw_ceiling_floor(&cube->screen, cube->map.color_ceil, cube->map.color_floor);

    // ...
}
