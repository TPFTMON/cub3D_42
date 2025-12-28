/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imirzaev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/28 17:23:00 by imirzaev          #+#    #+#             */
/*   Updated: 2025/12/28 17:27:27 by imirzaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	parse_one_map_row(t_cube *cube, int fd, char *line, int row)
{
	if (!parse_map(cube, &cube->map, line, row))
		return (parse_fail(cube, fd, line, NULL));
	free(line);
	return (true);
}

bool	finalize_map_or_fail(t_cube *cube, int row)
{
	cube->map.height = row;
	if (!require_all_elements(cube, &cube->map))
	{
		parser_cleanup_map(&cube->map);
		gnl_clear();
		return (false);
	}
	if (!validate_map(cube, &cube->map))
	{
		parser_cleanup_map(&cube->map);
		gnl_clear();
		return (false);
	}
	return (true);
}

bool	parse_cub_read_loop(t_cube *cube, t_parse_ctx *ctx)
{
	if (!cube || !ctx || ctx->fd < 0 || !ctx->capacity)
		return (false);
	ctx->in_map = false;
	ctx->row = 0;
	while ((ctx->line = get_next_line(ctx->fd)) != NULL)
	{
		if (!ctx->in_map)
		{
			if (!handle_config_section(cube, ctx->fd, ctx->line, &ctx->in_map))
				return (false);
			if (!ctx->in_map)
				continue ;
		}
		if (!validate_map_line_or_fail(cube, ctx->fd, ctx->line))
			return (false);
		if (!ensure_raw_capacity(cube, ctx))
			return (false);
		if (!parse_one_map_row(cube, ctx->fd, ctx->line, ctx->row))
			return (false);
		ctx->row++;
	}
	return (true);
}

static bool	parse_cub_run(t_cube *cube, int fd, int *capacity)
{
	t_parse_ctx	ctx;

	ctx.fd = fd;
	ctx.line = NULL;
	ctx.row = 0;
	ctx.capacity = capacity;
	ctx.in_map = false;
	if (!parse_cub_read_loop(cube, &ctx))
		return (false);
	if (!finalize_map_or_fail(cube, ctx.row))
		return (false);
	return (true);
}

bool	parse_cub_file(t_cube *cube, const char *path)
{
	int	fd;
	int	capacity;

	fd = -1;
	capacity = 16;
	if (!parse_open_and_init(cube, path, &fd, &capacity))
	{
		gnl_clear();
		return (false);
	}
	if (!parse_cub_run(cube, fd, &capacity))
	{
		close(fd);
		gnl_clear();
		return (false);
	}
	close(fd);
	gnl_clear();
	return (true);
}
