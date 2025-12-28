/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imirzaev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 15:16:11 by imirzaev          #+#    #+#             */
/*   Updated: 2025/12/28 17:13:35 by imirzaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	gnl_clear(void)
{
	get_next_line(-1);
}

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
		return (parser_error(cube, "Parser: internal null in expect_char"));
	if (**p != c)
		return (parser_error(cube, "Parser: invalid color format"));
	(*p)++;
	return (true);
}

bool	parser_error(t_cube *cube, const char *msg)
{
	if (!cube)
		return (false);
	cube->parse_err = EXC_PARS;
	if (!msg)
		msg = "Parser: unknown error";
	ft_strlcpy(cube->parse_errmsg, msg, sizeof(cube->parse_errmsg));
	return (false);
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
