/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imirzaev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 15:16:43 by imirzaev          #+#    #+#             */
/*   Updated: 2025/12/28 17:20:48 by imirzaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	parse_fail(t_cube *cube, int fd, char *line, const char *msg)
{
	if (line)
		free(line);
	if (fd >= 0)
		close(fd);
	if (msg)
		parser_error(cube, msg);
	parser_cleanup_map(&cube->map);
	gnl_clear();
	return (false);
}

bool	parse_open_and_init(t_cube *cube, const char *path,
		int *fd, int *capacity)
{
	if (!cube || !path || !fd || !capacity)
		return (parser_error(cube, "Parser: internal null in parse_cub_file"));
	*fd = open(path, O_RDONLY);
	if (*fd < 0)
		return (parser_error(cube, "Parser: failed to open .cub file"));
	*capacity = 16;
	cube->map.raw = (char **)ft_calloc(*capacity, sizeof(char *));
	if (!cube->map.raw)
	{
		close(*fd);
		*fd = -1;
		return (parser_error(cube, "Parser: malloc failed for map raw"));
	}
	cube->map.width = 0;
	cube->map.height = 0;
	return (true);
}

bool	handle_config_section(t_cube *cube, int fd, char *line, bool *in_map)
{
	if (looks_like_map_line(line))
	{
		*in_map = true;
		return (true);
	}
	if (!parse_config_line(cube, &cube->map, line))
		return (parse_fail(cube, fd, line, NULL));
	free(line);
	return (true);
}

bool	validate_map_line_or_fail(t_cube *cube, int fd, char *line)
{
	trim_newline(line);
	if (*skip_spaces(line) == '\0')
		return (parse_fail(cube, fd, line, "Parser: empty line inside map"));
	if (!looks_like_map_line(line))
		return (parse_fail(cube, fd, line,
				"Parser:non-map line after map started"));
	return (true);
}

bool	ensure_raw_capacity(t_cube *cube, t_parse_ctx *ctx)
{
	char	**new_raw;
	int		i;

	if (!cube || !ctx || !ctx->capacity)
		return (parser_error(cube,
				"Parser: internal null in ensure_raw_capacity"));
	if (ctx->row + 1 < *(ctx->capacity))
		return (true);
	*(ctx->capacity) *= 2;
	new_raw = (char **)ft_calloc(*(ctx->capacity), sizeof(char *));
	if (!new_raw)
		return (parse_fail(cube, ctx->fd, ctx->line,
				"Parser: malloc failed growing raw map"));
	i = 0;
	while (i < ctx->row)
	{
		new_raw[i] = cube->map.raw[i];
		i++;
	}
	free(cube->map.raw);
	cube->map.raw = new_raw;
	return (true);
}
