/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imirzaev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 15:15:28 by imirzaev          #+#    #+#             */
/*   Updated: 2025/12/28 17:45:23 by imirzaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	set_spawn(t_cube *cube, t_map *map, t_spawn spawn)
{
	if (!cube || !map)
		return (parser_error(cube, "Parser: internal null in set_spawn"));
	if (map->has_spawn)
		return (parser_error(cube,
				"Parser: multiple player spawn positions in map"));
	if (spawn.dir == 'N')
		map->player_direction = NO;
	else if (spawn.dir == 'S')
		map->player_direction = SO;
	else if (spawn.dir == 'W')
		map->player_direction = WE;
	else if (spawn.dir == 'E')
		map->player_direction = EA;
	else
		return (parser_error(cube, "Parser: invalid player dir char"));
	map->has_spawn = true;
	map->spawn_x = spawn.x;
	map->spawn_y = spawn.y;
	return (true);
}

static bool	scan_map_line(t_cube *cube, t_map *map, char *dup, int row)
{
	int	x;
	t_spawn	spawn;

	x = 0;
	while (dup[x])
	{
		if (!is_valid_map_char(dup[x]))
			return (parser_error(cube, "PARSER: invalid char in map"));
		if (dup[x] == 'N' || dup[x] == 'S' || dup[x] == 'E' || dup[x] == 'W')
		{
			spawn.x = x;
			spawn.y = row;
			spawn.dir = dup[x];
			if (!set_spawn(cube, map, spawn))
				return (false);
		}
		x++;
	}
	return (true);
}

bool	parse_map(t_cube *cube, t_map *map, char *line, int row)
{
	char	*dup;
	int	len;

	if (!cube || !map || !line)
		return (parser_error(cube, "Parser: internal null in parse_map"));
	trim_newline(line);
	dup = ft_strdup(line);
	if (!dup)
		return (parser_error(cube,
				"Parser: malloc failed duplicating map line"));
	if (!scan_map_line(cube, map, dup, row))
	{
		free(dup);
		return (false);
	}
	map->raw[row] = dup;
	len = (int)ft_strlen(dup);
	if (len > map->width)
	map->width = len;
	if (row + 1 > map->height)
		map->height = row + 1;
	return (true);
}
