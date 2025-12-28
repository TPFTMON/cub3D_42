/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imirzaev <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/23 15:16:28 by imirzaev          #+#    #+#             */
/*   Updated: 2025/12/28 17:15:03 by imirzaev         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	*skip_spaces(char *s)
{
	while (s && *s && ft_isspace(*s))//add \t, \r, etc to ft_isspace??
		s++;
	return (s);
}

void	trim_newline(char *s)
{
	size_t	n;

	if (!s)
		return ;
	n = ft_strlen(s);
	while (n > 0 && (s[n - 1] == '\n' || s[n - 1] == '\r'))
	{
		s[n - 1] = '\0';
		n--;
	}
}

int	is_only_spaces(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (1);
	while (s[i])
	{
		if (!ft_isspace((unsigned char)s[i]))
			return (0);
		i++;
	}
	return (1);
}

int	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == ' ' || c == 'N'
		|| c == 'S' || c == 'E' || c == 'W');
}

int	pack_rgb(int r, int g, int b)
{
	return ((r << 16) | (g << 8) | b);
}
