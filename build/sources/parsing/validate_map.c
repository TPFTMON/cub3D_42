/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imirzaev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 15:17:00 by imirzaev          #+#    #+#             */
/*   Updated: 2025/12/23 15:17:02 by imirzaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	cell(t_map *m, int y, int x)
{
	if (y < 0 || x < 0 || y >= m->height || x >= m->width)
		return (' ');//debatable
	return (m->grid[y][x]);
}

bool	build_grid(t_cube *cube, t_map *map)
{
	int	x;
	int	y;

	if (!cube || !map)
		return (parser_error(cube, "Parser: internal null in build_grid"));
	map->grid = (char **)ft_calloc(map->height + 1, sizeof(char *));
	if (!map->grid)
		return (parser_error(cube, "Parser: malloc failed building grid"));
	y = 0;
	while(y < map->height)
	{
		map->grid[y] = (char *)ft_calloc(map->width + 1, sizeof(char));
		if (!map->grid[y])
			return (parser_error(cube, "Parser: malloc failed building grid row"));
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
bool	validate_map(t_cube *cube, t_map *map)
{
	int	y;
	int	x;

	//print_grid(map);
	//printf("validate map\n");
	if (!cube || !map)
		return (parser_error(cube, "Parser: internal null in validate_map"));
	if (map->height <= 0 || map->width <= 0)
		return (parser_error(cube, "Parser:empty map"));
	if (!map->has_spawn)
		return (parser_error(cube, "Parser: missing player spawn in map"));
	if (!map->grid)
		if (!build_grid(cube, map))
			return (false);
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->grid[y][x] == '0' || map->grid[y][x] == 'N' || map->grid[y][x] == 'S'
				|| map->grid[y][x] == 'E' || map->grid[y][x] == 'W')
			{
				if (y == 0 || x == 0 || y == map->height - 1 || x == map->width - 1)
					return (parser_error(cube, "Parser:map not closed(open on border)"));
				if (cell(map, y - 1, x) == ' ' || cell(map, y + 1, x) == ' ' ||
							cell(map, y, x - 1) == ' ' || cell(map, y, x+ 1) == ' ')
					return (parser_error(cube, "Parser: map not closed(walkable touches void)"));
			}
			else if (map->grid[y][x] != '1' && map->grid[y][x] != ' ' && map->grid[y][x] != 'N'
					&& map->grid[y][x] != 'S' && map->grid[y][x] != 'E' && map->grid[y][x] != 'W')
				return (parser_error(cube, "Parser: unexpected cell in final grid"));
			x++;
		}
		y++;
	}
	return (true);
}
