/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imirzaev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 17:34:53 by imirzaev          #+#    #+#             */
/*   Updated: 2025/12/28 17:39:35 by imirzaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static bool	validate_map_preamble(t_cube *cube, t_map *map)
{
	if (!cube || !map)
		return (parser_error(cube, "Parser: internal null in validate_map"));
	if (map->height <= 0 || map->width <= 0)
		return (parser_error(cube, "Parser:empty map"));
	if (!map->has_spawn)
		return (parser_error(cube, "Parser: missing player spawn in map"));
	if (!map->grid)
	{
		if (!build_grid(cube, map))
			return (false);
	}
	return (true);
}

static bool	validate_map_cell(t_cube *cube, t_map *map, int y, int x)
{
	char	c;

	c = map->grid[y][x];
	if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (y == 0 || x == 0 || y == map->height - 1 || x == map->width - 1)
			return (parser_error(cube,
					"Parser:map not closed(open on border)"));
		if (cell(map, y - 1, x) == ' ' || cell(map, y + 1, x) == ' '
			|| cell(map, y, x - 1) == ' ' || cell(map, y, x + 1) == ' ')
			return (parser_error(cube,
					"Parser: map not closed(walkable touches void)"));
	}
	else if (c != '1' && c != ' ' && c != 'N'
		&& c != 'S' && c != 'E' && c != 'W')
		return (parser_error(cube, "Parser: unexpected cell in final grid"));
	return (true);
}

bool	validate_map(t_cube *cube, t_map *map)
{
	int	y;
	int	x;

	if (!validate_map_preamble(cube, map))
		return (false);
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (!validate_map_cell(cube, map, y, x))
				return (false);
			x++;
		}
		y++;
	}
	return (true);
}
