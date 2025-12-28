/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imirzaev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 15:15:41 by imirzaev          #+#    #+#             */
/*   Updated: 2025/12/28 17:52:02 by imirzaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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

static bool	parse_texture_header(t_cube *cube, t_texparse *ctx)
{
	char	*p;
	const char	*id;

	if (!cube || !ctx || !ctx->map || !ctx->line)
		return (parser_error(cube, "Parser: internal null in parse_texture"));
	trim_newline(ctx->line);
	p = skip_spaces(ctx->line);
	id = text_id(ctx->type);
	if (!starts_with_id(p, id) || !ft_isspace((unsigned char)p[2]))
		return (parser_error(cube,
				"Parser: invalid texture identifier/format"));
	if (ctx->map->texture_paths[ctx->type] != NULL)
		return (parser_error(cube, "Parser: duplicate texture definition"));
	p += 2;
	p = skip_spaces(p);
	if (!p || *p == '\0')
		return (parser_error(cube, "Parser: missing texture path"));
	ctx->p_out = p;
	return (true);
}

static bool	extract_texture_path(t_cube *cube, char *p, char **path_out)
{
	size_t	len;
	char	*path;

	if (!cube || !p || !path_out)
		return (parser_error(cube,
				"Parser: internal null in extract_texture_path"));
	len = 0;
	while (p[len] && !ft_isspace((unsigned char)p[len]))
		len++;
	path = ft_substr(p, 0, len);
	if (!path)
		return (parser_error(cube, "Parser: malloc failed for texture path"));
	p += len;
	p = skip_spaces(p);
	if (p && *p != '\0')
	{
		free(path);
		return (parser_error(cube, "Parser: extra tokens after texture path"));
	}
	*path_out = path;
	return (true);
}

bool	parse_texture(t_cube *cube, t_map *map, char *line, t_tex texture_type)
{
	t_texparse	ctx;
	char	*path;

	ctx.map = map;
	ctx.line = line;
	ctx.type = texture_type;
	ctx.p_out = NULL;
	if (!parse_texture_header(cube, &ctx))
		return (false);
	if (!extract_texture_path(cube, ctx.p_out, &path))
		return (false);
	map->texture_paths[texture_type] = path;
	return (true);
}
