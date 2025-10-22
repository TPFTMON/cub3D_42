/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 21:56:46 by abaryshe          #+#    #+#             */
/*   Updated: 2025/10/22 14:45:11 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// <<<<<<<<<<<<<<<<<<<<< INCLUDES >>>>>>>>>>>>>>>>>>>>>

# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <math.h>
# include <sys/time.h>

// <<<<<<<<<<<<<<<<<<<<< MACROS >>>>>>>>>>>>>>>>>>>>>

// --- General ---
# define SUCCESS 0
# define FAIL 1

// --- Exit Codes ---
# define EXC_OK 0  // We MAY want to add our own different codes. MAYBE for parsing.
# define EXC_CRIT 1 // !!!
# define EXC_PARS 2 // !!!

// --- File Descriptors ---
# define STDIN_FD 0
# define STDOUT_FD 1
# define STDERR_FD 2

// --- Messages ---


// // --- Some Colors ---
// # define RESET "\e[0m"
// # define BOLD "\e[1m"
// # define GREEN "\e[32m"
// # define YELLOW "\e[33m"
// # define CYAN "\e[36m"

// <<<<<<<<<<<<<<<<<<<<< STRUCTURES >>>>>>>>>>>>>>>>>>>>>



// <<<<<<<<<<<<<<<<<<<<< FUNCTIONS >>>>>>>>>>>>>>>>>>>>>





//testing: parsing: parsing.c:
void	parsing_report(void);

//testing: player: player.c
void	player_report(void);

#endif
