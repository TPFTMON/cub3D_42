/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 14:23:48 by abaryshe          #+#    #+#             */
/*   Updated: 2025/12/28 17:22:42 by imirzaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	starts_with_id_local(const char *s, const char *id)
{
	size_t	i;

	i = 0;
	while (id[i])
	{
		if (s[i] != id[i])
			return (false);
		i++;
	}
	return (true);
}

bool	looks_like_map_line(char *line)
{
	size_t	i;
	bool	has_tile;

	if (!line)
		return (false);
	trim_newline(line);
	i = 0;
	has_tile = false;
	while (line[i])
	{
		if (!is_valid_map_char(line[i]))
			return (false);
		if (line[i] == '0' || line[i] == '1'
			|| line[i] == 'N' || line[i] == 'S'
			|| line[i] == 'E' || line[i] == 'W')
			has_tile = true;
		i++;
	}
	return (has_tile);
}

bool	parse_config_line(t_cube *cube, t_map *map, char *line)
{
	char	*p;

	trim_newline(line);
	p = skip_spaces(line);
	if (*p == '\0')
		return (true);
	if (starts_with_id_local(p, "NO") && ft_isspace((unsigned char)p[2]))
		return (parse_texture(cube, map, line, NO));
	if (starts_with_id_local(p, "SO") && ft_isspace((unsigned char)p[2]))
		return (parse_texture(cube, map, line, SO));
	if (starts_with_id_local(p, "WE") && ft_isspace((unsigned char)p[2]))
		return (parse_texture(cube, map, line, WE));
	if (starts_with_id_local(p, "EA") && ft_isspace((unsigned char)p[2]))
		return (parse_texture(cube, map, line, EA));
	if (*p == 'F' && ft_isspace((unsigned char)p[1]))
		return (parse_floor_ceiling_colors(cube, map, line));
	if (*p == 'C' && ft_isspace((unsigned char)p[1]))
		return (parse_floor_ceiling_colors(cube, map, line));
	return (parser_error(cube,
			"Parser: unknown/invalid line in config section"));
}

bool	require_all_elements(t_cube *cube, t_map *map)
{
	if (!map->texture_paths[NO] || !map->texture_paths[SO]
		|| !map->texture_paths[WE] || !map->texture_paths[EA])
		return (parser_error(cube,
				"Parser: missing texture path(NO/SO/WE/EA)"));
	if (!map->has_floor)
		return (parser_error(cube, "Parser: missing floor color (F)"));
	if (!map->has_ceil)
		return (parser_error(cube, "Parser: missing ceiling color (C)"));
	if (map->height <= 0)
		return (parser_error(cube, "Parser: missing map"));
	if (!map->has_spawn)
		return (parser_error(cube, "Parser: missing player spawn (N/S/E/W)"));
	return (true);
}
