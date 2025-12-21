/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_string_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 19:06:42 by abaryshe          #+#    #+#             */
/*   Updated: 2025/12/21 19:06:43 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*free_string_array(char **str_array)
{
	int	i;

	if (!str_array)
		return (NULL);
	i = 0;
	while (str_array[i])
		i++;
	while (i >= 0)
	{
		free(str_array[i]);
		str_array[i] = NULL;
		i--;
	}
	free(str_array);
	return (NULL);
}
