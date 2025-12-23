/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 14:23:48 by abaryshe          #+#    #+#             */
/*   Updated: 2025/10/22 14:40:45 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
//parser_errors.c
/*void	handle_error(const char *msg)
{
	ft_putstr_fd("Error\n", STDERR_FD);
	if (msg)
	{
		ft_putstr_fd((char *)msg, STDERR_FD);
		if (msg[ft_strlen(msg) - 1] != '\n')
			ft_putstr_fd("\n", STDERR_FD);
	}
	exit(EXC_PARS);
}
//parser_utils.c
char	*skip_spaces(char *s)
{
	while (s && *s && ft_isspace(*s))//add \t, \r, etc to ft_isspace??
		s++;
	return (s);
}

void	trim_newline(char *s)
{
	size_t	n;

	if (!s)
		return ;
	n = ft_strlen(s);
	while (n > 0 && (s[n - 1] == '\n' || s[n - 1] == '\r'))
	{
		s[n - 1] = '\0';
		n--;
	}
}

int	is_only_spaces(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (1);
	while (s[i])
	{
		if (!ft_isspace((unsigned char)s[i]))
			return (0);
		i++;
	}
	return (1);
}

int	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == ' ' || c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	pack_rgb(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}
//parse_texture.c
int	starts_with_id(const char *s, const char *id)
{
	size_t	i;

	i = 0;
	while (id[i])
	{
		if (s[i] != id[i])
			return (0);
		i++;
	}
	return (1);
}
const char	*text_id(t_tex t)
{
	if (t == NO)
		return ("NO");
	if (t == SO)
		return ("SO");
	if (t == WE)
		return ("WE");
	if (t == EA)
		return ("EA");
	return ("");
}

void	parse_texture(t_map *map, char *line, t_tex texture_type)
{
	char		*p;
	char		*path;
	const char	*id;
	size_t		len;//debatable

	if (!map || !line)
		handle_error("Parser: internal null in parse_texture");
	trim_newline(line);
	p = skip_spaces(line);
	id = text_id(texture_type);
	if (!starts_with_id(p, id) || !ft_isspace((unsigned char)p[2]))
		handle_error("Parser: invalid texture identofier/format");
	if (map->texture_paths[texture_type] != NULL)
		handle_error("Parser: duplicate texture def");
	p += 2;
	p = skip_spaces(p);
	if (!p || *p == '\0')
		handle_error("Parser: missing texture path");
	{
		len = 0;
		while (p[len] && !ft_isspace((unsigned char)p[len]))
			len++;
		path = ft_substr(p, 0, len);
		if (!path)
			handle_error("Parser: malloc failed for texture path");
		p += len;
		p = skip_spaces(p);
		if (p && *p != '\0')
		{
			free(path);
			handle_error("Parser: extra tokens after texture path");
		}
	}
	map->texture_paths[texture_type] = path;
}
//parse_colors.c
int	parse_u8(char **p)
{
	long	val;
	char	*s;

	s = *p;
	if (!s || !ft_isdigit((unsigned char)*s))
		handle_error("Parser: expected a number in color");
	val = 0;
	while (*s && ft_isdigit((unsigned char)*s))
	{
		val = val * 10 + (*s - '0');
		if (val > 255)
			handle_error("Parser: color value out of range (0-255)");
		s++;
	}
	*p = s;
	return ((int)val);
}

void	expect_char(char **p, char c)
{
	if (!p || !*p || **p != c)
		handle_error("Parser: invalid color format");
	(*p)++;
}

void	parse_floor_ceiling_colors(t_map *map, char *line)
{
	char *p;
	char	kind;
	int	r;
	int	g;
	int	b;

	if (!map || !line)
		handle_error("Parser: internal null in parse_floor_ceiling_colors");
	trim_newline(line);
	p = skip_spaces(line);
	kind = *p;
	if (kind != 'F' && kind != 'C')
		handle_error("Parser: invalid color identif (F or C)");
	p++;
	if (!ft_isspace((unsigned char )*p))
		handle_error("Parser: invalid color format (missing space)");
	p = skip_spaces(p);
	r = parse_u8(&p);
	expect_char(&p, ',');
	g = parse_u8(&p);
	expect_char(&p, ',');
	b = parse_u8(&p);
	p = skip_spaces(p);
	if (p && *p != '\0')
		handle_error("Parser: extra tokens after color");
	if (kind == 'F')
	{
		if (map->has_floor)
			handle_error("Parser: duplicate floor color");
		map->color_floor = pack_rgb(r, g, b);
		map->has_floor = true;
	}
	else
	{
		if (map->has_ceil)
			handle_error("Parser: duplicate ceiling color");
		map->color_ceil = pack_rgb(r, g, b);
		map->has_ceil = true;
	}
}
//parse_map.c
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

void	parse_map(t_map *map, char *line, int row)
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
}
//validate_map.c
char	cell(t_map *m, int y, int x)
{
	if (y < 0 || x < 0 || y >= m->height || x >= m->width)
		return (' ');//debatable
	return (m->grid[y][x]);
}

void	build_grid(t_map *map)
{
	int	x;
	int	y;

	map->grid = (char **)ft_calloc(map->height + 1, sizeof(char *));
	if (!map->grid)
		handle_error("Parser: malloc failed building grid");
	y = 0;
	while(y < map->height)
	{
		map->grid[y] = (char *)ft_calloc(map->width + 1, sizeof(char));
		if (!map->grid[y])
			handle_error("Parser: malloc failed building grid row");
		x = 0;
		while (x < map->width)
		{
			if (map->raw[y] && x < (int1000000001
1000000001
1000010001
1000000001
1000000001
1000000001
1000000001
1111111111
---
)ft_strlen(map->raw[y]))
				map->grid[y][x] = map->raw[y][x];
			else
				map->grid[y][x] = ' ';
			x++;
		}
		map->grid[y][map->width] = '\0';
		y++;
	}
	map->grid[map->height] = NULL;
}
void	validate_map(t_map *map)
{
	int	y;
	int	x;

	if (!map)
		handle_error("Parser: internal null in validate_map");
	if (map->height <= 0 || map->width <= 0)
		handle_error("Parser:empty map");
	if (!map->has_spawn)
		handle_error("Parser: missing player spawn in map");
	if (!map->grid)
		build_grid(map);
	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (map->grid[y][x] == '0')
			{
				if (y == 0 || x == 0 || y == map->height - 1 || x == map->width - 1)
					handle_error("Parser:map not closed(open on border)");
				if (cell(map, y - 1, x) == ' ' || cell(map, y + 1, x) == ' ' ||
							cell(map, y, x - 1) == ' ' || cell(map, y, x+ 1) == ' ')
					handle_error("Parser: map not closed(walkable touches void)");
			}
			else if (map->grid[y][x] != '1' && map->grid[y][x] != ' ')
				handle_error("Parser: unexpected cell in final grid");
			x++;
		}
		y++;
	}
}*/
//main parsing logic

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

void	parse_config_line(t_map *map, char *line)
{
	char	*p;

	trim_newline(line);
	p = skip_spaces(line);
	if (*p == '\0')
		return ;
	if (starts_with_id_local(p, "NO") && ft_isspace((unsigned char)p[2]))
		return (parse_texture(map, line, NO));
	if (starts_with_id_local(p, "SO") && ft_isspace((unsigned char)p[2]))
		return (parse_texture(map, line, SO));
	if (starts_with_id_local(p, "WE") && ft_isspace((unsigned char)p[2]))
		return (parse_texture(map, line, WE));
	if (starts_with_id_local(p, "EA") && ft_isspace((unsigned char)p[2]))
		return (parse_texture(map, line, EA));
	if (*p == 'F' && ft_isspace((unsigned char)p[1]))
		return (parse_floor_ceiling_colors(map, line));
	if (*p == 'C' && ft_isspace((unsigned char)p[1]))
		return (parse_floor_ceiling_colors(map, line));
	handle_error("Parser: unknown/invalid line in config section");
}

void	require_all_elements(t_map *map)
{
	if (!map->texture_paths[NO] || !map->texture_paths[SO]
			|| !map->texture_paths[WE] || !map->texture_paths[EA])
		handle_error("Parser: missing texture path(NO/SO/WE/EA)");
	if (!map->has_floor)
		handle_error("Parser: missing floor color (F)");
	if (!map->has_ceil)
		handle_error("Parser: missing ceiling color (C)");
	if (map->height <= 0)
		handle_error("Parser: missing map");
	if (!map->has_spawn)
		handle_error("Parser: missing player spawn (N/S/E/W)");
}

/*void	parse_cub_file(t_cube *cube, const char *path)
{
	int	fd;
	char	*line;
	bool	in_map;
	int		row;
	int		capacity;//dynamic raw map storage

	if (!cube || !path)
		handle_error("Parser: internal null in parse_cub_file");
	fd = open(path, O_RDONLY);
	if (fd < 0)
		handle_error("Parser: failed to open .cub file");
	in_map = false;
	row = 0;
	capacity = 16;
	cube->map.raw = (char **)ft_calloc(capacity, sizeof(char *));
	if (!cube->map.raw)
		handle_error("Parser: malloc failed for map raw");
	cube->map.width = 0;
	cube->map.height = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		if (!in_map)
		{
			if (looks_like_map_line(line))
				in_map = true;
			else
			{
				parse_config_line(&cube->map, line);
				free(line);
				continue ;
			}
		}
		trim_newline(line);
		if (*skip_spaces(line) == '\0')
		{
			free(line);
			close(fd);
			handle_error("Parser: empty line inside map");
		}
		if (!looks_like_map_line(line))
		{
			free(line);
			close(fd);
			handle_error("Parser:non-map line after map started");
		}
		if (row + 1 >= capacity)
		{
			char	**new_raw;
			int	i;

			capacity *= 2;
			new_raw = (char **)ft_calloc(capacity, sizeof(char *));
			if (!new_raw)
			{
				free(line);
				close(fd);
				handle_error("Parser: malloc failed growing raw map");
			}
			i = 0;
			while (i < row)
			{
				new_raw[i] = cube->map.raw[i];
				i++;
			}
			free(cube->map.raw);
			cube->map.raw = new_raw;
		}
		parse_map(&cube->map, line, row);
		row++;
		free(line);
	}
	close(fd);
	cube->map.height = row;
	require_all_elements(&cube->map);
	validate_map(&cube->map);
}*/

void	parsing_report(void)
{
	printf("\e[1;36mThis is the parsing part. It does compile!\n\e[0m");
}
