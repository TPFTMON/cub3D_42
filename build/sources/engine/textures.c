/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 04:27:17 by abaryshe          #+#    #+#             */
/*   Updated: 2025/10/23 04:27:18 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static t_img	*get_texture(t_cube *cube, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->dir_x > 0)
			return (&cube->textures[EA]);
		else
			return (&cube->textures[WE]);
	}
	else
	{
		if (ray->dir_y > 0)
			return (&cube->textures[SO]);
		else
			return (&cube->textures[NO]);
	}
}

void	render_wall_strip(t_ray *ray, int x, t_cube *cube)
{
	t_render	render;

	render.texture = get_texture(cube, ray);
	if (ray->side == 0)
		render.wall_x = cube->player.pos_y + ray->perp_wall_dist * ray->dir_y;
	else
		render.wall_x = cube->player.pos_x + ray->perp_wall_dist * ray->dir_x;
	render.wall_x -= floor(render.wall_x);
	render.tex_x = (int)(render.wall_x * (double)render.texture->width);
	if (ray->side == 0 && ray->dir_x > 0)
		render.tex_x = render.texture->width - render.tex_x - 1;
	if (ray->side == 1 && ray->dir_y < 0)
		render.tex_x = render.texture->width - render.tex_x - 1;
	render.step = 1.0 * render.texture->height / ray->line_height;
	render.tex_pos = (ray->draw_start - WIN_HEIGHT / 2 + ray->line_height / 2)
		* render.step;
	render.y = ray->draw_start;
	while (render.y < ray->draw_end)
	{
		render.tex_y = (int)render.tex_pos % render.texture->height;
		render.tex_pos += render.step;
		render.color = get_pcolor(render.texture, render.tex_x, render.tex_y);
		my_pixel_put(&cube->screen, x, render.y, render.color);
		render.y++;
	}
}
