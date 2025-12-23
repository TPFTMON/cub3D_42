/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imirzaev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 15:15:41 by imirzaev          #+#    #+#             */
/*   Updated: 2025/12/23 15:15:43 by imirzaev         ###   ########.fr       */
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
