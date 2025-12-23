/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imirzaev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 15:15:28 by imirzaev          #+#    #+#             */
/*   Updated: 2025/12/23 15:15:30 by imirzaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	set_spawn(t_map *map, int x, int y, char c)
{
	if (map->has_spawn)
		handle_error("Parser: multiple player spawn positions in map");
	map->has_spawn = true;
	map->spawn_x = x;
	map->spawn_y = y;
	if (c == 'N')
		map->player_direction = NO;
	else if (c == 'S')
		map->player_direction = SO;
	else if (c == 'W')
		map->player_direction = WE;
	else if (c == 'E')
		map->player_direction = EA;
	else
		handle_error("Parser:invalid player dir char");
}

static char *dup_and_process_map_row(t_map *map, char *line, int row, int *out_len)
{
    char    *dup;
    int     x;

    if (!map || !line || !out_len)
        handle_error("Parser: dup_and_process_map_row");
    trim_newline(line);
    if (!dup)
        handle_error("Parser: dup_and_process_map_row");
    x = 0;
    while (dup[x])
    {
        if (!is_valid_map_char(dup[x]))
        {
            free(dup);
            handle_error("Parser: dup_and_process_map_row");
        }
        if (dup[x] == 'N' || dup[x] == 'S' || dup[x] == 'E' || dup[x] == 'W')
        {
            set_spawn(map, x, row, dup[x]);
            dup[x] = '0';
        }
        x++;
    }
    *out_len = x;
    return (dup);
}

void	parse_map(t_map *map, char *line, int row)
{
    char    *dup;
    int     len;

    if (!map || !line)
        handle_error("Parser: parse_map");
    dup = dup_and_process_map_row(map, line, row, &len);
    map->raw[row] = dup;
    if (len > map->width)
        map->width = len;//check
    if (row + 1 > map->height)
        map->height = row + 1;//check
}

/*void	parse_map(t_map *map, char *line, int row)
{
	char *dup;
	int	x;

	if (!map || !line)
		handle_error("Parser: internal null in parse_map");
	trim_newline(line);
	dup = ft_strdup(line);
	if (!dup)
		handle_error("Parser: malloc failed duplicating map line");
	x = 0;
	while (dup[x])
	{
		if (!is_valid_map_char(dup[x]))
		{
			free(dup);
			handle_error("PARSER: invalid char in map");
		}
		if (dup[x] == 'N' || dup[x] == 'S' || dup[x] == 'E' || dup[x] == 'W')
		{
			set_spawn(map, x, row, dup[x]);
			dup[x] = '0';
		}
		x++;
	}
	map->raw[row] = dup;//debatable
	if (x > map->width)
		map->width = x;
	if (row + 1 > map->height)//debatable
		map->height = row + 1;
}*/
