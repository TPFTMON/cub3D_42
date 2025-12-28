/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imirzaev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 17:45:46 by imirzaev          #+#    #+#             */
/*   Updated: 2025/12/28 17:47:30 by imirzaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	parser_cleanup_map(t_map *map)
{
	if (!map)
		return ;
	if (map->grid)
	{
		free_string_array(map->grid);
		map->grid = NULL;
	}
	free_raw_map(map);
	free_texture_paths(map);
	map->width = 0;
	map->height = 0;
	map->has_spawn = false;
	map->has_floor = false;
	map->has_ceil = false;
}

void	free_raw_map(t_map *map)
{
	int	i;

	if (!map->raw)
		return ;
	i = 0;
	while (map->raw[i])
	{
		free(map->raw[i]);
		i++;
	}
	free(map->raw);
	map->raw = NULL;
}

void	free_texture_paths(t_map *map)
{
	int	i;

	i = 0;
	while (i < TEX_NB)
	{
		free(map->texture_paths[i]);
		map->texture_paths[i] = NULL;
		i++;
	}
}
