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

void	parse_cub_file(t_cube *cube, const char *path)
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
	//print_grid(&cube->map);
	validate_map(&cube->map);
}
