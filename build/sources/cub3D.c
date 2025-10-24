/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 21:57:17 by abaryshe          #+#    #+#             */
/*   Updated: 2025/10/24 04:37:08 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	// PARSING IS HAPPENING HERE
	// +
	// DATA FOR ENGINE WRITTEN TO STRUCT
	parsing_report();
	engine_report();

	char	*miaou = "\e[1;32mմյաու մյաու մյաու մյաու մյաու\e[0m\n";
	ft_strlen(miaou);
	printf("%s", miaou);
	// THEN THE ENGINE DOES HIS GAME LOOP
	return (0);
}
