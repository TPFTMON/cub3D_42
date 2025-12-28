/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imirzaev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 15:17:00 by imirzaev          #+#    #+#             */
/*   Updated: 2025/12/28 17:34:38 by imirzaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	cell(t_map *m, int y, int x)
{
	if (y < 0 || x < 0 || y >= m->height || x >= m->width)
		return (' ');
	return (m->grid[y][x]);
}

static bool	allocate_grid(t_cube *cube, t_map *map)
{
	if (!cube || !map)
		return (parser_error(cube, "Parser: internal null in build_grid"));
	map->grid = (char **)ft_calloc(map->height + 1, sizeof(char *));
	if (!map->grid)
		return (parser_error(cube, "Parser: malloc failed building grid"));
	return (true);
}

static bool	fill_grid_rows(t_cube *cube, t_map *map)
{
	int	y;
	int	x;

	y = 0;
	while (y < map->height)
	{
		map->grid[y] = (char *)ft_calloc(map->width + 1, sizeof(char));
		if (!map->grid[y])
			return (parser_error(cube,
					"Parser: malloc failed building grid row"));
		x = 0;
		while (x < map->width)
		{
			if (map->raw[y] && x < (int)ft_strlen(map->raw[y]))
				map->grid[y][x] = map->raw[y][x];
			else
				map->grid[y][x] = ' ';
			x++;
		}
		map->grid[y][map->width] = '\0';
		y++;
	}
	map->grid[map->height] = NULL;
	return (true);
}

bool	build_grid(t_cube *cube, t_map *map)
{
	if (!allocate_grid(cube, map))
		return (false);
	if (!fill_grid_rows(cube, map))
		return (false);
	return (true);
}
