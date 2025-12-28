/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imirzaev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 15:15:15 by imirzaev          #+#    #+#             */
/*   Updated: 2025/12/28 17:11:34 by imirzaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	parse_u8(t_cube *cube, char **p, int *out)
{
	long	val;
	char	*s;

	if (!p || !*p || !out)
		return (parser_error(cube, "Parser: internal null in parse_u8"));
	s = *p;
	if (!s || !ft_isdigit((unsigned char)*s))
		return (parser_error(cube, "Parser: expected a number in color"));
	val = 0;
	while (*s && ft_isdigit((unsigned char)*s))
	{
		val = val * 10 + (*s - '0');
		if (val > 255)
			return (parser_error(cube,
					"Parser: color value out of range (0-255)"));
		s++;
	}
	*p = s;
	*out = (int)val;
	return (true);
}

static bool	parse_color_header(t_cube *cube, char *line, char **p, char *kind)
{
	if (!cube || !line || !p || !kind)
		return (parser_error(cube,
				"Parser: internal null in parse_floor_ceiling_colors"));
	trim_newline(line);
	*p = skip_spaces(line);
	*kind = **p;
	if (*kind != 'F' && *kind != 'C')
		return (parser_error(cube, "Parser: invalid color identif (F or C)"));
	(*p)++;
	if (!ft_isspace((unsigned char)**p))
		return (parser_error(cube,
				"Parser: invalid color format (missing space)"));
	*p = skip_spaces(*p);
	return (true);
}

static bool	parse_color_triplet(t_cube *cube, char **p, t_rgb *rgb)
{
	if (!cube || !p || !*p || !rgb)
		return (parser_error(cube,
				"Parser: internal null in parse_color_triplet"));
	if (!parse_u8(cube, p, &rgb->r))
		return (false);
	if (!expect_char(cube, p, ','))
		return (false);
	if (!parse_u8(cube, p, &rgb->g))
		return (false);
	if (!expect_char(cube, p, ','))
		return (false);
	if (!parse_u8(cube, p, &rgb->b))
		return (false);
	*p = skip_spaces(*p);
	if (**p != '\0')
		return (parser_error(cube, "Parser: extra tokens after color"));
	return (true);
}

static bool	apply_color_to_map(t_cube *cube, t_map *map, char kind, t_rgb rgb)
{
	if (kind == 'F')
	{
		if (map->has_floor)
			return (parser_error(cube, "Parser: duplicate floor color"));
		map->color_floor = pack_rgb(rgb.r, rgb.g, rgb.b);
		map->has_floor = true;
	}
	else
	{
		if (map->has_ceil)
			return (parser_error(cube,
					"Parser: duplicate ceiling color"));
		map->color_ceil = pack_rgb(rgb.r, rgb.g, rgb.b);
		map->has_ceil = true;
	}
	return (true);
}

bool	parse_floor_ceiling_colors(t_cube *cube, t_map *map, char *line)
{
	char	*p;
	char	kind;
	t_rgb	rgb;

	if (!map)
		return (parser_error(cube,
				"Parser: internal null in parse_floor_ceiling_colors"));
	if (!parse_color_header(cube, line, &p, &kind))
		return (false);
	if (!parse_color_triplet(cube, &p, &rgb))
		return (false);
	return (apply_color_to_map(cube, map, kind, rgb));
}
