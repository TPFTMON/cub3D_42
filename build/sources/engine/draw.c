/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 04:27:05 by abaryshe          #+#    #+#             */
/*   Updated: 2025/12/16 15:24:10 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// offset = (y × line_len) + (x × (bits_per_pixel / 8))
void    my_pixel_put(t_img *img, int x, int y, int color){
    char *dest;

    if (x < 0 || x > WIN_WIDTH || y < 0 || y > WIN_HEIGHT)
        return ;
    dest = img->addr + ((y * img->line_len) + (x * (img->bpp / 8)));
    *(unsigned int*)dest = color;
}

void    draw_ceiling_floor(t_img *img, int ceil_col, int floor_col){
    int x, y;

    x = 0;
    y = 0;
    while (y < WIN_HEIGHT / 2){
        while (x < WIN_WIDTH){
            my_pixel_put(img, x, y, ceil_col);
            x++;
        }
        y++;
    }

    x = 0;
    y = WIN_HEIGHT / 2;
    while (y < WIN_HEIGHT){
        while (x < WIN_WIDTH){
            my_pixel_put(img, x, y, floor_col);
            x++;
        }
        y++;
    }
}
