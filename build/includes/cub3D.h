/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaryshe <abaryshe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 21:56:46 by abaryshe          #+#    #+#             */
/*   Updated: 2025/10/24 04:08:58 by abaryshe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// <<<<<<<<<<<<<<<<<<<<< INCLUDES >>>>>>>>>>>>>>>>>>>>>

# include "libft.h"

# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

// <<<<<<<<<<<<<<<<<<<<< MACROS >>>>>>>>>>>>>>>>>>>>>

// --- General ---
# define SUCCESS 0
# define FAIL 1

// --- Exit Codes ---
# define EXC_OK 0   // We MAY want to add our own different codes. MAYBE for parsing.
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

// --- Required By Game ---
# define TILE_EMPTY 0
# define TILE_WALL 1
# define TILE_OUT  -1

// <<<<<<<<<<<<<<<<<<<<< STRUCTURES >>>>>>>>>>>>>>>>>>>>>

typedef enum	e_tex
{
	NO, 	// North
	SO, 	// South
	WE, 	// West
	EA, 	// East
	TEX_NB  // Number of textures
}			t_tex;

typedef struct s_img
{
	void		*mlx_img;
	char		*addr; // mlx_get_data_addr

	int			bpp;
	int			line_len;
	int			endian;
	int			width;
	int			height;
}				t_img;

typedef struct s_player
{
	double		pos_x;
	double		pos_y;             // position in map coords (float)

	double		dir_x;
	double		dir_y;       // direction vector (normalized)

	double		plane_x;
	double		plane_y; // camera plane (perp to dir)

	double		move_speed;
	double		rot_speed;
}				t_player;

typedef struct s_map
{
	char **raw;     // array of strings from parser (keep for error messages)

	int width;      // max row length
	int height;     // number of rows
	char **grid;    // rectangular map (same dims as width x height)
}				t_map;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	int			win_width;
	int			win_height;

	t_img		screen;
	t_img		textures[TEX_NB]; // EA, WE, NO, SO
	int			floor_color; // packed RGB
	int			ceil_color;

	t_player	player;
	t_map		map;

	int			key_w;
	int			key_s;
	int			key_a;
	int			key_d;
	int			key_l;
	int			key_r;

	double		delta_time;
}				t_data;

// <<<<<<<<<<<<<<<<<<<<< FUNCTIONS >>>>>>>>>>>>>>>>>>>>>




// testing: parsing: parsing.c:
void			parsing_report(void);

// testing: engine: engine.c
void			engine_report(void);

#endif
