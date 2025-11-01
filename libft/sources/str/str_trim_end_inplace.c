/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_trim_end_inplace.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 07:45:11 by abaryshe          #+#    #+#             */
/*   Updated: 2025/11/01 08:10:39 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Trims trailing characters specified in 'set' from the end of a string 'str'.
 * Modifies the string in place by adding a null terminator.
 * Returns the original string pointer.
 */
char	*str_trim_end_inplace(char *str, const char *set)
{
	int		len;
	char	*end;

	if (!str || !set)
		return (str);
	len = ft_strlen(str);
	if (len == 0)
		return (str);
	end = str + len - 1;
	while (end >= str && ft_strchr(set, *end))
		end--;
	*(end + 1) = '\0';
	return (str);
}
