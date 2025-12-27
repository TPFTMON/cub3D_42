/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imirzaev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 15:15:15 by imirzaev          #+#    #+#             */
/*   Updated: 2025/12/23 15:15:17 by imirzaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool parse_u8(t_cube *cube, char **p, int *out)
{
    long val;
    char *s;

    if (!p || !*p || !out)
        return parser_error(cube, "Parser: internal null in parse_u8");

    s = *p;
    if (!s || !ft_isdigit((unsigned char)*s))
        return parser_error(cube, "Parser: expected a number in color");

    val = 0;
    while (*s && ft_isdigit((unsigned char)*s))
    {
        val = val * 10 + (*s - '0');
        if (val > 255)
            return parser_error(cube, "Parser: color value out of range (0-255)");
        s++;
    }
    *p = s;
    *out = (int)val;
    return true;
}

/*bool	parse_u8(t_cube *cube, char **p, int *out)
{
	long	val;
	char	*s;

	s = *p;
	if (!s || !ft_isdigit((unsigned char)*s))
		return (parser_error(cube, "Parser: expected a number in color"));
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
}*/

/*static char parse_color_header(char *line, char *out_kind)
{
    char    *p;

    if (!line || !out_kind)
        handle_error("Parser: parse_color_header");
    trim_new_line(line);
    p = skip_spaces(line);
    *out_kind = *p;
    if (*out_kind != 'F' && *out_kind != 'C')
        handle_error("Parser: parse_color_header");
    p++;
    if (!ft_isspace((unsigned char)*p))
        handle_error("Parser: parse_color_header");
    p = skip_spaces(p);
    if (!p || *p == '\0')
        handle_error("Parser: parse_color_header");
    return (p);
}

static int  parse_rgb(char *p)
{
    int r;
    int g;
    int b;

    if (!p)
        handle_error("Parser: parse_rgb");
    r = parse_u8(&p);
    expect_char(&p, ',');
    g = parse_u8(&p);
    expect_char(&p, ',');
    b = parse_u8(&p);
    expect_char(&p, ',');
    p = skip_spaces(p);
    if (p && *p != '\0')
        handle_error("Parser: parse_rgb");
    return (pach_rgb(r, g, b));
}

static void apply_parsed_colors(t_map *map, char kind, int color)
{
    if (kind == 'F')
    {
        if (map->has_floor)
            handle_error("Parser: apply_parsed_colors");
        map->color_floor = color;
        map->has_floor = true;
    }
    else
    {
        if (map->has_ceil)
            handle_error("Parser: parse_rgb");
        map->color_ceil = color;
        map->has_ceil = true;
    }
}

void	parse_floor_ceiling_colors(t_map *map, char *line)
{
    char    kind;
    char    *p;
    int     color;

    if (!map || !line)
        handle_error("Parser: parse_floor_ceiling_colors");
    p = parse_color_header(line, &kind);
    color = parse_rgb(p);
    apply_parsed_colors(map, kind, color);
}*/

bool	parse_floor_ceiling_colors(t_cube *cube, t_map *map, char *line)
{
	char *p;
	char	kind;
	int	r;
	int	g;
	int	b;

	if (!map || !line)
		return (parser_error(cube, "Parser: internal null in parse_floor_ceiling_colors"));
	trim_newline(line);
	p = skip_spaces(line);
	kind = *p;
	if (kind != 'F' && kind != 'C')
		return (parser_error(cube, "Parser: invalid color identif (F or C)"));
	p++;
	if (!ft_isspace((unsigned char )*p))
		return (parser_error(cube, "Parser: invalid color format (missing space)"));
	p = skip_spaces(p);
	if (!parse_u8(cube, &p, &r))
		return (false);
	if (!expect_char(cube, &p, ','))
		return (false);
	if (!parse_u8(cube, &p, &g))
		return (false);
	if (!expect_char(cube, &p, ','))
		return (false);
	if (!parse_u8(cube, &p, &b))
		return (false);
	p = skip_spaces(p);
	if (p && *p != '\0')
		return (parser_error(cube, "Parser: extra tokens after color"));
	if (kind == 'F')
	{
		if (map->has_floor)
			return (parser_error(cube, "Parser: duplicate floor color"));
		map->color_floor = pack_rgb(r, g, b);
		map->has_floor = true;
	}
	else
	{
		if (map->has_ceil)
			return (parser_error(cube, "Parser: duplicate ceiling color"));
		map->color_ceil = pack_rgb(r, g, b);
		map->has_ceil = true;
	}
	return (true);
}