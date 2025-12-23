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

void	expect_char(char **p, char c)
{
	if (!p || !*p || **p != c)
		handle_error("Parser: invalid color format");
	(*p)++;
}