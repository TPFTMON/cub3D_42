/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/24 01:36:40 by abaryshe          #+#    #+#             */
/*   Updated: 2025/12/27 03:54:44 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	load_one_texture(t_cube *cube, t_img *tex, char *path);

int	init_textures(t_cube *cube)
{
	if (load_one_texture(cube, &cube->textures[NO],
			cube->map.texture_paths[NO]) == FAIL)
		return (print_error_with_code(NULL, ERR_NO_TEX, CRITICAL));
	if (load_one_texture(cube, &cube->textures[SO],
			cube->map.texture_paths[SO]) == FAIL)
		return (print_error_with_code(NULL, ERR_SO_TEX, CRITICAL));
	if (load_one_texture(cube, &cube->textures[EA],
			cube->map.texture_paths[EA]) == FAIL)
		return (print_error_with_code(NULL, ERR_EA_TEX, CRITICAL));
	if (load_one_texture(cube, &cube->textures[WE],
			cube->map.texture_paths[WE]) == FAIL)
		return (print_error_with_code(NULL, ERR_WE_TEX, CRITICAL));
	return (OKI);
}

static int	load_one_texture(t_cube *cube, t_img *tex, char *path)
{
	tex->img_ptr = mlx_xpm_file_to_image(cube->mlx_ptr, path, &tex->width,
			&tex->height);
	if (!tex->img_ptr)
		return (CRITICAL);
	tex->addr = mlx_get_data_addr(tex->img_ptr, &tex->bpp, &tex->line_len,
			&tex->endian);
	if (!tex->addr)
		return (CRITICAL);
	return (OKI);
}

// int	init_textures(t_cube *cube)
// {
// 	if (load_textures(cube) != OKI)
// 		return (CRITICAL);
// 	return (OKI);
// }

// int	load_textures(t_cube *cube)
// {
// 	if (load_one_texture(cube, &cube->textures[NO],
// 			cube->map.texture_paths[NO]) == FAIL)
// 		return (print_error_with_code(NULL, ERR_NO_TEX, CRITICAL));
// 	if (load_one_texture(cube, &cube->textures[SO],
// 			cube->map.texture_paths[SO]) == FAIL)
// 		return (print_error_with_code(NULL, ERR_SO_TEX, CRITICAL));
// 	if (load_one_texture(cube, &cube->textures[EA],
// 			cube->map.texture_paths[EA]) == FAIL)
// 		return (print_error_with_code(NULL, ERR_EA_TEX, CRITICAL));
// 	if (load_one_texture(cube, &cube->textures[WE],
// 			cube->map.texture_paths[WE]) == FAIL)
// 		return (print_error_with_code(NULL, ERR_WE_TEX, CRITICAL));
// 	return (OKI);
// }
