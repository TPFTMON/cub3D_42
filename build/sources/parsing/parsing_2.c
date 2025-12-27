/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imirzaev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 15:16:43 by imirzaev          #+#    #+#             */
/*   Updated: 2025/12/23 15:16:47 by imirzaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	parse_cub_file(t_cube *cube, const char *path)
{
	int	fd;
	char	*line;
	bool	in_map;
	int		row;
	int		capacity;//dynamic raw map storage

	if (!cube || !path)
		return (parser_error(cube, "Parser: internal null in parse_cub_file"));
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (parser_error(cube, "Parser: failed to open .cub file"));
	in_map = false;
	row = 0;
	capacity = 16;
	cube->map.raw = (char **)ft_calloc(capacity, sizeof(char *));
	if (!cube->map.raw)
	{
		close(fd);
		return (parser_error(cube, "Parser: malloc failed for map raw"));
	}
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
				if (!parse_config_line(cube, &cube->map, line))
				{
					free(line);
					close (fd);
					parser_cleanup_map(&cube->map);
					return (false);
				}
				free(line);
				continue ;
			}
		}
		trim_newline(line);
		if (*skip_spaces(line) == '\0')
		{
			free(line);
			close(fd);
			parser_error(cube, "Parser: empty line inside map");
			parser_cleanup_map(&cube->map);
			return (false);
		}
		if (!looks_like_map_line(line))
		{
			free(line);
			close(fd);
			parser_error(cube, "Parser:non-map line after map started");
			parser_cleanup_map(&cube->map);
			return (false);
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
				parser_error(cube, "Parser: malloc failed growing raw map");
				parser_cleanup_map(&cube->map);
				return (false);
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
		if (!parse_map(cube, &cube->map, line, row))
		{
			free(line);
			close(fd);
			parser_cleanup_map(&cube->map);
			return (false);
		}
		row++;
		free(line);
	}
	close(fd);
	cube->map.height = row;
	if (!require_all_elements(cube, &cube->map))
	{
		parser_cleanup_map(&cube->map);
		return (false);
	}
	//print_grid(&cube->map);
	if (!validate_map(cube, &cube->map))
	{
		parser_cleanup_map(&cube->map);
		return (false);
	}
	return (true);
}
