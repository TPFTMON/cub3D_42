/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imirzaev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 15:16:11 by imirzaev          #+#    #+#             */
/*   Updated: 2025/12/23 15:16:13 by imirzaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	handle_error(const char *msg)
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

bool	expect_char(t_cube *cube, char **p, char c)
{
	if (!p || !*p || **p != c)
		parser_error(cube, "Parser: invalid color format");
	(*p)++;
	return (true);
}

bool	parser_error(t_cube *cube, const char *msg)
{
    if (!cube)
        return false;
    cube->parse_err = EXC_PARS;
    if (!msg)
        msg = "Parser: unknown error";
    ft_strlcpy(cube->parse_errmsg, msg, sizeof(cube->parse_errmsg));
    return false;
}

void	parser_perror_and_setexit(t_cube *cube)
{
    ft_putstr_fd("Error\n", STDERR_FD);
    if (cube && cube->parse_errmsg[0])
    {
        ft_putstr_fd(cube->parse_errmsg, STDERR_FD);
        if (cube->parse_errmsg[ft_strlen(cube->parse_errmsg) - 1] != '\n')
            ft_putstr_fd("\n", STDERR_FD);
    }
}

void	parser_cleanup_map(t_map *map)
{
    if (!map)
        return;
    if (map->grid)
    {
        free_string_array(map->grid);
        map->grid = NULL;
    }
    free_raw_map(map);
    free_texture_paths(map);
    map->width = 0;
    map->height = 0;
    map->has_spawn = false;
    map->has_floor = false;
    map->has_ceil = false;
}

void	free_raw_map(t_map *map)
{
	int	i;

	if (!map->raw)
		return ;
	i = 0;
	while (map->raw[i])
	{
		free(map->raw[i]);
		i++;
	}
	free(map->raw);
	map->raw = NULL;
}
void	free_texture_paths(t_map *map)
{
	int	i;

	i = 0;
	while (i < TEX_NB)
	{
		free(map->texture_paths[i]);
		map->texture_paths[i] = NULL;
		i++;
	}
}